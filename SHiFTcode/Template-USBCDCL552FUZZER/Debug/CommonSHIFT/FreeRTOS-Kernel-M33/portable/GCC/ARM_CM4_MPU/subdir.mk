################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.c 

OBJS += \
./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.o \
./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.o 

C_DEPS += \
./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.d \
./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.c CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L552xx -c -I../Core/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L5xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.c CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L552xx -c -I../Core/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L5xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M33-2f-portable-2f-GCC-2f-ARM_CM4_MPU

clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M33-2f-portable-2f-GCC-2f-ARM_CM4_MPU:
	-$(RM) ./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.d ./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.o ./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.su ./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.d ./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.o ./CommonSHIFT/FreeRTOS-Kernel-M33/portable/GCC/ARM_CM4_MPU/port.su

.PHONY: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M33-2f-portable-2f-GCC-2f-ARM_CM4_MPU

