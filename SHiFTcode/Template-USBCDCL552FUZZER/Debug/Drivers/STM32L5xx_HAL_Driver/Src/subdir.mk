################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0X20030000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_cortex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_exti.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ramfunc.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_gpio.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_icache.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart_ex.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dma.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_exti.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_gpio.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_ucpd.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usb.c \
../Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_utils.c 

OBJS += \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_cortex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_exti.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ramfunc.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_gpio.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_icache.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart_ex.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dma.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_exti.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_gpio.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_ucpd.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usb.o \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_utils.o 

C_DEPS += \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_cortex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_exti.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ramfunc.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_gpio.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_icache.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart_ex.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dma.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_exti.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_gpio.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_ucpd.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usb.d \
./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L5xx_HAL_Driver/Src/%.o Drivers/STM32L5xx_HAL_Driver/Src/%.su: ../Drivers/STM32L5xx_HAL_Driver/Src/%.c Drivers/STM32L5xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L552xx -c -I../Core/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L5xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M33/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM33_NTZ/non_secure" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBCDCL552FUZZER/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBCDCL552FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/MallocMPU/FreeRTOS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32L5xx_HAL_Driver-2f-Src

clean-Drivers-2f-STM32L5xx_HAL_Driver-2f-Src:
	-$(RM) ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_adc_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_cortex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_cortex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_cortex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_crc_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_dma_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_exti.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_exti.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_exti.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ramfunc.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ramfunc.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_flash_ramfunc.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_gpio.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_gpio.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_gpio.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_i2c_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_icache.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_icache.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_icache.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pcd_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_pwr_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rcc_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_rtc_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_tim_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart_ex.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart_ex.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_hal_uart_ex.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dma.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dma.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_dma.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_exti.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_exti.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_exti.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_gpio.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_gpio.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_gpio.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_ucpd.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_ucpd.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_ucpd.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usb.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usb.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_usb.su ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_utils.d ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_utils.o ./Drivers/STM32L5xx_HAL_Driver/Src/stm32l5xx_ll_utils.su

.PHONY: clean-Drivers-2f-STM32L5xx_HAL_Driver-2f-Src

