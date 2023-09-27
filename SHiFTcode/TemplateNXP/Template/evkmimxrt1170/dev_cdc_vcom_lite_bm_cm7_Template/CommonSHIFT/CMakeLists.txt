# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

file(GLOB FILES
  AsanRuntime/ASANMCU/src/*.c
  FreeRTOS-Kernel/*.c
  FreeRTOS-Kernel/portable/Common/*.c
  FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU/*.c
  FreeRTOS-Kernel/portable/MemMang/*.c
  Fuzzing/Src/app_main.c
  Fuzzing/Src/fault_handlersRTOS.c
  Fuzzing/Src/fuzzing.c
  Fuzzing/Src/ring.c
  Fuzzing/Src/SanitizerGCC.c
  MallocMPU/FreeRTOS/*.h
 )

# add_library: With this declaration, you express the intent to build a library. 
# The first argument, here its pico-shift-register, is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(CommonSHIFT OBJECT ${FILES})

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(  
 CommonSHIFT
  
)

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(
  CommonSHIFT
  PUBLIC
   ./
  ../CMSIS
  ../source
  ../board
  ../device
  ../drivers
  ../FuzzerSHIFT/inc
  ./AsanRuntime/ASANMCU/inc
  ./FreeRTOS-Kernel/include
  ./FreeRTOS-Kernel/portable/GCC/ARM_CM4_MPU
  ./Fuzzing/Inc
  ./MallocMPU/FreeRTOS
)
