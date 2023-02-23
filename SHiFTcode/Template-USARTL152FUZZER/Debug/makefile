################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU ARM embedded shadow 0x20010000
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include FuzzerSHIFT/src/subdir.mk
-include FuzzerSHIFT/Target/src/subdir.mk
-include Drivers/STM32L1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include CommonSHIFT/Fuzzing/Src/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel-M3/portable/MemMang/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel-M3/portable/GCC/ARM_CM3_MPU/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel-M3/portable/Common/subdir.mk
-include CommonSHIFT/FreeRTOS-Kernel-M3/subdir.mk
-include CommonSHIFT/AsanRuntime/ASANMCU/src/subdir.mk
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


BUILD_ARTIFACT_NAME := Template-USARTL152FUZZER
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Template-USARTL152FUZZER.elf \

MAP_FILES += \
Template-USARTL152FUZZER.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Template-USARTL152FUZZER.list \


# All Target
all: main-build

# Main-build Target
main-build: Template-USARTL152FUZZER.elf secondary-outputs

# Tool invocations
Template-USARTL152FUZZER.elf Template-USARTL152FUZZER.map: $(OBJS) $(USER_OBJS) /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/STM32L152RETX_FLASH_MPU_ASAN.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Template-USARTL152FUZZER.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/Template-USARTL152FUZZER/STM32L152RETX_FLASH_MPU_ASAN.ld" --specs=nosys.specs -Wl,-Map="Template-USARTL152FUZZER.map" -Wl,--gc-sections -static  -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Template-USARTL152FUZZER.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Template-USARTL152FUZZER.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Template-USARTL152FUZZER.elf Template-USARTL152FUZZER.list Template-USARTL152FUZZER.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
