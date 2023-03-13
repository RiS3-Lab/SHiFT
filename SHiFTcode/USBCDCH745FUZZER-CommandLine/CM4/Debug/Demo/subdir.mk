################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Demo/app_main.c \
../Demo/memfault_handler.c \
../Demo/mpu_demo.c 

OBJS += \
./Demo/app_main.o \
./Demo/memfault_handler.o \
./Demo/mpu_demo.o 

C_DEPS += \
./Demo/app_main.d \
./Demo/memfault_handler.d \
./Demo/mpu_demo.d 


# Each subdirectory must supply rules for building sources it contributes
Demo/%.o Demo/%.su: ../Demo/%.c Demo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../Demo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Demo

clean-Demo:
	-$(RM) ./Demo/app_main.d ./Demo/app_main.o ./Demo/app_main.su ./Demo/memfault_handler.d ./Demo/memfault_handler.o ./Demo/memfault_handler.su ./Demo/mpu_demo.d ./Demo/mpu_demo.o ./Demo/mpu_demo.su

.PHONY: clean-Demo

