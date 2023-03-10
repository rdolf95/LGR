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

#ifndef __FTL_CONFIG__
#define __FTL_CONFIG__

#include "sim/base_config.hh"

namespace SimpleSSD {

namespace FTL {

typedef enum {
  /* Common FTL configuration */
  FTL_MAPPING_MODE,
  FTL_OVERPROVISION_RATIO,
  FTL_GC_THRESHOLD_RATIO,
  FTL_BAD_BLOCK_THRESHOLD,
  FTL_FILLING_MODE,
  FTL_FILL_RATIO,
  FTL_INVALID_PAGE_RATIO,
  FTL_GC_MODE,
  FTL_GC_RECLAIM_BLOCK,
  FTL_GC_RECLAIM_THRESHOLD,
  FTL_GC_EVICT_POLICY,
  FTL_GC_D_CHOICE_PARAM,
  FTL_USE_RANDOM_IO_TWEAK,

  /* Refresh configuration*/
  FTL_REFRESH_POLICY,
  FTL_REFRESH_THRESHOLD,
  FTL_REFRESH_PERIOD,
  FTL_REFRESH_FILTER_NUM,
  FTL_REFRESH_FILTER_SIZE,
  FTL_REFRESH_MODE,
  FTL_REFRESH_MAX_LAYER_NUM,
  FTL_REFRESH_MAX_RBER,
  FTL_GC_RECO_PARAM,
  FTL_REFRESH_GROUPING_SIZE,

  /*Initial configuration for experiment*/
  FTL_INITIAL_ERASE_COUNT,

  /* Error modeling configuration */
  FTL_TEMPERATURE,
  FTL_EPSILON,
  FTL_ALPHA,
  FTL_BETA,
  FTL_GAMMA,
  FTL_KTERM,
  FTL_MTERM,
  FTL_NTERM,
  FTL_ERROR_SIGMA,
  FTL_RANDOM_SEED,

  /* N+K Mapping configuration*/
  FTL_NKMAP_N,
  FTL_NKMAP_K,

  FTL_HOT_COLD_SEPERATION,
  FTL_HOT_BLOCK_RATIO,
  FTL_COOL_DOWN_WINDOW_SIZE,
} FTL_CONFIG;

typedef enum {
  PAGE_MAPPING,
} MAPPING;

typedef enum {
  GC_MODE_0,  // Reclaim fixed number of blocks
  GC_MODE_1,  // Reclaim blocks until threshold
} GC_MODE;

typedef enum {
  FILLING_MODE_0,
  FILLING_MODE_1,
  FILLING_MODE_2,
} FILLING_MODE;

typedef enum {
  POLICY_GREEDY,  // Select the block with the least valid pages
  POLICY_COST_BENEFIT,
  POLICY_RANDOM,  // Select the block randomly
  POLICY_DCHOICE,
  POLICY_RECO,    // Refresh considering
} EVICT_POLICY;

typedef enum {
  POLICY_NONE,
} REFRESH_POLICY;

class Config : public BaseConfig {
 private:
  MAPPING mapping;              //!< Default: PAGE_MAPPING
  float overProvision;          //!< Default: 0.25 (25%)
  float gcThreshold;            //!< Default: 0.05 (5%)
  uint64_t badBlockThreshold;   //!< Default: 100000
  FILLING_MODE fillingMode;     //!< Default: FILLING_MODE_0
  float fillingRatio;           //!< Default: 0.0 (0%)
  float invalidRatio;           //!< Default: 0.0 (0%)
  uint64_t reclaimBlock;        //!< Default: 1
  float reclaimThreshold;       //!< Default: 0.1 (10%)
  GC_MODE gcMode;               //!< Default: FTL_GC_MODE_0
  EVICT_POLICY evictPolicy;     //!< Default: POLICY_GREEDY
  uint64_t dChoiceParam;        //!< Default: 3
  bool randomIOTweak;           //!< Default: true

  REFRESH_POLICY refreshPolicy; //!< Default: POLICY_NONE
  uint64_t refreshThreshold;    //!< Default: 10000000
  uint64_t refreshPeriod;       //!< Default: 0
  uint32_t refreshFilterNum;    //!< Default: 10
  uint32_t refreshFilterSize;   //!< Default: 0
  uint32_t refreshMode;         //!< Default: 0
  uint32_t refreshMaxLayerNum;  //!< Default: 100000
  uint32_t refreshGroupingSize; //!< Default: 3

  uint32_t randomSeed;          //!< Default: 0
  float temperature;            //!< Default: 25
  float epsilon;                //!< Default: 0.0000006175
  float alpha;                  //!< Default: 0.00006636
  float beta;                   //!< Default: 0.02416
  float gamma;                  //!< Default: 0.0000328
  float kTerm;                  //!< Default: -4.110
  float mTerm;
  float nTerm;
  float errorSigma;             //!< Default: 2
  float refreshMaxRBER;         //!< Default: 0.00018
  uint32_t initEraseCount;      //!< Default : 0
  float recoGCParam;            //!< Default : 0.2
  
  uint32_t hotColdSeperation;   //!< Default: 0 (disabled)
  float hotBlocksRatio;         //!< Default : 0.1
  uint32_t coolDownWindowSize;  //!< Default : 64

 public:
  Config();

  bool setConfig(const char *, const char *) override;
  void update() override;

  int64_t readInt(uint32_t) override;
  uint64_t readUint(uint32_t) override;
  float readFloat(uint32_t) override;
  bool readBoolean(uint32_t) override;
};

}  // namespace FTL

}  // namespace SimpleSSD

#endif
