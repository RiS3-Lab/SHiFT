################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FuzzerSHIFT/Target/src/test.c 

OBJS += \
./FuzzerSHIFT/Target/src/test.o 

C_DEPS += \
./FuzzerSHIFT/Target/src/test.d 


# Each subdirectory must supply rules for building sources it contributes
FuzzerSHIFT/Target/src/test.o: ../FuzzerSHIFT/Target/src/test.c FuzzerSHIFT/Target/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBCDCH745FUZZER/CM7/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBCDCH745FUZZER/CM7/FuzzerSHIFT/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../CommonSHIFT/Fuzzing/Inc -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../../CommonSHIFT/MallocMPU/FreeRTOS/ -I../../../CommonSHIFT/AsanRuntime/ASANMCU/inc -Ofast -ffunction-sections -fdata-sections -Wall -fno-common -fsanitize-coverage=trace-pc -fsanitize=address -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FuzzerSHIFT-2f-Target-2f-src

clean-FuzzerSHIFT-2f-Target-2f-src:
	-$(RM) ./FuzzerSHIFT/Target/src/test.d ./FuzzerSHIFT/Target/src/test.o ./FuzzerSHIFT/Target/src/test.su

.PHONY: clean-FuzzerSHIFT-2f-Target-2f-src

