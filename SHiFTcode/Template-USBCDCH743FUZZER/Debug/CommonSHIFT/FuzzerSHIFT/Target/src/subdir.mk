################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FuzzerSHIFT/Target/src/test.c 

OBJS += \
./CommonSHIFT/FuzzerSHIFT/Target/src/test.o 

C_DEPS += \
./CommonSHIFT/FuzzerSHIFT/Target/src/test.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/FuzzerSHIFT/Target/src/test.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FuzzerSHIFT/Target/src/test.c CommonSHIFT/FuzzerSHIFT/Target/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBCDCH743FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBCDCH743FUZZER/FuzzerSHIFT/Target/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-FuzzerSHIFT-2f-Target-2f-src

clean-CommonSHIFT-2f-FuzzerSHIFT-2f-Target-2f-src:
	-$(RM) ./CommonSHIFT/FuzzerSHIFT/Target/src/test.d ./CommonSHIFT/FuzzerSHIFT/Target/src/test.o ./CommonSHIFT/FuzzerSHIFT/Target/src/test.su

.PHONY: clean-CommonSHIFT-2f-FuzzerSHIFT-2f-Target-2f-src

