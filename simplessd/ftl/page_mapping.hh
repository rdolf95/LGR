/*
 * Copyright (C) 2017 CAMELab
 *
 * This file is part of SimpleSSD.
 *
 * SimpleSSD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SimpleSSD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SimpleSSD.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FTL_PAGE_MAPPING__
#define __FTL_PAGE_MAPPING__

#include <cinttypes>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <deque>

#include "ftl/abstract_ftl.hh"
#include "ftl/common/block.hh"
#include "ftl/ftl.hh"
#include "pal/pal.hh"

#include "ftl/error_modeling.hh"

#include "ftl/bloom_filter.hh" // for bloom filter
#include "sim/engine.hh"

extern Engine engine;

namespace SimpleSSD {

namespace FTL {

class PageMapping : public AbstractFTL {
 private:
  PAL::PAL *pPAL;

  ConfigReader &conf;

  std::unordered_map<uint64_t, std::vector<std::pair<uint32_t, uint32_t>>>
      table;
  std::unordered_map<uint32_t, Block> blocks;
  std::list<Block> freeBlocks;
  uint32_t nFreeBlocks;  // For some libraries which std::list::size() is O(n)
  std::vector<uint32_t> lastFreeBlock;
  Bitset lastFreeBlockIOMap;
  uint32_t lastFreeBlockIndex;

  std::vector<uint32_t> layerQueueNum;

  bool bReclaimMore;
  bool bRandomTweak;
  uint32_t bitsetSize;

  struct {
    uint64_t gcCount;
    uint64_t reclaimedBlocks;
    uint64_t validSuperPageCopies;
    uint64_t validPageCopies;
    uint64_t refreshGcPageCopies;

    // Refresh stat
    uint64_t refreshCount;
    uint64_t refreshedBlocks;
    uint64_t refreshSuperPageCopies;
    uint64_t refreshPageCopies;
    uint64_t refreshCallCount;
    uint64_t layerCheckCount;

    uint64_t doubleInsertionCount;

    // Hot cold seperation
    uint64_t hotGcCount;
    uint64_t reclaimedHotBlocks;
    uint64_t hotValidSuperPageCopies;
    uint64_t hotValidPageCopies;

    uint64_t coldGcCount;
    uint64_t reclaimedColdBlocks;
    uint64_t coldValidSuperPageCopies;
    uint64_t coldValidPageCopies;
  } stat;

  uint64_t lastRefreshed;

  ErrorModeling errorModel;

  std::vector<bloom_filter> bloomFilters;
  uint64_t refresh_period;
  uint32_t background_ratio;

  Bitset insertedLayerCheck;
  Bitset insertedGroupCheck;
  std::vector< std::deque<uint32_t> > refreshQueues;
  std::vector< std::deque<uint32_t> > checkedQueues;
  
  std::ofstream refreshStatFile;

  // Hot cold seperation
  std::unordered_map<uint32_t, Block> hotPoolBlocks;
  std::unordered_map<uint32_t, Block> coldPoolBlocks;
  std::unordered_map<uint32_t, Block> coolDownBlocks;

  std::list<Block> hotFreeBlocks;
  std::list<Block> coldFreeBlocks;
  
  uint32_t nHotFreeBlocks;
  uint32_t nColdFreeBlocks;
  uint32_t nCooldownBlocks;
  uint32_t hotBlocksLimit;
  uint32_t coldBlocksLimit;
  float coldRatio;
  uint32_t cooldownIndex;

  std::deque<uint32_t> hotWindow;
  std::deque<uint32_t> coolDownWindow;

  std::vector<uint32_t> lastHotFreeBlock;
  std::vector<uint32_t> lastColdFreeBlock;
  std::vector<uint32_t> lastCoolFreeBlock;

  Bitset lastHotFreeBlockIOMap;
  Bitset lastColdFreeBlockIOMap;
  Bitset lastCoolFreeBlockIOMap;
  uint32_t lastHotFreeBlockIndex;
  uint32_t lastColdFreeBlockIndex;
  uint32_t lastCoolFreeBlockIndex;



  // Refresh
  void refresh_event(uint64_t);
  void setRefreshPeriod(uint32_t, uint32_t, uint32_t);
  void insertToQueue(uint32_t, uint32_t);
  void removeFromQueue(uint32_t);

  float freeBlockRatio();
  uint32_t convertBlockIdx(uint32_t);
  uint32_t getFreeBlock(uint32_t);
  uint32_t getLastFreeBlock(Bitset &);
  void calculateVictimWeight(std::vector<std::pair<uint32_t, float>> &,
                             const EVICT_POLICY, uint64_t);
  void selectVictimBlock(std::vector<uint32_t> &, uint64_t &, std::vector<uint32_t> &);
  void doGarbageCollection(std::vector<uint32_t> &, uint64_t &, bool);

  float calculateWearLeveling();
  void calculateTotalPages(uint64_t &, uint64_t &);

  void readInternal(Request &, uint64_t &);
  void writeInternal(Request &, uint64_t &, bool = true);
  void trimInternal(Request &, uint64_t &);
  void eraseInternal(PAL::Request &, uint64_t &);

  // Old refresh
  void doRefresh(std::vector<uint32_t> &, uint64_t &);
  void selectRefreshVictim(std::vector<uint32_t> &, uint64_t &);
  void calculateRefreshWeight(std::vector<std::pair<uint32_t, float>> &,
                            const REFRESH_POLICY, uint64_t);

  void refreshPage(uint32_t, uint64_t &);
  
  float calculateAverageError();

  // Hot cold seperation
  void sepWriteInternal(Request &, uint64_t &, bool = true);
  void sepHotWriteInternal(Request &, uint64_t &, bool = false);
  void sepEraseInternal(PAL::Request  &, uint64_t &);
  uint32_t getLastHotFreeBlock(Bitset &);
  uint32_t getLastColdFreeBlock(Bitset &);
  uint32_t getLastCoolFreeBlock(Bitset &);

  float hotFreeBlockRatio();
  float coldFreeBlockRatio();

  uint32_t getHotFreeBlock(uint32_t);
  uint32_t getColdFreeBlock(uint32_t, bool);

  void calculateColdVictimWeight(std::vector<std::pair<uint32_t, float>> &,
                             const EVICT_POLICY);
  void selectColdVictimBlock(std::vector<uint32_t> &, uint64_t &);
  void selectHotVictimBlock(std::vector<uint32_t> &, uint64_t &);

  void sepDoGarbageCollection(std::vector<uint32_t> &, uint64_t &, bool, blockPoolType);


 public:
  PageMapping(ConfigReader &, Parameter &, PAL::PAL *, DRAM::AbstractDRAM *);
  ~PageMapping();

  bool initialize() override;

  void read(Request &, uint64_t &) override;
  void write(Request &, uint64_t &) override;
  void trim(Request &, uint64_t &) override;

  void format(LPNRange &, uint64_t &) override;

  Status *getStatus(uint64_t, uint64_t) override;

  void getStatList(std::vector<Stats> &, std::string) override;
  void getStatValues(std::vector<double> &) override;
  void resetStatValues() override;
};

}  // namespace FTL

}  // namespace SimpleSSD

#endif
