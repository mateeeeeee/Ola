set(SOURCE
  Tests.cpp
)

set(HEADERS
  TestMacros.h
)

add_executable(WaveTests ${SOURCE} ${HEADERS})

source_group(" " FILES ${SOURCE} ${HEADERS})

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
		cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(WaveTests PRIVATE gtest_main)

target_include_directories(WaveTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(WaveTests PRIVATE ${CMAKE_SOURCE_DIR}/WaveCompiler/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Tests DESTINATION ${CMAKE_BINARY_DIR}/WaveTests/Tests)

