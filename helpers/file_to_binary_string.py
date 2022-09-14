#!/usr/bin/env python3
import os
import argparse
from IPython import embed
parser = argparse.ArgumentParser()
parser.add_argument("-i","--input_dir", type=str,required=True, help="path to afl out dir")
parser.add_argument("-o","--out_file", type=str,default="./crash_inputs.txt", help="output file name")

args = parser.parse_args()

def main():
    if not os.path.exists(args.input_dir):
        print("{} does not exist")
        exit(-1)
    crash_dir = os.path.join(args.input_dir,"crashes")
    if not os.path.exists(crash_dir):
        print("no `crashes` folder found under the given directory")
        exit(-1)
    with open(args.out_file,"w") as wfile:
        for each_crash_input in os.listdir(crash_dir):
            if("README" in each_crash_input):
                continue
            filename = os.path.join(crash_dir,each_crash_input)
            with open(filename,"rb") as rfile:
                buf = rfile.read()
                wfile.write("{}\n".format(str(buf)))
if __name__ == '__main__':
    main()
