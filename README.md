# SHiFT
SHiFT: Semi-hosted Fuzz Testing for Embedded Applications

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
