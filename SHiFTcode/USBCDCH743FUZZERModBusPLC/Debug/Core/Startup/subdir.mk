################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: asan-0x2400
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h743zitx.s 

OBJS += \
./Core/Startup/startup_stm32h743zitx.o 

S_DEPS += \
./Core/Startup/startup_stm32h743zitx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32h743zitx.d ./Core/Startup/startup_stm32h743zitx.o

.PHONY: clean-Core-2f-Startup

