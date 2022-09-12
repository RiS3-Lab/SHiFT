# Folder content details

## ->Common
Contains common code for the communication protocol, test (toy programs),
FreeRTOS-Kernel. It is  used by single and dual core fuzzers detailed below.


## ->USBCDCH743FUZZER and ->USBCDCH745FUZZER
Single core fuzzer, it supports:
- Thread management for killing and spawning target threads
- Memfault trap to handle MPU violations
- Speed issue solved  adjusting clock configuration at 480Mhz on all peripherals
- Dual compilation with and without instrumentation for
clang and gcc, respectively.


## ->USBCDCH745FUZZDC
This is the dual core fuzzer:
M7 is the fuzzer and M4 is the target
I will add details soon it is work in progress


## ->AddressSanitizerH743
working example of address sanitizer with GCC,
based on the following blog post:
https://mcuoneclipse.com/2021/05/31/finding-memory-bugs-with-google-address-sanitizer-asan-on-microcontrollers/



## -> EVALUSARTCHANNEL
Toy firmware to test the spped of the communication channel through  PC->(ST-Link->USB-USART)->(USART)->MCU
Only the CM7 is working in this test

## -> EVALUSBCHANNEL
Toy firmware to test the spped of the communication channel through  PC->(USB-USART)->MCU
Only the CM7 is working in this test

the preliminary results are at:

https://docs.google.com/spreadsheets/d/1zPdFxDGfl9xJw9QjMdAPlQPV2mh-CSHKNFcSvX6Ndos/edit?usp=sharing


## ->Coremark*
all of these folders contains projects for the coremark benchmark

## ->ETMtestH743 (deprecated)
test of the ETM hardware tracing module, not used anymore but very 
interesting for future research of binary only tracing


## ->USBCDCH743 and ->USBCDCH745 (deprecated)
Basic fuzzers with no memfault traps or thread management
these fuzzers where mostly used to test the communication protocol
- Dual compilation with and without instrumentation for 
clang and gcc, respectively.


## Templates
-  Template-USBCDCH745FUZZER
-  Template-USBCDCH743FUZZER
-  Template-USBCDCH745FUZZDC


##  Ported firmwares:

### USBCDCH745FUZZERModBus

- Working nice and sweet.
- All BoF are identified.

### USBCDCH745FUZZERlwgsm

- Not working
- it has many static global variables used by individual .c file. These static globals are not aggregated into the global region.
- in its intialization routine, it created 2 threads, upon creating these threads, a Mem error is triggered.

### USBCDCH745FUZZERModBus

- Working
- For bug detection, in order to grant access to the _global_locale, we gave more than necessary areas to the target, and I've fuzzed no-stop for 3 hours, no bugs is found.

## Trouble shooting:

- if you have multiple errors reported not from your code but from the drivers and libraries, and these errors look like broken dependencies e.g., undefined references to some library functions. You should open the .ioc file and did some dummy change e.g., change the baudrate of a virtual serial port since it does not matter(you can change it and then change it back), and when the IDE promots "do you want to generate the code", press yes. The IDE will refresh the dependencies and generate links for you to get back those broken library dependencies.
