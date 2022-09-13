# SHiFT
SHiFT: Semi-hosted Fuzz Testing for Embedded Applications

## Compiling AFL for serial port
- Example 

> usb_input_max=512 bms_pow2=16 make

1.  *usb_input_max* speficifies the maximum length of mutated input AFL should send to the MCU
2.  *bms_pow2* specifies the bitmap size used by AFL, e.g., 16 means 65535 bytes

optionally:
- if you want to generate profile data add `PROFILE=1` at the front in addition to the original make

## Run AFL with serial port
- Example

> AFL_NO_FORKSRV=1 ./afl-fuzz -c /dev/ttyACM1 -w 9600 -t 5000 -i ./test/in -o ./test/out 2>err.txt

1. *AFL_NO_FORKSRV=1* since we don't need the forkserver
2. *-c* specifies the device file name for the serial port to use
3. *-w* specifies the baud rate for the serial port, if it needs to be set.
4. *-t* timeout in ms, specifies how much time to wait before deciding the MCU is dead
5. it's good practice to write the stderr to a file, since the error information can be useful



## AFL working with serial port
In original AFL, each fuzzing iteration comprises of 
1. writing the current mutated input to a file 
2. execute the target (which is programmed to receive input from the file)

As in SHiFT's case, step 1 is replaced with sending the mutated input through the serial port which is [here](https://github.com/RiS3-Lab/SHiFT/blob/main/AFL/afl-fuzz.c#L2484).

And step 2 is replaced with waiting for the MCU to send back the feedback which is 
[here](https://github.com/RiS3-Lab/SHiFT/blob/main/AFL/afl-fuzz.c#L2403)

Since the coverage feedback sent back from the MCU are in pairs of hit edges, 
instead of reconstructing a bitmap, we direct use these pairs to find interesting edges, saving us some time.
This part is [here](https://github.com/RiS3-Lab/SHiFT/blob/main/AFL/afl-fuzz.c#L996)
