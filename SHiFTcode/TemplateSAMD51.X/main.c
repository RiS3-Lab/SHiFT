#include <atmel_start.h>

#include "fuzzing.h"
#include "app_main.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
    cdcd_acm_example();
    
    activateCortexMtraps();
    app_main();

    
	/* Replace with your application code */
	while (1) {
	}
}
