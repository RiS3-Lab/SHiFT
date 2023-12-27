################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: asan-0x2400
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/SanitizerGCC.c \
/home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/app_main.c \
/home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.c \
/home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/fuzzing.c \
/home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/ring.c 

OBJS += \
./CommonSHIFT/Fuzzing/Src/SanitizerGCC.o \
./CommonSHIFT/Fuzzing/Src/app_main.o \
./CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.o \
./CommonSHIFT/Fuzzing/Src/fuzzing.o \
./CommonSHIFT/Fuzzing/Src/ring.o 

C_DEPS += \
./CommonSHIFT/Fuzzing/Src/SanitizerGCC.d \
./CommonSHIFT/Fuzzing/Src/app_main.d \
./CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.d \
./CommonSHIFT/Fuzzing/Src/fuzzing.d \
./CommonSHIFT/Fuzzing/Src/ring.d 


# Each subdirectory must supply rules for building sources it contributes
CommonSHIFT/Fuzzing/Src/SanitizerGCC.o: /home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/SanitizerGCC.c CommonSHIFT/Fuzzing/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/inc" -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/Target/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CommonSHIFT/Fuzzing/Src/app_main.o: /home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/app_main.c CommonSHIFT/Fuzzing/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/inc" -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/Target/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.o: /home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.c CommonSHIFT/Fuzzing/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/inc" -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/Target/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CommonSHIFT/Fuzzing/Src/fuzzing.o: /home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/fuzzing.c CommonSHIFT/Fuzzing/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/inc" -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/Target/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CommonSHIFT/Fuzzing/Src/ring.o: /home/lcm/github/shift/SHiFT/SHiFTcode/CommonSHIFT/Fuzzing/Src/ring.c CommonSHIFT/Fuzzing/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../CommonSHIFT/Fuzzing/Inc -I../../CommonSHIFT/FreeRTOS-Kernel/include -I../../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU -I../../CommonSHIFT/AsanRuntime/ASANMCU/inc -I../../CommonSHIFT/MallocMPU/FreeRTOS -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/inc" -I"/home/lcm/github/shift/SHiFT/SHiFTcode/USBCDCH743FUZZERModBusPLC/FuzzerSHIFT/Target/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CommonSHIFT-2f-Fuzzing-2f-Src

clean-CommonSHIFT-2f-Fuzzing-2f-Src:
	-$(RM) ./CommonSHIFT/Fuzzing/Src/SanitizerGCC.d ./CommonSHIFT/Fuzzing/Src/SanitizerGCC.o ./CommonSHIFT/Fuzzing/Src/SanitizerGCC.su ./CommonSHIFT/Fuzzing/Src/app_main.d ./CommonSHIFT/Fuzzing/Src/app_main.o ./CommonSHIFT/Fuzzing/Src/app_main.su ./CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.d ./CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.o ./CommonSHIFT/Fuzzing/Src/fault_handlersRTOS.su ./CommonSHIFT/Fuzzing/Src/fuzzing.d ./CommonSHIFT/Fuzzing/Src/fuzzing.o ./CommonSHIFT/Fuzzing/Src/fuzzing.su ./CommonSHIFT/Fuzzing/Src/ring.d ./CommonSHIFT/Fuzzing/Src/ring.o ./CommonSHIFT/Fuzzing/Src/ring.su

.PHONY: clean-CommonSHIFT-2f-Fuzzing-2f-Src
