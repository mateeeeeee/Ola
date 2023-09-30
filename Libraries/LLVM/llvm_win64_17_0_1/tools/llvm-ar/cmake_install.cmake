# Install script for directory: C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/tools/llvm-ar

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "llvm-ar" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/Debug/bin/llvm-ar.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/Release/bin/llvm-ar.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/MinSizeRel/bin/llvm-ar.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/RelWithDebInfo/bin/llvm-ar.exe")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "llvm-ranlib" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/cmake/modules/LLVMInstallSymlink.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "llvm-ranlib" OR NOT CMAKE_INSTALL_COMPONENT)
  install_symlink("llvm-ranlib.exe" "llvm-ar.exe" "bin" "copy")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "llvm-lib" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/cmake/modules/LLVMInstallSymlink.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "llvm-lib" OR NOT CMAKE_INSTALL_COMPONENT)
  install_symlink("llvm-lib.exe" "llvm-ar.exe" "bin" "copy")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "llvm-dlltool" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/cmake/modules/LLVMInstallSymlink.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "llvm-dlltool" OR NOT CMAKE_INSTALL_COMPONENT)
  install_symlink("llvm-dlltool.exe" "llvm-ar.exe" "bin" "copy")
endif()

