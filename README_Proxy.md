# How to make
1. configurables:
    - p1: bms_pow2: power to 2 of the bit map size, default 16.
    - p2: max_afl_input: max input mutated by afl, default 1024, suggested: 512.

## Apply the patch

- `patch -p0 < afl_patch.diff`
- `patch -p0 < aflplusplus_patch.diff`
    - please ignore the error "File vanillaAFLplusplus/config.h is not a regular file -- refusing to patch"
    - as this file is just a symbolic link

## Make for AFL
- `cd vanillaAFL`
- ` bms_pow2=<p1> make` 
- `cd ../shift_proxy`
- `AFL=1 bms_pow2=<p1> usb_input_max=<p2> make`

## Make for AFLplusplus
- `cd vanillaAFLplusplus`
- ` bms_pow2=<p1> make` 
- `cd ../shift_proxy`
- `AFLplusplus=1 bms_pow2=<p1> usb_input_max=<p2> make`

# How to run

- configurables
    - timeout: suggest 5000, minimum 1000 to detect hangs for default configuration of AFL
    - baudrate: 9600 (does not take effect on the virtual serial port)
    - usb_channel_name: /dev/ttyACM1

- `./afl-fuzz -i in -o out -t <timeout> -- ./shift_proxy/afl-proxy -t <timeout> -c <usb_channel_name> -w <baud rate>`

## Note:
Before running execute the following as root:
```bash
su -
echo core >/proc/sys/kernel/core_pattern 
cd /sys/devices/system/cpu
echo performance | tee cpu*/cpufreq/scaling_governor

```
