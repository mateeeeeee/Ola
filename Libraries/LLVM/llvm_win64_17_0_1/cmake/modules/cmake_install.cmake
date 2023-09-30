# Install script for directory: C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/cmake/modules

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "cmake-exports" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm/LLVMExports.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm/LLVMExports.cmake"
         "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/cmake/modules/CMakeFiles/Export/488324e79e44ed4aa1c9ea53c513c58e/LLVMExports.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm/LLVMExports-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm/LLVMExports.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm" TYPE FILE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/cmake/modules/CMakeFiles/Export/488324e79e44ed4aa1c9ea53c513c58e/LLVMExports.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm" TYPE FILE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/cmake/modules/CMakeFiles/Export/488324e79e44ed4aa1c9ea53c513c58e/LLVMExports-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm" TYPE FILE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/cmake/modules/CMakeFiles/Export/488324e79e44ed4aa1c9ea53c513c58e/LLVMExports-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm" TYPE FILE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/cmake/modules/CMakeFiles/Export/488324e79e44ed4aa1c9ea53c513c58e/LLVMExports-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm" TYPE FILE FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/cmake/modules/CMakeFiles/Export/488324e79e44ed4aa1c9ea53c513c58e/LLVMExports-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "cmake-exports" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm" TYPE FILE FILES
    "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/cmake/modules/CMakeFiles/LLVMConfig.cmake"
    "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm_win64_17_0_1/./lib/cmake/llvm/LLVMConfigVersion.cmake"
    "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/cmake/modules/LLVM-Config.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "cmake-exports" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/llvm" TYPE DIRECTORY FILES "C:/Users/mateb/OneDrive/Desktop/Projekti/LLVM/llvm-project_17_0_1/llvm/cmake/modules/." FILES_MATCHING REGEX "/[^/]*\\.cmake$" REGEX "/llvmconfig\\.cmake$" EXCLUDE REGEX "/llvmconfigextensions\\.cmake$" EXCLUDE REGEX "/llvmconfigversion\\.cmake$" EXCLUDE REGEX "/llvm\\-config\\.cmake$" EXCLUDE REGEX "/gethosttriple\\.cmake$" EXCLUDE REGEX "/llvm\\-driver\\-template\\.cpp\\.in$")
endif()

