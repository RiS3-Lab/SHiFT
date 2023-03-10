################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x20010000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_crc.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.c \
../Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.c 

OBJS += \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_crc.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.o \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.o 

C_DEPS += \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_crc.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.d \
./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L1xx_HAL_Driver/Src/%.o Drivers/STM32L1xx_HAL_Driver/Src/%.su: ../Drivers/STM32L1xx_HAL_Driver/Src/%.c Drivers/STM32L1xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-STM32L1xx_HAL_Driver-2f-Src

clean-Drivers-2f-STM32L1xx_HAL_Driver-2f-Src:
	-$(RM) ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_crc.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_crc.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_crc.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.su ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.d ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.o ./Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.su

.PHONY: clean-Drivers-2f-STM32L1xx_HAL_Driver-2f-Src

