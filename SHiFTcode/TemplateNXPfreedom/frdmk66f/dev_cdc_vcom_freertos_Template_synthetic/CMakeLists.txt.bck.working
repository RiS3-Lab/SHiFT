cmake_minimum_required(VERSION 3.15.3)

# Optional: print out extra messages to see what is going on. Comment it to have less verbose messages
set(CMAKE_VERBOSE_MAKEFILE ON)

# enable export of compiler commands to compile_commands.json
#set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Path to toolchain file. This one has to be before 'project()' below
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake)

# Setup project, output and linker file
set(BUILD_FOLDER ./build)
project(EVKMIMXRT1176_CMake)
set(EXECUTABLE ${PROJECT_NAME}.elf)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(LINKER_FILE "frdmk66f_dev_cdc_vcom_freertos_Debug.ld")

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

# Optional: issue a message to be sure it uses the correct toolchain file.
message(STATUS "CMAKE_TOOLCHAIN_FILE is: ${CMAKE_TOOLCHAIN_FILE}")

# List of source files
set(SRC_FILES
  source/printhelpers.c
  source/virtual_com.c
  source/usb_device_descriptor.c
  source/virtual_com.c
  startup/startup_mk66f18.c  
  device/system_MK66F18.c
  
)

include_directories(

./usb/device/class
./usb/device/class/cdc
)


# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

# List of compiler defines, prefix with -D compiler option. Copy from the project settings
add_compile_options(
-DCPU_MK66FN2M0VMD18 
-DCPU_MK66FN2M0VMD18_cm4 
-DSDK_OS_FREE_RTOS 
-DSERIAL_PORT_TYPE_UART=1 
-D_DEBUG=1 
-DSDK_DEBUGCONSOLE=1 
-DUSB_STACK_BM 
-DFSL_OSA_BM_TASK_ENABLE=0 
-DFSL_OSA_BM_TIMER_CONFIG=0 
-DMCUXPRESSO_SDK 
-DSDK_OS_BAREMETAL 
-DCR_INTEGER_PRINTF 
-D__MCUXPRESSO 
-D__USE_CMSIS 
-DDEBUG
-D__NEWLIB__
 
-std=gnu11  
-O1
-g 
-c 
-ffunction-sections 
-fdata-sections 
-fno-builtin 
-Wall -fstack-usage  
-mthumb 
-mcpu=cortex-m7 
-mfpu=fpv5-d16 
-mfloat-abi=hard 
-mthumb 
-specs=nano.specs
-specs=nosys.specs

)

target_compile_definitions(${EXECUTABLE} PRIVATE
-DCPU_MK66FN2M0VMD18 
-DCPU_MK66FN2M0VMD18_cm4 
-DSDK_OS_FREE_RTOS 
-DSERIAL_PORT_TYPE_UART=1 
-D_DEBUG=1 
-DSDK_DEBUGCONSOLE=1 
-DUSB_STACK_BM 
-DFSL_OSA_BM_TASK_ENABLE=0 
-DFSL_OSA_BM_TIMER_CONFIG=0 
-DMCUXPRESSO_SDK 
-DSDK_OS_BAREMETAL 
-DCR_INTEGER_PRINTF 
-D__MCUXPRESSO 
-D__USE_CMSIS 
-DDEBUG
-D__NEWLIB__
 

)

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE

-std=gnu11  
-O1 
-g 
-gdwarf-4 
-c 
-ffunction-sections 
-fdata-sections 
-fno-builtin 
-mthumb 
-Wall -fstack-usage  
-mcpu=cortex-m4 
-mfpu=fpv4-sp-d16 
-mfloat-abi=hard 
-mthumb 

-specs=nosys.specs


)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE

  -g
  -Wall
  -fno-common 
  -ffunction-sections 
  -fdata-sections 
  -ffreestanding 
  -fno-builtin 
  -nostdlib 
  -Xlinker -Map=${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.map,--cref
  -mcpu=cortex-m4 
  -mfpu=fpv4-sp-d16 
  -mfloat-abi=hard 
  -mthumb 
   
  -specs=nosys.specs
  -L "${CMAKE_SOURCE_DIR}/ld"
  -T "${LINKER_FILE}"
  
)


add_subdirectory(./CommonSHIFT build/CommonSHIFT)
add_subdirectory(./FuzzerSHIFT build/FuzzerSHIFT)
add_subdirectory(./board     build/board)
add_subdirectory(./component build/component)
add_subdirectory(./drivers   build/drivers)
add_subdirectory(./freertos   build/freertos)
add_subdirectory(./usb build/usb)
add_subdirectory(./utilities build/utilities)


target_link_libraries(
  ${EXECUTABLE}
  utilities
  board
  component
  drivers
  freertos
  usb
  CommonSHIFT
  FuzzerSHIFT

 )

# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}
)

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.s19"
  COMMAND ${CMAKE_OBJCOPY} -O ihex "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex"
  COMMAND ${CMAKE_OBJCOPY} -O binary "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin" 
)