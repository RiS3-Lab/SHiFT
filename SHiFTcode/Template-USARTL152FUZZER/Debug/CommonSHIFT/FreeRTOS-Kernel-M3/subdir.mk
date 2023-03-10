################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x20010000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/list.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/queue.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/tasks.c \
/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/timers.c 

OBJS += \
./CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.o \
./CommonSHIFT/FreeRTOS-Kernel-M3/list.o \
./CommonSHIFT/FreeRTOS-Kernel-M3/queue.o \
./CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.o \
./CommonSHIFT/FreeRTOS-Kernel-M3/tasks.o \
./CommonSHIFT/FreeRTOS-Kernel-M3/timers.o 

C_DEPS += \
./CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.d \
./CommonSHIFT/FreeRTOS-Kernel-M3/list.d \
./CommonSHIFT/FreeRTOS-Kernel-M3/queue.d \
./CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.d \
./CommonSHIFT/FreeRTOS-Kernel-M3/tasks.d \
./CommonSHIFT/FreeRTOS-Kernel-M3/timers.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.c CommonSHIFT/FreeRTOS-Kernel-M3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
CommonSHIFT/FreeRTOS-Kernel-M3/list.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/list.c CommonSHIFT/FreeRTOS-Kernel-M3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
CommonSHIFT/FreeRTOS-Kernel-M3/queue.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/queue.c CommonSHIFT/FreeRTOS-Kernel-M3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.c CommonSHIFT/FreeRTOS-Kernel-M3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
CommonSHIFT/FreeRTOS-Kernel-M3/tasks.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/tasks.c CommonSHIFT/FreeRTOS-Kernel-M3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
CommonSHIFT/FreeRTOS-Kernel-M3/timers.o: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/CommonSHIFT/FreeRTOS-Kernel-M3/timers.c CommonSHIFT/FreeRTOS-Kernel-M3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel-M3/include -I../../CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/FuzzerSHIFT/Target/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M3

clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M3:
	-$(RM) ./CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.d ./CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.o ./CommonSHIFT/FreeRTOS-Kernel-M3/event_groups.su ./CommonSHIFT/FreeRTOS-Kernel-M3/list.d ./CommonSHIFT/FreeRTOS-Kernel-M3/list.o ./CommonSHIFT/FreeRTOS-Kernel-M3/list.su ./CommonSHIFT/FreeRTOS-Kernel-M3/queue.d ./CommonSHIFT/FreeRTOS-Kernel-M3/queue.o ./CommonSHIFT/FreeRTOS-Kernel-M3/queue.su ./CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.d ./CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.o ./CommonSHIFT/FreeRTOS-Kernel-M3/stream_buffer.su ./CommonSHIFT/FreeRTOS-Kernel-M3/tasks.d ./CommonSHIFT/FreeRTOS-Kernel-M3/tasks.o ./CommonSHIFT/FreeRTOS-Kernel-M3/tasks.su ./CommonSHIFT/FreeRTOS-Kernel-M3/timers.d ./CommonSHIFT/FreeRTOS-Kernel-M3/timers.o ./CommonSHIFT/FreeRTOS-Kernel-M3/timers.su

.PHONY: clean-CommonSHIFT-2f-FreeRTOS-2d-Kernel-2d-M3

