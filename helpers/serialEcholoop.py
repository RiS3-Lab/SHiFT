#!/usr/bin/env python3
import os
import sys

def main(argv):
    testnumber=int(argv[1])
    i=1
    while(testnumber):
        print("\nEXEC No: {}".format(i))
        os.system("./serialEchoProtocol.py "+argv[0])
        testnumber-=1
        i+=1

if __name__ == "__main__":
   main(sys.argv[1:])
