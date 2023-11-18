################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.c 

OBJS += \
./CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.o 

C_DEPS += \
./CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.c CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModBusPLC/CM7/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModBusPLC/CM7/FuzzerSHIFT/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../CommonSHIFT/Fuzzing/Inc -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../../CommonSHIFT/MallocMPU/FreeRTOS/ -I../../../CommonSHIFT/AsanRuntime/ASANMCU/inc -O0 -ffunction-sections -fdata-sections -Wall -fno-common -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-FreRTOS-2d-Kernel-2d-M23-2f-portable-2f-MemMang

clean-CommonSHIFT-2f-FreRTOS-2d-Kernel-2d-M23-2f-portable-2f-MemMang:
	-$(RM) ./CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.d ./CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.o ./CommonSHIFT/FreRTOS-Kernel-M23/portable/MemMang/heap_4.su

.PHONY: clean-CommonSHIFT-2f-FreRTOS-2d-Kernel-2d-M23-2f-portable-2f-MemMang

