# Install script for directory: /home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/alejandro/Documents/semi-fuzz-project/SHiFT/toolchains/gcc-linaro12.3.1-0x20020000/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/CommonSHIFT/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/FuzzerSHIFT/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/board/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/component/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/freertos/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/usb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/build/utilities/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/alejandro/Documents/semi-fuzz-project/SHiFT/SHiFTcode/TemplateNXPfreedom/frdmk66f/dev_cdc_vcom_freertos/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
