cmake_minimum_required(VERSION 3.20)
project(Ola)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(OLA_COMPILER_PATH 		${CMAKE_CURRENT_SOURCE_DIR}/OlaCompiler/)
set(OLA_LIB_PATH    		${CMAKE_CURRENT_SOURCE_DIR}/OlaLib/)
set(OLA_TESTS_PATH    		${CMAKE_CURRENT_SOURCE_DIR}/OlaTests/)
set(OLA_PLAYGROUND_PATH   	${CMAKE_CURRENT_SOURCE_DIR}/OlaPlayground/)
set(OLA_BINARY_PATH   		${CMAKE_BINARY_DIR}/bin/)


if(MSVC)
	add_compile_options(/MP)
	add_definitions(/MT)
endif()

if(CMAKE_CONFIGURATION_TYPES)
	message("Multi-configuration generator")
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
elseif()
	message("Single-configuration generator")
endif()

add_compile_definitions(
  "$<$<CONFIG:DEBUG>:DEBUG>"
  "$<$<CONFIG:RELEASE>:RELEASE>"
)

add_subdirectory(OlaLib)
add_subdirectory(OlaCompiler)
add_subdirectory(OlaTests)
add_subdirectory(OlaPlayground)

add_dependencies(OlaCompiler OlaLib)
add_dependencies(OlaDriver OlaCompiler)
add_dependencies(OlaTests OlaDriver)
add_dependencies(OlaPlayground OlaCompiler)