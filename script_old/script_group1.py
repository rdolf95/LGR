from distutils.command.config import config
from genericpath import isdir
from posixpath import dirname
import subprocess
import os
from sys import argv
#out=subprocess.check_output('ls')
def execute(trace):
    simulator_config = [(trace + "_3000_50.cfg"), (trace + "_5000_50.cfg")]
    ssd_config = [("temp50_pe3000_reco0.5.cfg"), ("temp50_pe5000.cfg")]

    for i in range(len(simulator_config)):
        print('./config/' + simulator_config[i], './simplessd/config/' + ssd_config[i])
        subprocess.run(['./simplessd-standalone','./config/' + simulator_config[i], './simplessd/config/' + ssd_config[i], './log'])
        #output_file = open('test_output.txt', "at")
        #output_file.write("####################### " + simulator_config[i] + " #################################\n")
        #output_file.write(out.decode('ascii'))
        #output_file.write("####################### " + "simulation " + str(i+1) + "/" + str(len(simulator_config)) + " ended" + " #################################\n\n")
        #output_file.close()

def execute_with(simulator, trace, ssd_config, temperature, peCycle, others):
    if others != "" :
        dir_name = './log' + '/temp' + temperature + '/PE' +  peCycle + '/' + others + '/' + trace
    else :
        dir_name = './log' + '/temp' + temperature + '/PE' +  peCycle + '/' + trace

    if(not os.path.isdir(dir_name)):
        os.makedirs(dir_name)

    subprocess.run([simulator,'./config/' + trace + '.cfg', './simplessd/config/' + ssd_config, dir_name])



#execute (argv[1])
# argv[1] : trace name
# argv[2] : PE cycle
#grouping_size = ["3", "7"]
#for i in range(len(grouping_size)):

print("########################################################################################")
print("Trace : " + argv[1] + " temperature : 25, PE : 3000")
print("########################################################################################")
trace = argv[1]
ssd_config = "temp25_pe" + "3000" + "_group1.cfg"
others = "group1"
execute_with("./simplessd-standalone", trace, ssd_config, "25", "3000", others)
print("########################################################################################")
print()

print("########################################################################################")
print("Trace : " + argv[1] + " temperature : 25, PE : 5000")
print("########################################################################################")
trace = argv[1]
ssd_config = "temp25_pe" + "5000" + "_group1.cfg"
others = "group1"
execute_with("./simplessd-standalone", trace, ssd_config, "25", "5000", others)
print("########################################################################################")
print()

'''
print("########################################################################################")
print("Trace : " + argv[1] + " temperature : 25, PE : " + argv[3])
print("########################################################################################")
trace = argv[1]
ssd_config = "temp25_pe" + argv[3] + ".cfg"
others = ""
execute_with("./simplessd-standalone", trace, ssd_config, "25", argv[3], others)
print("########################################################################################")
print()

print("########################################################################################")
print("Trace : " + argv[2] + " temperature : 25, PE : " + argv[3])
print("########################################################################################")
trace = argv[2]
ssd_config = "temp25_pe" + argv[3] + ".cfg"
others = ""
execute_with("./simplessd-standalone", trace, ssd_config, "25", argv[3], others)
print("########################################################################################")
print()
'''
'''
for i in range(len(recoWeight)):
    print("########################################################################################")
    print("temperature : 50, PE : " + argv[2] + ", reco : " + recoWeight[i] )
    print("########################################################################################")
    trace = argv[1]
    ssd_config = "temp50_pe" + argv[2] + "_reco" +  recoWeight[i] + ".cfg"
    others = "reco" + recoWeight[i]
    execute_with("./simplessd-standalone", trace, ssd_config, "50", argv[2], others)
    print("########################################################################################")
    print()
'''


#execute_with("./simplessd-standalone", argv[1] + ".cfg", "temp25_" + argv[2] + "reco0.2" + ".cfg")
#execute_with("./simplessd-standalone", argv[1] + ".cfg", "temp25_" + argv[2] + "reco0.5" + ".cfg")

#execute_with("./simplessd-standalone", argv[1] + ".cfg", "temp50_" + argv[2] + "reco0.1" + ".cfg")
#execute_with("./simplessd-standalone", argv[1] + ".cfg", "temp50_" + argv[2] + "reco0.2" + ".cfg")
#execute_with("./simplessd-standalone", argv[1] + ".cfg", "temp50_" + argv[2] + "reco0.5" + ".cfg")
