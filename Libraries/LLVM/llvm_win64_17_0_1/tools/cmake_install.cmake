# Install script for directory: C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/tools

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
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/lto/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/gold/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-ar/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-config/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-lto/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-profdata/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/bugpoint/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/bugpoint-passes/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/dsymutil/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/dxil-dis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/lli/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-as/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-as-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-bcanalyzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-c-test/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-cat/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-cfi-verify/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-cov/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-cvtres/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-cxxdump/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-cxxfilt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-cxxmap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-debuginfo-analyzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-debuginfod/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-debuginfod-find/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-diff/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-dis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-dis-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-dlang-demangle-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-dwarfdump/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-dwarfutil/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-dwp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-exegesis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-extract/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-gsymutil/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-ifs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-isel-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-itanium-demangle-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-jitlink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-libtool-darwin/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-link/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-lipo/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-lto2/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-mc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-mc-assemble-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-mc-disassemble-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-mca/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-microsoft-demangle-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-ml/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-modextract/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-mt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-nm/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-objcopy/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-objdump/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-opt-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-opt-report/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-pdbutil/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-profgen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-rc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-readobj/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-reduce/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-remark-size-diff/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-remarkutil/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-rtdyld/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-rust-demangle-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-shlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-sim/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-size/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-special-case-list-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-split/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-stress/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-strings/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-symbolizer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-tapi-diff/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-tli-checker/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-undname/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-xray/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-yaml-numeric-parser-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/llvm-yaml-parser-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/obj2yaml/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/opt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/opt-viewer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/remarks-shlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/sancov/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/sanstats/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/verify-uselistorder/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/vfabi-demangle-fuzzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/xcode-toolchain/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/tools/yaml2obj/cmake_install.cmake")
endif()

