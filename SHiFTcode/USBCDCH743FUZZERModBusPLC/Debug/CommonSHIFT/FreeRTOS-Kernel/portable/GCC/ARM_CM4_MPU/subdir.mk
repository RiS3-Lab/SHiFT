################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: asan-0x2400
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.c 

OBJS += \
./CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.o 

C_DEPS += \
./CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.o: /home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.c CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/inc" -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/Target/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2f-portable-2f-GCC-2f-ARM_CM4_MPU

clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2f-portable-2f-GCC-2f-ARM_CM4_MPU:
	-$(RM) ./CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.d ./CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.o ./CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/port.su

.PHONY: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2f-portable-2f-GCC-2f-ARM_CM4_MPU

