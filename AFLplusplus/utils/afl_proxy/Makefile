all:	afl-proxy

ifdef bms_pow2
    CFLAGS ?= -DMAP_SIZE_POW2_CUSTOM=$(bms_pow2)
else
    CFLAGS ?= 
endif

ifdef usb_input_max
    CFLAGS += -DINPUT_MAX_LEN=$(usb_input_max)
endif


afl-proxy:	afl-proxy.c
	$(CC) $(CFLAGS) -I../../include -o afl-proxy afl-proxy.c

clean:
	rm -f afl-proxy *~ core
