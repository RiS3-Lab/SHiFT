#!/usr/bin/env python3


import serial
import subprocess, signal, time
import argparse, os
from sys import version_info
'''
 
 usage: FuzzerBBcollector.py [-h] -s1 SERIAL -b1 BAUD -s2 SERIALBB -b2 BAUDBB -o OUT -t TTIME
 
 Example:
 ./FuzzerBBcollector.py -s1 /dev/ttyACM1 -b1 115200 -s2 /dev/ttyACM0 -b2 7500000 -o ../FuzzingCampaigns/Synthetic1 -t 86400

 '''

def resetBoard(conf):
    from pyocd.core.helpers import ConnectHelper
    from pyocd.core.target import Target
    from pyocd.debug.elf.symbols import ELFSymbolProvider
    import yaml
    # use the following line  when no pyocd.yaml is in the current folder
    #session = ConnectHelper.session_with_chosen_probe(unique_id = "0668FF323239524257253610", options = {"frequency": 8000000, "target_override": "stm32l552zetxq"})
    # use the following line when a yocd.yaml is in the current folder
    #session = ConnectHelper.session_with_chosen_probe()
    with open(conf, 'r') as file:
        conf = yaml.safe_load(file)

    probes = conf['probes']
    u_id=list(probes.keys())[0]
    opts=probes[u_id]
    opts['frequency'] = conf['frequency']
    
    print(opts)
    print(u_id)
    exit
    session = ConnectHelper.session_with_chosen_probe(unique_id = str(u_id) , options = opts)
    session.open()
    target = session.target
    target.reset()


# Set here how many seconds are we going to fuzz test firmware
totalseconds = 24*3600
# the file to save the basic blocks
plot_data = 'plot_dataBB'
acc_time_name = 'acc_time'
timestart = 0


def saveBBs(bbs):

    with open(args.out + plot_data, 'a') as f:
        for b in bbs.items():
            print(b)
            f.write('{} {} \n'.format(b[1],b[0]))


def resume_session():
    assert(os.path.exists(args.out))
    plot_dataBB_file = os.path.join(args.out,plot_data)
    acc_time_file = os.path.join(args.out, acc_time_name)
    assert(os.path.exists(plot_dataBB_file))
    assert(os.path.exists(acc_time_file))
    old_BBs = {}
    acc_time = 0
    with open(acc_time_file,'r') as rfile:
        acc_time = int(rfile.readlines()[0].strip().split(':')[1].strip(),10)
    with open(plot_dataBB_file,"r") as rfile:
        for it, each_line in enumerate(rfile.readlines()):
            t ,bb = each_line.strip().split(' ')
            t, bb = int(t.strip(),10), bb.strip()
            old_BBs[bb] = t

    assert(acc_time != 0)
    return acc_time, old_BBs

def record_time(filename, old_time, launch_time):

    acc_time = old_time + int(time.time()) - launch_time
    with open(filename,"w") as rfile:
        rfile.write("acc_time:{}\n".format(acc_time))

if __name__ == "__main__":  # confirms that the code is under main function
    parser = argparse.ArgumentParser()
    parser.add_argument("-s1","--serial", type=str,required=True, help="Serial port for fuzzing")
    parser.add_argument("-b1","--baud", type=int,required=True, help="Baud rate for fuzzing")
    parser.add_argument("-s2","--serialBB", type=str,required=True, help="Serial port for collecting BB")
    parser.add_argument("-b2","--baudBB", type=int,required=True, help="Baud rate for collecting BB")
    parser.add_argument("-o","--out", type=str,required=True, help="out folder fuzzing")
    parser.add_argument("-t","--ttime", type=int,required=True, help="Total seconds for fuzzing campaign")
    parser.add_argument('-e','--error_file', type=str, help="file to output the error message",default="error.txt")
    parser.add_argument('-c', '--cont', action=argparse.BooleanOptionalAction, help="whether to resume the last interrupted session",default=False)
    parser.add_argument('-p', '--pconf', type=str,required=False, help="PyOCD configuration file to reset the board",default=None)

    args = parser.parse_args()
    if(version_info.major != 3):
        print("please use python3")
        exit(1)
    if(version_info.minor <= 9):
        print("please use python 3.9 and above")
        exit(1)
   
    
    # set here the serialport to get the BBs
    #ser = serial.Serial('/dev/ttyACM0', baudrate=7500000, timeout = None)
    ser = serial.Serial(args.serialBB, baudrate=args.baudBB, timeout = 10)
  
    procAFL = ''
    bbs={}
    
    timestart = int(time.time())
    timeend = int(timestart + args.ttime)

    print('Fuzzing for {} seconds'.format(args.ttime))
    
    
    try:
        if args.pconf:
            resetBoard(args.pconf)
            time.sleep(3)


        os.makedirs(args.out, exist_ok=True) 
        # command to run AFL with proxy: set here the serialport for fuzztesting
        #cmd_aflpp = ['../vanillaAFLplusplus/afl-fuzz', '-i', '../vanillaAFLplusplus/in', '-o', args.out ,'-t', '1000', '--','../shift_proxy/afl-proxy','-t', '1000', '-c', args.serial, '-w', str(args.baud) ]
        #cmd_aflpp = ['../vanillaAFL/afl-fuzz', '-i', '../vanillaAFL/in', '-o', args.out ,'-t', '1000', '--','../shift_proxy/afl-proxy','-t', '1000', '-c', args.serial, '-w', str(args.baud) ]
        # AFL_SKIP_CPUFREQ=1 AFL_NO_FORKSRV=1 ./afl-fuzz -c /dev/ttyACM1 -w 9600 -t 5000 -i ./in -o ./test/out 2>err.txt
        my_env = os.environ.copy()
        my_env["AFL_SKIP_CPUFREQ"]='1'
        my_env["AFL_NO_FORKSRV"]='1'
        in_file = "../AFL/in"
        old_time = 0
        old_bbs = {}
        if args.cont :
            in_file = '-'
            old_time, old_bbs = resume_session()
            timeend -= old_time
        cmd_aflpp = [  '../AFL/afl-fuzz',  '-c', args.serial, '-w', str(args.baud), '-t', '5000', '-i', in_file, '-o',args.out ]
        # launch AFL in a subprocess
        plot_dataBB_file = os.path.join(args.out,plot_data)
        acc_time_file = os.path.join(args.out, acc_time_name)
        err_file = open(args.error_file,"w")
        procAFL = subprocess.Popen(cmd_aflpp, env = my_env,stderr=err_file)
        
      
        while( True ):
            if (int(time.time()) > timeend):
                break
            
            line = str(ser.readline().decode(errors='ignore'))
            if len(line)==10 and  line[0] == '#':
                bb ='0x'+line[1:9]
                if bb not in bbs and bb not in old_bbs:
                    t = int(time.time() - timestart) + old_time
                    bbs[bb] = t
                    with open(plot_dataBB_file, 'a') as f:
                        f.write('{} {} \n'.format(t,bb))
                    record_time(acc_time_file, old_time,timestart)

        ser.close()
        # terminate AFL
        procAFL.send_signal(signal.SIGINT)
        # wait till AFL terminates
        procAFL.wait()
        print(bbs)
        record_time(acc_time_file, old_time,timestart)
        #saveBBs(bbs)
    except KeyboardInterrupt:
        # terminate AFL
        procAFL.send_signal(signal.SIGINT)
        # wait till AFL terminates
        procAFL.wait()
        record_time(acc_time_file, old_time,timestart)
        print(bbs)
        #saveBBs(bbs)
        ser.close()
        exit(0)



