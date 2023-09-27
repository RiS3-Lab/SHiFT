# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

file(GLOB FILES
  device/source/*.c
  device/source/ehci/*.c
  phy/*.c
 )

# add_library: With this declaration, you express the intent to build a library. 
# The first argument, here its pico-shift-register, is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(usb  OBJECT  ${FILES})

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  usb
)

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(
  usb
  PUBLIC
  ../CMSIS
  ../source
  ../board
  ../device
  ../drivers
  ../component/osa
  ../component/lists
  ./include
  ./device/include
  ./device/source
  ./device/source/ehci
  ./phy
)