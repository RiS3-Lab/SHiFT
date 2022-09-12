ROOT_DIR := $(abspath ..)
PROJ_DIR := $(abspath .)
BUILD_DIR  := $(PROJ_DIR)/build
Q ?= @

# use the following command to compile using LLVM
#COMPILER=clang make


DRIVERS_ROOT_DIR := $(PROJ_DIR)/Drivers/STM32H7xx_HAL_Driver/Src

MIDDLEWARES_ROOT_DIR := $(PROJ_DIR)/Middlewares

USBDEVICE_ROOT_DIR := $(PROJ_DIR)/USB_DEVICE

FUZZING_ROOT_DIR :=  $(ROOT_DIR)/Common/Fuzzing
TEST_ROOT_DIR :=  $(ROOT_DIR)/Common/Test

#SANITIZER_ROOT_DIR := $(ROOT_DIR)/Common/ASANMCU


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
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_crc.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_crc_ex.c \
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
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_pcd.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_pcd_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_pwr.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_pwr_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_rcc.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_rcc_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_rng.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_rng_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_tim.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_tim_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_uart.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_hal_uart_ex.c \
$(DRIVERS_ROOT_DIR)/stm32h7xx_ll_usb.c



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


MIDDLEWARES_SOURCES += \
$(MIDDLEWARES_ROOT_DIR)/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
$(MIDDLEWARES_ROOT_DIR)/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
$(MIDDLEWARES_ROOT_DIR)/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
$(MIDDLEWARES_ROOT_DIR)/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c


USB_DEVICE_SOURCES += \
$(USBDEVICE_ROOT_DIR)/App/usbd_cdc_if.c \
$(USBDEVICE_ROOT_DIR)/App/usbd_desc.c \
$(USBDEVICE_ROOT_DIR)/App/usb_device.c \
$(USBDEVICE_ROOT_DIR)/Target/usbd_conf.c


PROJECT_SRC_DIR = $(PROJ_DIR)/Core/Src


TEST_SRC = \
$(TEST_ROOT_DIR)/Src/testmodbus.c \
$(TEST_ROOT_DIR)/Src/test.c \
$(TEST_ROOT_DIR)/Src/test2.c \


#$(TEST_ROOT_DIR)/Src/asan_test.c




FUZZING_SOURCES += \
$(FUZZING_ROOT_DIR)/Src/sanitizer.c \
$(FUZZING_ROOT_DIR)/Src/ring.c \
$(FUZZING_ROOT_DIR)/Src/fuzzing.c \
$(FUZZING_ROOT_DIR)/Src/app_main.c \
$(FUZZING_ROOT_DIR)/Src/memfault_handler.c \
$(FUZZING_ROOT_DIR)/Src/FuzzerTargetSingleCore.c


#SANITIZER_SOURCES += \
#$(SANITIZER_ROOT_DIR)/McuASAN.c 

SRC_FILES += \
$(PROJECT_SRC_DIR)/main.c \
$(PROJECT_SRC_DIR)/stm32h7xx_hal_msp.c \
$(PROJECT_SRC_DIR)/stm32h7xx_it.c \
$(PROJECT_SRC_DIR)/stm32h7xx_hal_timebase_tim.c \
$(PROJECT_SRC_DIR)/syscalls.c \
$(PROJECT_SRC_DIR)/sysmem.c \
$(PROJECT_SRC_DIR)/system_stm32h7xx.c \
$(TEST_SRC) \
$(DRIVERS_SOURCES) \
$(MIDDLEWARES_SOURCES) \
$(USB_DEVICE_SOURCES) \
$(FUZZING_SOURCES) \
$(FREERTOS_SOURCES)
#$(SANITIZER_SOURCES)



OBJ_FILES := $(patsubst $(ROOT_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))


PROJECT_STARTUP_DIR = $(PROJ_DIR)/Core/Startup

STARTUP_SOURCES += \
$(PROJECT_STARTUP_DIR)/startup_stm32h743zitx.s


OBJ_FILES := $(OBJ_FILES) \
$(patsubst $(ROOT_DIR)/%.s,$(BUILD_DIR)/%.o,$(STARTUP_SOURCES))


INCLUDE_PATHS += \
  -I$(PROJ_DIR)/Core/Inc \
  -I$(PROJ_DIR)/Drivers/CMSIS/Device/ST/STM32H7xx/Include \
  -I$(PROJ_DIR)/Drivers/CMSIS/Include \
  -I$(PROJ_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc \
  -I$(PROJ_DIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Inc \
  -I$(PROJ_DIR)/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc \
  -I$(PROJ_DIR)/USB_DEVICE/App \
  -I$(PROJ_DIR)/USB_DEVICE/Target \
  -I$(ROOT_DIR)/Common/Fuzzing/Inc \
  -I$(ROOT_DIR)/Common/Test/Inc \
  -I$(ROOT_DIR)/Common/FreeRTOS-Kernel/include \
  -I$(ROOT_DIR)/Common/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU 


# Note: These arguments will be used by clang to select
# the specific architecture target when we use the
# generic --target=arm-none-eabi
ARCH_CFLAGS += \
  -mthumb -mcpu=cortex-m7 \
  -mfloat-abi=hard -mfpu=fpv5-d16

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
CFLAGS += -DUSE_HAL_DRIVER 
CFLAGS += -DSTM32H743xx 
CFLAGS += -Wno-parentheses-equality 
CFLAGS +=  $(COMPILER_SPECIFIC_CFLAGS) 
CFLAGS +=  $(ARCH_CFLAGS) 
CFLAGS +=  $(CLI_CFLAG_OVERRIDES)



ASFLAGS += -g3 -DDEBUG -c 
ASFLAGS += -x assembler-with-cpp 
#ASFLAGS += --specs=nano.specs 
ASFLAGS += $(ARCH_CFLAGS)


TARGET ?= stm32h743
LDSCRIPT = $(PROJ_DIR)/STM32H743ZITX_FLASH_MPU.ld
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


H743AM := $(shell STM32_Programmer_CLI --Connect port=SWD sn=002800243156501420323443 > /dev/null 2>&1 ; echo $$?)
H743CH := $(shell STM32_Programmer_CLI --Connect port=SWD sn=0046003D3137511239383538 > /dev/null 2>&1 ; echo $$?)

flash: $(TARGET_ELF)
ifeq ($(H743AM),0)
	STM32_Programmer_CLI -c port=SWD -w $(BUILD_DIR)/stm32h743.elf -v -ob displ -hardRst  sn=002800243156501420323443
else
ifeq ($(H743CH),0)
	STM32_Programmer_CLI -c port=SWD -w $(BUILD_DIR)/stm32h743.elf -v -ob displ -hardRst  sn=0046003D3137511239383538
else
	@echo "ERROR: No Board H743 found"
endif	
endif	
    


$(TARGET_ELF): $(OBJ_FILES)  $(LDSCRIPT)
	@echo "Linking library"
  #$(Q) $(CC) $(OBJ_FILES)  $(LDFLAGS) -o $@
	$(Q) arm-none-eabi-gcc $(OBJ_FILES)  $(LDFLAGS) -o $@
	@echo "Generated $(patsubst $(ROOT_DIR)/%,%,$@)"
	arm-none-eabi-objcopy -O binary $(TARGET_ELF)  "$(BUILD_DIR)/$(TARGET).bin"
  
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

# build core files
$(BUILD_DIR)/Template-USBCDCH743FUZZER/Core/Src/%.o: $(PROJ_DIR)/Core/Src/%.c | $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build drivers
$(BUILD_DIR)/Template-USBCDCH743FUZZER/Drivers/%.o: $(PROJ_DIR)/Drivers/%.c | $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build Fuzzing files
$(BUILD_DIR)/Common/Fuzzing/%.o: $(ROOT_DIR)/Common/Fuzzing/%.c |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build middlewares
$(BUILD_DIR)/Template-USBCDCH743FUZZER/Middlewares/%.o: $(PROJ_DIR)/Middlewares/%.c | $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build USB CDC DEVICE
$(BUILD_DIR)/Template-USBCDCH743FUZZER/USB_DEVICE/%.o: $(PROJ_DIR)/USB_DEVICE/%.c | $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<

# build Assembly startup code
$(BUILD_DIR)/Template-USBCDCH743FUZZER/Core/Startup/%.o: $(PROJ_DIR)/Core/Startup/%.s | $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(ASFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


#build FreeRTOS kernel
$(BUILD_DIR)/Common/FreeRTOS-Kernel/%.o: $(ROOT_DIR)/Common/FreeRTOS-Kernel/%.c |  $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS) $(INCLUDE_PATHS) -c -o $@ $<


# build instrumented test
$(BUILD_DIR)/Common/Test/%.o: $(ROOT_DIR)/Common/Test/%.c | $(BUILD_DIR) $(DEP_DIR) 
	@echo "Compiling $(patsubst $(ROOT_DIR)/%,%,$<)"
	@mkdir -p $(dir $@)
	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS)  -fsanitize-coverage=trace-pc-guard  $(INCLUDE_PATHS) -c -o $@ $<

#	$(Q) $(CC) $(DEP_CFLAGS) $(CFLAGS)   -fsanitize=kernel-address   $(INCLUDE_PATHS) -c -o $@ $<



#$(CC) -mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(DEP_DIR)/startup_stm32l152retx.d" -MT"$(BUILD_DIR)/Core/Startup/startup_stm32l152retx.o" --specs=nano.specs -mfloat-abi=soft -mthumb  -o $@ $< 
   