#!/usr/bin/env python3

#from multiprocessing import Process
#from multiprocessing import Queue
import serial
import subprocess, signal, time

# Set here how many seconds are we going to fuzz test firmware
totalseconds = 24*3600
# the file to save the basic blocks
plot_data = './plot_data'



def saveBBs(bbs):

    with open(plot_data, 'a') as f:
        for b in bbs.items():
            print(b)
            f.write('{} {} \n'.format(b[1],b[0]))




if __name__ == "__main__":  # confirms that the code is under main function
    
   
    
    # set here the serialport to get the BBs
    ser = serial.Serial('/dev/ttyACM0', baudrate=7500000, timeout = None)
    procAFL = ''
    bbs={}

    timestart = int(time.time()) 
    
    
    try:
      
        # command to run AFL with proxy: set here the serialport for fuzztesting
        cmd_aflpp = ['./afl-fuzz', '-i', 'in', '-o', 'out' ,'-t', '1000', '--','../shift_proxy/afl-proxy','-t', '1000', '-c', '/dev/ttyACM1', '-w', '115200']
        # launch AFL in a subprocess
        procAFL = subprocess.Popen(cmd_aflpp)
                
        while( int(time.time()) - timestart < totalseconds ):
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



