################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include usb/phy/subdir.mk
-include usb/device/source/khci/subdir.mk
-include usb/device/source/ehci/subdir.mk
-include usb/device/source/subdir.mk
-include usb/device/class/cdc/subdir.mk
-include usb/device/class/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include freertos/freertos_kernel/portable/MemMang/subdir.mk
-include freertos/freertos_kernel/portable/GCC/ARM_CM4F/subdir.mk
-include freertos/freertos_kernel/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/osa/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include FuzzerSHIFT/src/subdir.mk
-include FuzzerSHIFT/Target/src/subdir.mk
-include CommonSHIFT/Fuzzing/Src/subdir.mk
-include CommonSHIFT/AsanRuntime/ASANMCU/src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := frdmk66f_dev_cdc_vcom_freertos
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: frdmk66f_dev_cdc_vcom_freertos.axf

# Tool invocations
frdmk66f_dev_cdc_vcom_freertos.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="frdmk66f_dev_cdc_vcom_freertos.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T frdmk66f_dev_cdc_vcom_freertos_Release.ld -o "frdmk66f_dev_cdc_vcom_freertos.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) frdmk66f_dev_cdc_vcom_freertos.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "frdmk66f_dev_cdc_vcom_freertos.axf"; # arm-none-eabi-objcopy -v -O binary "frdmk66f_dev_cdc_vcom_freertos.axf" "frdmk66f_dev_cdc_vcom_freertos.bin" ; # checksum -p MK66FN2M0xxx18 -d "frdmk66f_dev_cdc_vcom_freertos.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
