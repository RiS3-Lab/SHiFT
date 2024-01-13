#include <atmel_start.h>
#include "examples/driver_examples.h"
#include "fuzzing.h"
#include "app_main.h"
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES 0
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES_SOFT 1
#include "printf/printf/printf.h"

uint8_t initialized=0;

void putchar_(char c)
{
    
    if (initialized)
    {
    struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);
	int32_t i = io_write(io, (uint8_t *)&c, 1);
    }

}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
    cdcd_acm_example(); // needed to start receiving data on USB
    initialized = 1;
    //stdio_redirect_init(); // needed to redirect data to UART0   
    printf("this is a test\n");
    activateCortexMtraps();
    app_main();

  
	/* Replace with your application code */
	while (1) {
	}
}
