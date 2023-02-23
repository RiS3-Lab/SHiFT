################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x20010000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.c 

OBJS += \
./CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.o \
./CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.o 

C_DEPS += \
./CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.d \
./CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.c CommonSHIFT/AsanRuntime/ASANMCU/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.c CommonSHIFT/AsanRuntime/ASANMCU/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-AsanRuntime-2f-ASANMCU-2f-src

clean-CommonSHIFT-2f-AsanRuntime-2f-ASANMCU-2f-src:
	-$(RM) ./CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.d ./CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.o ./CommonSHIFT/AsanRuntime/ASANMCU/src/McuASAN.su ./CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.d ./CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.o ./CommonSHIFT/AsanRuntime/ASANMCU/src/ubsan_handlers.su

.PHONY: clean-CommonSHIFT-2f-AsanRuntime-2f-ASANMCU-2f-src

