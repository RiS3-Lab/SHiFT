## command to make
`usb_input_max=512 bms_pow2=16 make`
optionally: 
- if you want to generate profile data add `PROFILE=1` at the front in addition to the original make
## command to run 
expain:
- don't launch forkserver
- the physical baudrate is 9600(if there is any)
- the timeout for reading from the MCU is 5000ms
AFL_NO_FORKSRV=1 ./afl-fuzz -c /dev/ttyACM1 -w 9600 -t 5000 -i ./test/in -o ./test/out 2>err.txt

## to observe output from the firmware
screen /dev/ttyACM0 115200 

## noticable modification to AFL	
- No fork server: for obvious reason
- Max input len from 1MB to 2KB

## fuzzing multiple boards:
AFL_SKIP_CPUFREQ=1 AFL_NO_FORKSRV=1 ./afl-fuzz -c /dev/ttyACM1 -i ./test/in -o ./test/out_sync -M f1 2>err_f1.txt
AFL_SKIP_CPUFREQ=1 AFL_NO_FORKSRV=1 ./afl-fuzz -c /dev/ttyACM3 -i ./test/in -o ./test/out_sync -S f2 2>err_f2.txt

### Checkout the combined speed:
./afl-whatsup


## Configurable parameters but not exposed

- serial port related:
    -. Retry:
        -. sleep time after each retry:
            protocol.c, func retry, line 1
        -. number of retry attemps:
            protocol.c, line 32
    - timeout for writing:
        serialport.c, line 21
    - timeout for reading from serial port:
        serialport.c, line 22
    