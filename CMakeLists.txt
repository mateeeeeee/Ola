cmake_minimum_required(VERSION 3.20)
project(Wave)

find_package(LLVM REQUIRED CONFIG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(WAVE_COMPILER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/WaveCompiler/)
set(WAVE_TESTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/WaveTests/)
set(WAVE_BINARY_PATH ${CMAKE_BINARY_DIR}/bin/)

if(MSVC)
	add_definitions(/MT)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

if(CMAKE_CONFIGURATION_TYPES)
	message("Multi-configuration generator")
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
elseif()
	message("Single-configuration generator")
endif()

add_compile_definitions(
  "$<$<CONFIG:DEBUG>:WAVE_DEBUG_BUILD>"
  "$<$<CONFIG:RELEASE>: WAVE_RELEASE_BUILD>"
)



add_subdirectory(WaveLib)
add_subdirectory(WaveCompiler)
add_subdirectory(WaveTests)

add_dependencies(WaveCompiler WaveLib)
add_dependencies(WaveTests WaveCompiler)
