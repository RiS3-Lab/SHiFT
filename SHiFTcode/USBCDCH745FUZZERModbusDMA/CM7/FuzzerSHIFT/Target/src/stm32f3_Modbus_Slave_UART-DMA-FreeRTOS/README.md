# stm32f3_Modbus_Slave_UART-DMA-FreeRTOS
Light modbus RTU Slave without SPL and HAL. This lib doesn't need timers, only UART and 2 channels of DMA.

# HOW TO USE:

1) You need CMSIS library for stm32f3
2) You need FreeRTOS library.
3) Start Thread:
``` c
#include "FreeRTOS.h"
#include "task.h"

#include "modbus_rtu.h"

int main(void)
{
    SystemInit();
    modbusSlaveStartTread();
    vTaskStartScheduler();
    return 0;
}
```
