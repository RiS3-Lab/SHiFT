################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Target/src/test.c 

OBJS += \
./Target/src/test.o 

C_DEPS += \
./Target/src/test.d 


# Each subdirectory must supply rules for building sources it contributes
Target/src/%.o Target/src/%.su: ../Target/src/%.c Target/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SoTA/TemplateL152/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SoTA/TemplateL152/afl/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SoTA/TemplateL152/Target/inc" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Target-2f-src

clean-Target-2f-src:
	-$(RM) ./Target/src/test.d ./Target/src/test.o ./Target/src/test.su

.PHONY: clean-Target-2f-src

