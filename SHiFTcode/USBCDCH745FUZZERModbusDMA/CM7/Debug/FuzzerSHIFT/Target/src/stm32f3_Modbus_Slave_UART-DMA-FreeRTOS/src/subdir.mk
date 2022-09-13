################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/callbacks.c \
../FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.c 

OBJS += \
./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/callbacks.o \
./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.o 

C_DEPS += \
./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/callbacks.d \
./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.d 


# Each subdirectory must supply rules for building sources it contributes
FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/%.o FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/%.su: ../FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/%.c FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModbusDMA/CM7/FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/inc" -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModbusDMA/CM7/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModbusDMA/CM7/FuzzerSHIFT/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../CommonSHIFT/Fuzzing/Inc -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../../CommonSHIFT/MallocMPU/FreeRTOS/ -I../../../CommonSHIFT/AsanRuntime/ASANMCU/inc -O0 -ffunction-sections -fdata-sections -Wall -fno-common -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.o: ../FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.c FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModbusDMA/CM7/FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/inc" -I../Core/Inc -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModbusDMA/CM7/FuzzerSHIFT/Target/inc" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/USBCDCH745FUZZERModbusDMA/CM7/FuzzerSHIFT/inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../CommonSHIFT/Fuzzing/Inc -I../../../CommonSHIFT/FreeRTOS-Kernel/include -I../../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../../CommonSHIFT/MallocMPU/FreeRTOS/ -I../../../CommonSHIFT/AsanRuntime/ASANMCU/inc -O0 -ffunction-sections -fdata-sections -Wall -fno-common -fsanitize-coverage=trace-pc -fsanitize=address -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FuzzerSHIFT-2f-Target-2f-src-2f-stm32f3_Modbus_Slave_UART-2d-DMA-2d-FreeRTOS-2f-src

clean-FuzzerSHIFT-2f-Target-2f-src-2f-stm32f3_Modbus_Slave_UART-2d-DMA-2d-FreeRTOS-2f-src:
	-$(RM) ./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/callbacks.d ./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/callbacks.o ./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/callbacks.su ./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.d ./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.o ./FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/modbus_rtu.su

.PHONY: clean-FuzzerSHIFT-2f-Target-2f-src-2f-stm32f3_Modbus_Slave_UART-2d-DMA-2d-FreeRTOS-2f-src

