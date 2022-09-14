#!/usr/bin/env python3
import os
import sys
import random

def main(argv):
    testnumber=int(argv[0])
    
    while(testnumber):
        r = random.randint(0,11)
        print("\nEXEC No: {}".format(r))
        os.system("./serialEchoProtocol.py "+ str(r))
        testnumber-=1
        

if __name__ == "__main__":
   main(sys.argv[1:])
