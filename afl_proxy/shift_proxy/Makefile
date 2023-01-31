all:	afl-proxy

SerialPortCFLAGS = $(shell  pkg-config --cflags libserialport)
SerialPortLIBS = $(shell pkg-config --libs libserialport)
ProtocolCFLAGS = -DMAX_LEN_INPUT_PAYLOAD=$(usb_input_max)

ifdef PROFILE
	ProtocolCFLAGS += -DMEASSURE_TIME
endif

ifdef bms_pow2
    CFLAGS ?= -DMAP_SIZE_POW2_CUSTOM=$(bms_pow2)
else
    CFLAGS ?= 
endif

ifdef usb_input_max
    CFLAGS += -DINPUT_MAX_LEN=$(usb_input_max)
endif

CFLAGS += -I..

serialport.o: serialport.c serialport.h
	$(CC) $(CFLAGS) $(SerialPortCFLAGS) -c -g serialport.c 

protocol.o: protocol.c protocol.h serialport.h
	$(CC) $(CFLAGS) $(ProtocolCFLAGS) -c -g protocol.c 

afl-proxy: afl-proxy.c serialport.o protocol.o 
	$(CC) $(CFLAGS) -g -o afl-proxy afl-proxy.c protocol.o serialport.o  $(LDFLAGS) $(SerialPortLIBS)

clean:
	rm -f afl-proxy *~ core
	rm *.o
