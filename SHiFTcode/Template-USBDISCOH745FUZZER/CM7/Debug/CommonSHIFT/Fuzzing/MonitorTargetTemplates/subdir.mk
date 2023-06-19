################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.c 

OBJS += \
./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.o \
./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.o \
./CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.o 

C_DEPS += \
./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.d \
./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.d \
./CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.c CommonSHIFT/Fuzzing/MonitorTargetTemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBDISCOH745FUZZER/CM7/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBDISCOH745FUZZER/CM7/FuzzerSHIFT/Target/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/MallocMPU/FreeRTOS" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.c CommonSHIFT/Fuzzing/MonitorTargetTemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBDISCOH745FUZZER/CM7/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBDISCOH745FUZZER/CM7/FuzzerSHIFT/Target/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/MallocMPU/FreeRTOS" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.c CommonSHIFT/Fuzzing/MonitorTargetTemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBDISCOH745FUZZER/CM7/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USBDISCOH745FUZZER/CM7/FuzzerSHIFT/Target/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/MallocMPU/FreeRTOS" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/AsanRuntime/ASANMCU/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-Fuzzing-2f-MonitorTargetTemplates

clean-CommonSHIFT-2f-Fuzzing-2f-MonitorTargetTemplates:
	-$(RM) ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.d ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.o ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerDualCore.su ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.d ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.o ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/FuzzerTargetSingleCore.su ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.d ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.o ./CommonSHIFT/Fuzzing/MonitorTargetTemplates/TargetDualCore.su

.PHONY: clean-CommonSHIFT-2f-Fuzzing-2f-MonitorTargetTemplates

