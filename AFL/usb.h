#include <libusb.h>
#include <stdbool.h>

libusb_device_handle* initUSB(uint16_t idVendor, uint16_t idProduct);
void closeUSB(libusb_device_handle* );
bool sendReceiveHello(libusb_device_handle *devH);