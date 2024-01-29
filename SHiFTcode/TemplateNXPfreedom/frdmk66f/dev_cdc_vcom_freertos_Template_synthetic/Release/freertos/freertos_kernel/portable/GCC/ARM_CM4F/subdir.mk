################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.c 

C_DEPS += \
./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.d 

OBJS += \
./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/portable/GCC/ARM_CM4F/%.o: ../freertos/freertos_kernel/portable/GCC/ARM_CM4F/%.c freertos/freertos_kernel/portable/GCC/ARM_CM4F/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D_DEBUG=1 -DCPU_MK66FN2M0VMD18 -DUSB_STACK_FREERTOS -DUSB_STACK_FREERTOS_HEAP_SIZE=32768 -DSDK_OS_FREE_RTOS -DFSL_OSA_BM_TASK_ENABLE=0 -DFSL_OSA_BM_TIMER_CONFIG=0 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DMCUXPRESSO_SDK -DCPU_MK66FN2M0VMD18_cm4 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/source" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/device/source/khci" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/device/source/ehci" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/phy" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/freertos/freertos_kernel/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/freertos/freertos_kernel/portable/GCC/ARM_CM4F" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/drivers" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/device" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/utilities" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/component/uart" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/component/serial_manager" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/component/lists" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/device/include" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/device/source" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/component/osa" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/CMSIS" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/board" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/device/class" -I"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/usb/device/class/cdc" -Os -fno-common -g -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-freertos_kernel-2f-portable-2f-GCC-2f-ARM_CM4F

clean-freertos-2f-freertos_kernel-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.d ./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.o

.PHONY: clean-freertos-2f-freertos_kernel-2f-portable-2f-GCC-2f-ARM_CM4F

