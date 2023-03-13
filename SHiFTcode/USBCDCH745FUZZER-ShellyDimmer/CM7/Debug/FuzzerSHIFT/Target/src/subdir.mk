################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FuzzerSHIFT/Target/src/callbacks.c \
../FuzzerSHIFT/Target/src/main_shelly.c 

OBJS += \
./FuzzerSHIFT/Target/src/callbacks.o \
./FuzzerSHIFT/Target/src/main_shelly.o 

C_DEPS += \
./FuzzerSHIFT/Target/src/callbacks.d \
./FuzzerSHIFT/Target/src/main_shelly.d 


# Each subdirectory must supply rules for building sources it contributes
FuzzerSHIFT/Target/src/%.o FuzzerSHIFT/Target/src/%.su: ../FuzzerSHIFT/Target/src/%.c FuzzerSHIFT/Target/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZER-ShellyDimmer/CM7/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZER-ShellyDimmer/CM7/FuzzerSHIFT/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../CommonSHIFT/Fuzzing/Inc -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../../CommonSHIFT/MallocMPU/FreeRTOS/ -I../../../CommonSHIFT/AsanRuntime/ASANMCU/inc -Ofast -ffunction-sections -fdata-sections -Wall -fno-common -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
FuzzerSHIFT/Target/src/main_shelly.o: ../FuzzerSHIFT/Target/src/main_shelly.c FuzzerSHIFT/Target/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZER-ShellyDimmer/CM7/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZER-ShellyDimmer/CM7/FuzzerSHIFT/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../CommonSHIFT/Fuzzing/Inc -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../../CommonSHIFT/MallocMPU/FreeRTOS/ -I../../../CommonSHIFT/AsanRuntime/ASANMCU/inc -Ofast -ffunction-sections -fdata-sections -Wall -fsanitize=float-divide-by-zero -fsanitize-coverage=trace-pc -fno-common -fsanitize=address -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FuzzerSHIFT-2f-Target-2f-src

clean-FuzzerSHIFT-2f-Target-2f-src:
	-$(RM) ./FuzzerSHIFT/Target/src/callbacks.d ./FuzzerSHIFT/Target/src/callbacks.o ./FuzzerSHIFT/Target/src/callbacks.su ./FuzzerSHIFT/Target/src/main_shelly.d ./FuzzerSHIFT/Target/src/main_shelly.o ./FuzzerSHIFT/Target/src/main_shelly.su

.PHONY: clean-FuzzerSHIFT-2f-Target-2f-src

