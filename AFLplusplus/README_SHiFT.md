# How to make
1. configurables:
    - p1: bms_pow2: power to 2 of the bit map size, default 16.
    - p2: max_afl_input: max input mutated by afl, default 1024, suggested: 512.
- `bms_pow2=<p1> make` 
- `cd util/afl_proxy`
- `bms_pow2=<p1> usb_input_max=<p2> make`

# How to run

- `afl-fuzz -G <p2>`