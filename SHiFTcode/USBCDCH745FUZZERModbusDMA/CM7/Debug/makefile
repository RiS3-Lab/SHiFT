################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x24000000
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/subdir.mk
-include FuzzerSHIFT/src/subdir.mk
-include FuzzerSHIFT/Target/src/stm32f3_Modbus_Slave_UART-DMA-FreeRTOS/src/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include CommonSHIFT/Fuzzing/Src/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel/portable/MemMang/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel/portable/Common/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel/subdir.mk
-include CommonSHIFT/AsanRuntime/ASANMCU/src/subdir.mk
-include Common/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := USBCDCH745FUZZERModbusDMA_CM7
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
USBCDCH745FUZZERModbusDMA_CM7.elf \

MAP_FILES += \
USBCDCH745FUZZERModbusDMA_CM7.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
USBCDCH745FUZZERModbusDMA_CM7.list \


# All Target
all: main-build

# Main-build Target
main-build: USBCDCH745FUZZERModbusDMA_CM7.elf secondary-outputs

# Tool invocations
USBCDCH745FUZZERModbusDMA_CM7.elf USBCDCH745FUZZERModbusDMA_CM7.map: $(OBJS) $(USER_OBJS) ../STM32H745ZITX_FLASH_MPU_ASAN.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "USBCDCH745FUZZERModbusDMA_CM7.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"../STM32H745ZITX_FLASH_MPU_ASAN.ld" --specs=nosys.specs -Wl,-Map="USBCDCH745FUZZERModbusDMA_CM7.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

USBCDCH745FUZZERModbusDMA_CM7.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "USBCDCH745FUZZERModbusDMA_CM7.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) USBCDCH745FUZZERModbusDMA_CM7.elf USBCDCH745FUZZERModbusDMA_CM7.list USBCDCH745FUZZERModbusDMA_CM7.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
