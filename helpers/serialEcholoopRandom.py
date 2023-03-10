#!/usr/bin/env python3
import os
import sys, signal
import random


def main(argv):
    testnumber=int(argv[0])
    try:

        while(testnumber>0):
            r = random.randint(0,11)
            print("\nEXEC Input No.: {}, Remaining: {}".format(r,testnumber))
            os.system("./serialEchoProtocol.py "+ str(r))
            testnumber-=1
    except KeyboardInterrupt:
        print('Interrupted!')
        

def signaL_handler(signal, frame):
    print("\nInterrupted")

if __name__ == "__main__":
   signal.signal(signal.SIGINT, signaL_handler)
   main(sys.argv[1:])
