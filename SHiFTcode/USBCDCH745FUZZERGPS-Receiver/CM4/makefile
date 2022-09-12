ROOT_DIR := $(abspath ../..)
COMMON_DIR := $(abspath ..)
PROJ_DIR := $(abspath .)
BUILD_DIR  := $(PROJ_DIR)/build

Q ?= @

# use the following command to compile using LLVM
#COMPILER=clang make


COMMON_CODE_DIR := $(COMMON_DIR)/Common/Src

DRIVERS_ROOT_DIR := $(COMMON_DIR)/Drivers/STM32H7xx_HAL_Driver/Src

FUZZING_ROOT_DIR :=  $(ROOT_DIR)/Common/Fuzzing


FREERTOS_ROOT := $(ROOT_DIR)/Common/FreeRTOS-Kernel

# CFLAGS which can provided from the CLI
# They will be appended last and will consequently override
# any pre-existing settings
CLI_CFLAG_OVERRIDES ?=
CLI_LDFLAG_OVERRIDES ?=

# Set things up to use the arm-none-eabi-gcc that is on
# our path by default but allow things to be easily overridden, i.e:
#
# COMPILER=<PATH_TO_OTHER_GCC_VERSION>/arm-none-eabi-gcc make
# COMPILER=clang make
COMPILER ?= arm-none-eabi-gcc
CC = $(COMPILER)

$(info $(CC))


DRIVERS_SOURCES += \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_cortex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_dma.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_dma_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_exti.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_flash.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_flash_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_gpio.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_hsem.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_i2c.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_i2c_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_mdma.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_pwr.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_pwr_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_rcc.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_rcc_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_tim.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_tim_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_uart.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_uart_ex.c





FREERTOS_SOURCES += \
$(FREERTOS_ROOT)/croutine.c \
$(FREERTOS_ROOT)/event_groups.c \
$(FREERTOS_ROOT)/list.c \
$(FREERTOS_ROOT)/queue.c \
$(FREERTOS_ROOT)/stream_buffer.c \
$(FREERTOS_ROOT)/tasks.c \
$(FREERTOS_ROOT)/timers.c \
$(FREERTOS_ROOT)/portable/GCC/ARM_CM4_MPU/port.c \
$(FREERTOS_ROOT)/portable/Common/mpu_wrappers.c \
$(FREERTOS_ROOT)/portable/MemMang/heap_4.c


COMMON_SOURCES += \
$(COMMON_CODE_DIR)/system_stm32h7xx_dualcore_boot_cm4_cm7.c


PROJECT_SRC_DIR = $(PROJ_DIR)/Core/Src

DEMO_SRC_DIR = $(PROJ_DIR)/Demo

DEMO_SOURCES += \
$(DEMO_SRC_DIR)/app_main.c \
$(DEMO_SRC_DIR)/memfault_handler.c \
$(DEMO_SRC_DIR)/mpu_demo.c




#TEST_SRC = \
#$(TEST_ROOT_DIR)/Src/testmodbus.c \
#$(TEST_ROOT_DIR)/Src/test.c \


#FUZZING_SOURCES += \
#$(FUZZING_ROOT_DIR)/Src/sanitizer.c \
#$(FUZZING_ROOT_DIR)/Src/ring.c \
#$(FUZZING_ROOT_DIR)/Src/fuzzing.c \


SRC_FILES += \
$(PROJECT_SRC_DIR)/main.c \
$(PROJECT_SRC_DIR)/stm32h7xx_hal_msp.c \
$(PROJECT_SRC_DIR)/stm32h7xx_it.c \
$(PROJECT_SRC_DIR)/stm32h7xx_hal_timebase_tim.c \
$(PROJECT_SRC_DIR)/syscalls.c \
$(PROJECT_SRC_DIR)/sysmem.c \
$(FREERTOS_SOURCES) \
$(DRIVERS_SOURCES) \
$(DEMO_SOURCES) \
$(COMMON_SOURCES)

OBJ_FILES := $(patsubst $(ROOT_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))


PROJECT_STARTUP_DIR = $(PROJ_DIR)/Core/Startup

STARTUP_SOURCES += \
$(PROJECT_STARTUP_DIR)/startup_stm32h745zitx.s


OBJ_FILES := $(OBJ_FILES) \
$(patsubst $(ROOT_DIR)/%.s,$(BUILD_DIR)/%.o,$(STARTUP_SOURCES))


INCLUDE_PATHS += \
  -I$(PROJ_DIR)/Core/Inc \
  -I$(COMMON_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc \
  -I$(COMMON_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy \
  -I$(COMMON_DIR)/Drivers/CMSIS/Device/ST/STM32H7xx/Include \
  -I$(COMMON_DIR)/Drivers/CMSIS/Include \
  -I$(ROOT_DIR)/Common/Fuzzing/Inc \
  -I$(ROOT_DIR)/Common/FreeRTOS-Kernel/include \
  -I$(ROOT_DIR)/Common/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU \
  -I$(PROJ_DIR)/Demo



# Note: These arguments will be used by clang to select
# the specific architecture target when we use the
# generic --target=arm-none-eabi
ARCH_CFLAGS += \
  -mthumb -mcpu=cortex-m4 \
  -mfloat-abi=hard -mfpu=fpv4-sp-d16

#  -mfloat-abi=soft
#-mfloat-abi=hard -mfpu=fpv4-sp-d16

CC_VERSION_INFO ="$(shell $(CC) -v 2>&1 | head -2)"

ifneq '' '$(findstring clang,$(CC_VERSION_INFO))'
$(info ===Clang Compiler Detected===)

# Default assumes an GNU ARM toolchain is on your path
# but an explicit path can also be provided by doing
# ARM_GNU_CC=<PATH_TO_GCC> make
ARM_GNU_CC ?= arm-none-eabi-gcc

ARM_CORTEXM_SYSROOT = \
  $(shell $(ARM_GNU_CC) $(ARCH_CFLAGS) -print-sysroot 2>&1)

# The directory where Newlib's libc.a & libm.a reside
# for the specific target architecture
ARM_CORTEXM_MULTI_DIR = \
  $(shell $(ARM_GNU_CC) $(ARCH_CFLAGS) -print-multi-directory 2>&1)

# Pick up builtins needed for compilation
ARM_CORTEXM_BUILTINS ?= \
  $(shell $(ARM_GNU_CC) $(ARCH_CFLAGS) -print-libgcc-file-name 2>&1)

COMPILER_SPECIFIC_CFLAGS += \
  --target=arm-none-eabi \
  --sysroot=$(ARM_CORTEXM_SYSROOT) \
  -Oz 


#-Wthread-safety \
#  -Wthread-safety-beta

COMPILER_SPECIFIC_LDFLAGS += \
  -L$(ARM_CORTEXM_SYSROOT)/lib/$(ARM_CORTEXM_MULTI_DIR) \
  $(ARM_CORTEXM_BUILTINS)

endif

ifneq '' '$(findstring gcc,$(CC_VERSION_INFO))'
$(info ===GCC Compiler Detected===)

COMPILER_SPECIFIC_CFLAGS += \
  -Os

COMPILER_SPECIFIC_LDFLAGS += \
  -Wl,-lgcc 

endif


CFLAGS += -std=gnu11
CFLAGS += -g3
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -Wall
#CFLAGS += -fstack-usage
#CFLAGS += --specs=nano.specs 
CFLAGS += -Werror 
CFLAGS += -nostdlib 
CFLAGS += -DDEBUG 
CFLAGS += -DCORE_CM4
CFLAGS += -DUSE_HAL_DRIVER 
CFLAGS += -DSTM32H745xx 
CFLAGS += -Wno-parentheses-equality 
CFLAGS +=  $(COMPILER_SPECIFIC_CFLAGS) 
CFLAGS +=  $(ARCH_CFLAGS) 
CFLAGS +=  $(CLI_CFLAG_OVERRIDES)



ASFLAGS += -g3 -DDEBUG -c 
ASFLAGS += -x assembler-with-cpp 
#ASFLAGS += --specs=nano.specs 
ASFLAGS += $(ARCH_CFLAGS)



TARGET ?= stm32h745M4
LDSCRIPT = $(PROJ_DIR)/STM32H745ZITX_FLASH_MPU.ld
TARGET_ELF = $(BUILD_DIR)/$(TARGET).elf


LDFLAGS += $(COMPILER_SPECIFIC_LDFLAGS)
LDFLAGS +=  $(ARCH_CFLAGS) 
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,-Map="$(BUILD_DIR)/$(TARGET).map"
LDFLAGS += -Wl,--gc-sections -static 
LDFLAGS += --specs=nano.specs
LDFLAGS += -Wl,--start-group -lc -lm -Wl,--end-group
LDFLAGS += $(CLI_LDFLAG_OVERRIDES)




LINKER_OVERRIDE ?=

DEP_DIR = $(BUILD_DIR)/dep
DEP_CFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$(*F).d

all: $(TARGET_ELF)

-include $(wildcard $(DEP_DIR)/*.d)

clean:
	rm -rf $(BUILD_DIR)



H745AM := $(shell STM32_Programmer_CLI --Connect port=SWD sn=0035002C3137511039383538 > /dev/null 2>&1 ; echo $$?)
H745CH := $(shell STM32_Programmer_CLI --Connect port=SWD sn=004000463137511139383538 > /dev/null 2>&1 ; echo $$?)

flash: $(TARGET_ELF)
ifeq ($(H745AM),0)
	STM32_Programmer_CLI -c port=SWD -w $(BUILD_DIR)/stm32h745M4.elf -v -ob displ -hardRst  sn=0035002C3137511039383538
else
ifeq ($(H745CH),0)
	STM32_Programmer_CLI -c port=SWD -w $(BUILD_DIR)/stm32h745M4.elf -v -ob displ -hardRst  sn=004000463137511139383538
else
	@echo "ERROR: No Board H745 found"
endif	
endif






$(TARGET_ELF): $(OBJ_FILES)  $(LDSCRIPT)
	@echo "Linking library"
  #$(Q) $(CC) $(OBJ_FILES)  $(LDFLAGS) -o $@
	$(Q) arm-none-eabi-gcc $(OBJ_FILES)  $(LDFLAGS) -o $@
	@echo "Generated $(patsubst $(ROOT_DIR)/%,%,$@)"
	arm-none-eabi-objcopy -O binary $(TARGET_ELF)  "$(BUILD_DIR)/$(TARGET).bin"
	arm-none-eabi-objcopy -O ihex $(TARGET_ELF) "$(BUILD_DIR)/$(TARGET).hex"
  


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(DEP_DIR):
	@mkdir -p $(DEP_DIR)

# FreeRTOS should really be included as a submodule in a real project
# Let's do a cheap hack and clone it here instead
#$(FREERTOS_PORT_ROOT):
#	git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git $(FREERTOS_ROOT_DIR)
#

$(OBJ_FILES): $(SRC_FILES) makefile



# build Core files
$(BUILD_DIR)/USBCDCH745FUZZERGPS-Receiver/CM4/Core/Src/%.o: $(PROJ_DIR)/Core/Src/%.c |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build Demo files
$(BUILD_DIR)/USBCDCH745FUZZERGPS-Receiver/CM4/Demo/%.o: $(PROJ_DIR)/Demo/%.c |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<

# build drivers
$(BUILD_DIR)/USBCDCH745FUZZERGPS-Receiver/Drivers/%.o: $(COMMON_DIR)/Drivers/%.c |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<

# build Fuzzing files
#$(BUILD_DIR)/Common/Fuzzing/%.o: $(ROOT_DIR)/Common/Fuzzing/%.c |  $(BUILD_DIR) $(DEP_DIR) 
#	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
#	@mkdir -p $(dir $@)
#	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build middlewares
#$(BUILD_DIR)/USBCDCH745FUZZERGPS-Receiver/Middlewares/%.o: $(COMMON_DIR)/Middlewares/%.c |  $(BUILD_DIR) $(DEP_DIR) 
#	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
#	@mkdir -p $(dir $@)
#	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<



# build Assembly startup code
$(BUILD_DIR)/USBCDCH745FUZZERGPS-Receiver/CM4/Core/Startup/%.o: $(PROJ_DIR)/Core/Startup/%.s |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(ASFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build COMMON CODE
$(BUILD_DIR)/USBCDCH745FUZZERGPS-Receiver/Common/%.o: $(COMMON_DIR)/Common/%.c |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


#build FreeRTOS kernel
$(BUILD_DIR)/Common/FreeRTOS-Kernel/%.o: $(ROOT_DIR)/Common/FreeRTOS-Kernel/%.c |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<




# build instrumented test
#$(BUILD_DIR)/Common/Test/%.o: $(ROOT_DIR)/Common/Test/%.c | $(BUILD_DIR) $(DEP_DIR) 
#	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
#	@mkdir -p $(dir $@)
#	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS)  -fsanitize-coverage=trace-pc-guard  $(INCLUDE_PATHS) -c -o $@ $<


#$(CC) -mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(DEP_DIR)/startup_stm32l152retx.d" -MT"$(BUILD_DIR)/Core/Startup/startup_stm32l152retx.o" --specs=nano.specs -mfloat-abi=soft -mthumb  -o $@ $< 
   