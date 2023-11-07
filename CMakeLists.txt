cmake_minimum_required(VERSION 3.20)
project(Wave)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
	add_definitions(/MT)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(WAVE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/)

if(CMAKE_CONFIGURATION_TYPES)
	message("Multi-configuration generator")
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
elseif()
	message("Single-configuration generator")
endif()

add_subdirectory(WaveLib)
add_subdirectory(WaveCompiler)
add_subdirectory(WaveTests)

add_dependencies(WaveCompiler WaveLib)
add_dependencies(WaveTests WaveCompiler)


#target_include_directories(ProjectATargetName PRIVATE
#    ${CMAKE_SOURCE_DIR}/ProjectBDirectory
#)

## Copy the Compiler executable to the Tests build directory
#add_custom_command(TARGET Tests POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE:Compiler>
#    $<TARGET_FILE_DIR:Tests>
#)