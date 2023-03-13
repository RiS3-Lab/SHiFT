################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FuzzerSHIFT/Target/mmmidi/src/leds.c \
../FuzzerSHIFT/Target/mmmidi/src/main_original.c \
../FuzzerSHIFT/Target/mmmidi/src/mm_midiccrouter.c \
../FuzzerSHIFT/Target/mmmidi/src/mm_midievent.c \
../FuzzerSHIFT/Target/mmmidi/src/mm_midieventbuilder.c \
../FuzzerSHIFT/Target/mmmidi/src/mm_midimsg.c \
../FuzzerSHIFT/Target/mmmidi/src/mm_midimsgbuilder.c \
../FuzzerSHIFT/Target/mmmidi/src/mm_midirouter.c 

OBJS += \
./FuzzerSHIFT/Target/mmmidi/src/leds.o \
./FuzzerSHIFT/Target/mmmidi/src/main_original.o \
./FuzzerSHIFT/Target/mmmidi/src/mm_midiccrouter.o \
./FuzzerSHIFT/Target/mmmidi/src/mm_midievent.o \
./FuzzerSHIFT/Target/mmmidi/src/mm_midieventbuilder.o \
./FuzzerSHIFT/Target/mmmidi/src/mm_midimsg.o \
./FuzzerSHIFT/Target/mmmidi/src/mm_midimsgbuilder.o \
./FuzzerSHIFT/Target/mmmidi/src/mm_midirouter.o 

C_DEPS += \
./FuzzerSHIFT/Target/mmmidi/src/leds.d \
./FuzzerSHIFT/Target/mmmidi/src/main_original.d \
./FuzzerSHIFT/Target/mmmidi/src/mm_midiccrouter.d \
./FuzzerSHIFT/Target/mmmidi/src/mm_midievent.d \
./FuzzerSHIFT/Target/mmmidi/src/mm_midieventbuilder.d \
./FuzzerSHIFT/Target/mmmidi/src/mm_midimsg.d \
./FuzzerSHIFT/Target/mmmidi/src/mm_midimsgbuilder.d \
./FuzzerSHIFT/Target/mmmidi/src/mm_midirouter.d 


# Each subdirectory must supply rules for building sources it contributes
FuzzerSHIFT/Target/mmmidi/src/%.o FuzzerSHIFT/Target/mmmidi/src/%.su: ../FuzzerSHIFT/Target/mmmidi/src/%.c FuzzerSHIFT/Target/mmmidi/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH743FUZZERmidiDMA/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH743FUZZERmidiDMA/FuzzerSHIFT/Target/mmmidi/inc" -O1 -ffunction-sections -fdata-sections -Wall -fsanitize-coverage=trace-pc -fno-common -fsanitize=address -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FuzzerSHIFT-2f-Target-2f-mmmidi-2f-src

clean-FuzzerSHIFT-2f-Target-2f-mmmidi-2f-src:
	-$(RM) ./FuzzerSHIFT/Target/mmmidi/src/leds.d ./FuzzerSHIFT/Target/mmmidi/src/leds.o ./FuzzerSHIFT/Target/mmmidi/src/leds.su ./FuzzerSHIFT/Target/mmmidi/src/main_original.d ./FuzzerSHIFT/Target/mmmidi/src/main_original.o ./FuzzerSHIFT/Target/mmmidi/src/main_original.su ./FuzzerSHIFT/Target/mmmidi/src/mm_midiccrouter.d ./FuzzerSHIFT/Target/mmmidi/src/mm_midiccrouter.o ./FuzzerSHIFT/Target/mmmidi/src/mm_midiccrouter.su ./FuzzerSHIFT/Target/mmmidi/src/mm_midievent.d ./FuzzerSHIFT/Target/mmmidi/src/mm_midievent.o ./FuzzerSHIFT/Target/mmmidi/src/mm_midievent.su ./FuzzerSHIFT/Target/mmmidi/src/mm_midieventbuilder.d ./FuzzerSHIFT/Target/mmmidi/src/mm_midieventbuilder.o ./FuzzerSHIFT/Target/mmmidi/src/mm_midieventbuilder.su ./FuzzerSHIFT/Target/mmmidi/src/mm_midimsg.d ./FuzzerSHIFT/Target/mmmidi/src/mm_midimsg.o ./FuzzerSHIFT/Target/mmmidi/src/mm_midimsg.su ./FuzzerSHIFT/Target/mmmidi/src/mm_midimsgbuilder.d ./FuzzerSHIFT/Target/mmmidi/src/mm_midimsgbuilder.o ./FuzzerSHIFT/Target/mmmidi/src/mm_midimsgbuilder.su ./FuzzerSHIFT/Target/mmmidi/src/mm_midirouter.d ./FuzzerSHIFT/Target/mmmidi/src/mm_midirouter.o ./FuzzerSHIFT/Target/mmmidi/src/mm_midirouter.su

.PHONY: clean-FuzzerSHIFT-2f-Target-2f-mmmidi-2f-src

