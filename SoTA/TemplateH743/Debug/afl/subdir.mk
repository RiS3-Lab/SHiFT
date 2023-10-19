################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../afl/SanitizerGCC.c \
../afl/fuzzing.c \
../afl/ring.c 

OBJS += \
./afl/SanitizerGCC.o \
./afl/fuzzing.o \
./afl/ring.o 

C_DEPS += \
./afl/SanitizerGCC.d \
./afl/fuzzing.d \
./afl/ring.d 


# Each subdirectory must supply rules for building sources it contributes
afl/%.o afl/%.su: ../afl/%.c afl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SoTA/TemplateH743/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SoTA/TemplateH743/afl/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-afl

clean-afl:
	-$(RM) ./afl/SanitizerGCC.d ./afl/SanitizerGCC.o ./afl/SanitizerGCC.su ./afl/fuzzing.d ./afl/fuzzing.o ./afl/fuzzing.su ./afl/ring.d ./afl/ring.o ./afl/ring.su

.PHONY: clean-afl

