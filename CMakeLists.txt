cmake_minimum_required(VERSION 3.20)
project(Ola VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(ENABLE_LLVM "Enable LLVM backend" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_PLAYGROUND "Build playground executable" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(OLA_COMPILER_PATH 		${CMAKE_CURRENT_SOURCE_DIR}/OlaCompiler/)
set(OLA_LIB_PATH    		${CMAKE_CURRENT_SOURCE_DIR}/OlaLib/)
set(OLA_TESTS_PATH    		${CMAKE_CURRENT_SOURCE_DIR}/OlaTests/)
set(OLA_PLAYGROUND_PATH   	${CMAKE_CURRENT_SOURCE_DIR}/OlaPlayground/)
set(OLA_BINARY_PATH   		${CMAKE_BINARY_DIR}/bin/)

# Platform-specific executable name
if(WIN32)
	set(OLA_EXE_NAME "Ola.exe")
else()
	set(OLA_EXE_NAME "Ola")
endif()

# Handle different generator types (multi-config vs single-config)
if(CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Multi-configuration generator detected")
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
else()
	message(STATUS "Single-configuration generator detected")
	if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Debug or Release)" FORCE)
	endif()
	message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()

# MSVC-specific settings
if(MSVC)
	add_compile_options(/MP)  # Multi-processor compilation
	# Use modern CMake approach for runtime library
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Define DEBUG/RELEASE macros
add_compile_definitions(
  "$<$<CONFIG:DEBUG>:DEBUG>"
  "$<$<CONFIG:RELEASE>:RELEASE>"
)

# Add subdirectories
add_subdirectory(OlaLib)
add_subdirectory(OlaCompiler)

if(BUILD_TESTS)
	add_subdirectory(OlaTests)
endif()

if(BUILD_PLAYGROUND)
	add_subdirectory(OlaPlayground)
endif()

# Set up dependencies
add_dependencies(OlaCompiler OlaLib)
add_dependencies(OlaDriver OlaCompiler)

if(BUILD_TESTS)
	add_dependencies(OlaTests OlaDriver)
endif()

if(BUILD_PLAYGROUND)
	add_dependencies(OlaPlayground OlaCompiler)
endif()