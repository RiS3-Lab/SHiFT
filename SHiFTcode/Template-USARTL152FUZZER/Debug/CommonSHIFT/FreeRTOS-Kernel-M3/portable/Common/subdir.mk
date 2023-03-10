################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x20010000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.c 

OBJS += \
./CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.o 

C_DEPS += \
./CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.c CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M3-2f-portable-2f-Common

clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M3-2f-portable-2f-Common:
	-$(RM) ./CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.d ./CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.o ./CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/mpu_wrappers.su

.PHONY: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M3-2f-portable-2f-Common

