# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

file(GLOB FILESNORMAL
  src/MonitorAndTargetSingleCore.c
 )


file(GLOB FILESTARGET
 Target/src/test.c
 )
 
#add flags for ASAN and SANCOV
#set_source_files_properties(${FILESTARGET} PROPERTIES COMPILE_FLAGS -fsanitize-coverage=trace-pc -fsanitize=address  -fno-common )

set_source_files_properties(${FILESTARGET} PROPERTIES COMPILE_FLAGS -fsanitize-coverage=trace-pc -fsanitize=address  -fno-common )


# add_library: With this declaration, you express the intent to build a library. 
# The first argument, here its pico-shift-register, is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(FuzzerSHIFT OBJECT ${FILESNORMAL} ${FILESTARGET} )

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  FuzzerSHIFT 
 
)





# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(
  FuzzerSHIFT
  PUBLIC
  ./
  ../CMSIS
  ../source
  ../board
  ../device
  ../drivers
  ../FuzzerSHIFT/inc
  ../CommonSHIFT/FreeRTOS-Kernel/include
  ../CommonSHIFT/FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU
  ../CommonSHIFT/Fuzzing/Inc
  ../CommonSHIFT/AsanRuntime/ASANMCU/inc
  ../usb/device/include
  ../usb/include
  ../component/osa
  ../component/lists
  ./inc
  ./Target/inc
)
