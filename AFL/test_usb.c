#include "usb.h"
#include "stdio.h"

const int VENDOR_ID  = 0xCAFE;
const int PRODUCT_ID = 0x4010;

int 
main(void){
    libusb_device_handle * dev_h = initUSB(VENDOR_ID, PRODUCT_ID);
    if (dev_h == NULL){
        printf("Connecting to USB Fail");
    }
    closeUSB(dev_h);
}