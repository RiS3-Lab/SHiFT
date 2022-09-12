#include "usb.h"
#include <stdio.h>
#include <stdlib.h>

const int USB_ENDPOINT_OUT = 0x01;
const int USB_ENDPOINT_IN  = 0x82;
const int USB_TIMEOUT      = 5000;
const int USB_INTERFACE_NUM = 0;
const int PACKAGE_LIMIT = 64;

libusb_device_handle* initUSB(uint16_t idVendor, uint16_t idProduct)
{
	if(libusb_init(NULL))
	{
		fprintf(stderr, "libusb init failed.\n");
		return NULL;
	}
	libusb_device **list;
	ssize_t num = libusb_get_device_list(NULL, &list);
	if(num < 0)
	{
		fprintf(stderr, "Failed to get device list.\n");
		return NULL;
	}

	libusb_device_handle *devH = NULL;
	for(uint32_t i = 0; i < num; i++)
	{
		struct libusb_device_descriptor desc;
		if(libusb_get_device_descriptor(list[i], &desc) < 0)
		{
			fprintf(stderr, "Failed to get device descriptor.\n");
			libusb_free_device_list(list, 1);
			return devH;
		}

		if(desc.idVendor == idVendor && desc.idProduct == idProduct)
		{
			if(libusb_open(list[i], &devH)) fprintf(stderr, "Failed to open device.\n");
			else
			{
				if(libusb_set_configuration(devH, 1))
				{
					fprintf(stderr, "Failed to set configuration\n");
					libusb_close(devH);
					devH = NULL;
				}
			}
			break;
		}
	}
	libusb_free_device_list(list, 1);

	if(libusb_claim_interface(devH, USB_INTERFACE_NUM))
	{
		fprintf(stderr, "Failed to claim interface 0.\n");
		libusb_close(devH);
		libusb_exit(NULL);
		return NULL;
	}

	return devH;
}

void closeUSB(libusb_device_handle* dev){
	libusb_release_interface(dev, USB_INTERFACE_NUM);
	libusb_close(dev);
	libusb_exit(NULL);
}

bool sendData(libusb_device_handle * dev_h, uint8_t * buf, int len){
	int transferred;
	int len_to_send;
	while(true){
		len_to_send = len > PACKAGE_LIMIT ? PACKAGE_LIMIT : len;
		if(libusb_bulk_transfer(dev_h, USB_ENDPOINT_OUT, buf, len_to_send, &transferred, USB_TIMEOUT))
		{
			fprintf(stderr, "Failed to send data.\n");
			return false;
		}
		if (transferred != len_to_send){
			fprintf(stderr, "attempt to send %d, sent % instead", len_to_send, transferred);
			return false;
		}
		buf = buf + len_to_send;
		len = len - len_to_send;
	}
	return true;
}

uint8_t * receiveData(libusb_device_handle * dev_h, int * buf_len){
	int buf_sz = sizeof(uint8_t) * PACKAGE_LIMIT;
	uint8_t * buf = (uint8_t *)malloc(buf_sz);
	int transferred;
	while (true){
		if(libusb_bulk_transfer(dev_h, USB_ENDPOINT_IN, buf, PACKAGE_LIMIT, &transferred, USB_TIMEOUT))
		{
			fprintf(stderr, "Failed to receive data.\n");
			*buf_len = 0;
			return NULL;
		}
		if(transferred < PACKAGE_LIMIT){
			break;
		}else{
			// expand the buf
			buf_sz += sizeof(uint8_t) * PACKAGE_LIMIT;
			buf = (uint8_t *)realloc(buf, buf_sz);
		}
	}
	*buf_len = buf_sz;
	return buf;
}
