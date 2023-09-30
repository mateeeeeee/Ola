# Install script for directory: C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/examples/Kaleidoscope

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/LLVM")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/BuildingAJIT/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter5/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter7/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter8/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/examples/Kaleidoscope/Chapter9/cmake_install.cmake")
endif()

