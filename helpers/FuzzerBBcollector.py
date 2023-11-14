#!/usr/bin/env python3


import serial
import subprocess, signal, time
import argparse

'''
 
 usage: FuzzerBBcollector.py [-h] -s1 SERIAL -b1 BAUD -s2 SERIALBB -b2 BAUDBB -o OUT -t TTIME
 
 Example:
 ./FuzzerBBcollector.py -s1 /dev/ttyACM1 -b1 115200 -s2 /dev/ttyACM0 -b2 7500000 -o ../FuzzingCampaigns/Synthetic1 -t 86400

 '''





# Set here how many seconds are we going to fuzz test firmware
totalseconds = 24*3600
# the file to save the basic blocks
plot_data = '/plot_dataBB'



def saveBBs(bbs):

    with open(args.out + plot_data, 'a') as f:
        for b in bbs.items():
            print(b)
            f.write('{} {} \n'.format(b[1],b[0]))




if __name__ == "__main__":  # confirms that the code is under main function
    parser = argparse.ArgumentParser()
    parser.add_argument("-s1","--serial", type=str,required=True, help="Serial port for fuzzing")
    parser.add_argument("-b1","--baud", type=int,required=True, help="Baud rate for fuzzing")
    parser.add_argument("-s2","--serialBB", type=str,required=True, help="Serial port for collecting BB")
    parser.add_argument("-b2","--baudBB", type=int,required=True, help="Baud rate for collecting BB")
    parser.add_argument("-o","--out", type=str,required=True, help="out folder fuzzing")
    parser.add_argument("-t","--ttime", type=int,required=True, help="Total seconds for fuzzing campaign")
    args = parser.parse_args()    
   
    
    # set here the serialport to get the BBs
    #ser = serial.Serial('/dev/ttyACM0', baudrate=7500000, timeout = None)
    ser = serial.Serial(args.serialBB, baudrate=args.baudBB, timeout = None)
  
    procAFL = ''
    bbs={}

    timestart = int(time.time()) 
    
    
    try:
      
        # command to run AFL with proxy: set here the serialport for fuzztesting
        cmd_aflpp = ['../vanillaAFLplusplus/afl-fuzz', '-i', '../vanillaAFLplusplus/in', '-o', args.out ,'-t', '1000', '--','../shift_proxy/afl-proxy','-t', '1000', '-c', args.serial, '-w', str(args.baud) ]
        # launch AFL in a subprocess
        procAFL = subprocess.Popen(cmd_aflpp)
                
        while( int(time.time()) - timestart < args.ttime ):
            line = str(ser.readline().decode())
            if line[0] == '#':
            #i-=1
            
                bb ='0x'+line[1:9]
                if bb not in bbs:
                    bbs[bb] = int(time.time() - timestart) 
       
        # terminate AFL
        procAFL.send_signal(signal.SIGINT)
        # wait till AFL terminates
        procAFL.wait()
        print(bbs)
        saveBBs(bbs)


                      

    except KeyboardInterrupt:
        # terminate AFL
        procAFL.send_signal(signal.SIGINT)
        # wait till AFL terminates
        procAFL.wait()
        print(bbs)
        saveBBs(bbs)
        #ser.close()
        exit(0)



