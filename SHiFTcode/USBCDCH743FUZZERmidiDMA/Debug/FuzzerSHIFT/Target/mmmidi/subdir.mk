################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FuzzerSHIFT/Target/mmmidi/midi_lowlevel.c \
../FuzzerSHIFT/Target/mmmidi/mm_midirouter_standard.c 

OBJS += \
./FuzzerSHIFT/Target/mmmidi/midi_lowlevel.o \
./FuzzerSHIFT/Target/mmmidi/mm_midirouter_standard.o 

C_DEPS += \
./FuzzerSHIFT/Target/mmmidi/midi_lowlevel.d \
./FuzzerSHIFT/Target/mmmidi/mm_midirouter_standard.d 


# Each subdirectory must supply rules for building sources it contributes
FuzzerSHIFT/Target/mmmidi/%.o FuzzerSHIFT/Target/mmmidi/%.su: ../FuzzerSHIFT/Target/mmmidi/%.c FuzzerSHIFT/Target/mmmidi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH743FUZZERmidiDMA/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH743FUZZERmidiDMA/FuzzerSHIFT/Target/mmmidi/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FuzzerSHIFT-2f-Target-2f-mmmidi

clean-FuzzerSHIFT-2f-Target-2f-mmmidi:
	-$(RM) ./FuzzerSHIFT/Target/mmmidi/midi_lowlevel.d ./FuzzerSHIFT/Target/mmmidi/midi_lowlevel.o ./FuzzerSHIFT/Target/mmmidi/midi_lowlevel.su ./FuzzerSHIFT/Target/mmmidi/mm_midirouter_standard.d ./FuzzerSHIFT/Target/mmmidi/mm_midirouter_standard.o ./FuzzerSHIFT/Target/mmmidi/mm_midirouter_standard.su

.PHONY: clean-FuzzerSHIFT-2f-Target-2f-mmmidi

