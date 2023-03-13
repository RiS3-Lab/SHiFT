################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FuzzerSHIFT/src/MonitorAndTargetSingleCore.c 

OBJS += \
./FuzzerSHIFT/src/MonitorAndTargetSingleCore.o 

C_DEPS += \
./FuzzerSHIFT/src/MonitorAndTargetSingleCore.d 


# Each subdirectory must supply rules for building sources it contributes
FuzzerSHIFT/src/%.o FuzzerSHIFT/src/%.su: ../FuzzerSHIFT/src/%.c FuzzerSHIFT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModBusPLC/CM7/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModBusPLC/CM7/FuzzerSHIFT/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../CommonSHIFT/Fuzzing/Inc -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../../CommonSHIFT/MallocMPU/FreeRTOS/ -I../../../CommonSHIFT/AsanRuntime/ASANMCU/inc -O0 -ffunction-sections -fdata-sections -Wall -fno-common -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FuzzerSHIFT-2f-src

clean-FuzzerSHIFT-2f-src:
	-$(RM) ./FuzzerSHIFT/src/MonitorAndTargetSingleCore.d ./FuzzerSHIFT/src/MonitorAndTargetSingleCore.o ./FuzzerSHIFT/src/MonitorAndTargetSingleCore.su

.PHONY: clean-FuzzerSHIFT-2f-src

