from distutils.command.config import config
from genericpath import isdir
from posixpath import dirname
import subprocess
import os
from sys import argv
from sys import stdout

def execute_with(simulator, trace, ssd_config, temperature, peCycle, others):
    if others != "" :
        dir_name = './log' + '/PE' +  peCycle + '/' + others
    else :
        dir_name = './log' + '/PE' +  peCycle

    if(not os.path.isdir(dir_name)):
        os.makedirs(dir_name)

    subprocess.run([simulator,'./config/selected/' + trace + '.cfg', './simplessd/config/' + ssd_config, dir_name])



#execute (argv[1])
# argv[1] : trace name
# argv[2] : PE cycle
#grouping_size = ["3", "7"]
#for i in range(len(grouping_size)):

## Usage : python3 script_ali.py {trace1} {trace2} ... {peCycle}

len_argv = len(argv)
peCycle = argv[len_argv - 1]
for i in range (1, len_argv - 1):
    trace = argv[i]
    print("########################################################################################")
    print("Trace : " + trace + ", temperature : 25, PE : " + peCycle)
    print("########################################################################################")
    stdout.flush()
    ssd_config = "alibaba_pe" + peCycle + ".cfg"      ## days config
    others = "selected/vanila"
    execute_with("./simplessd-standalone", trace, ssd_config, "25", peCycle, others)
    print("########################################################################################")
    print()
