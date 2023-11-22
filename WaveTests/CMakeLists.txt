
configure_file(${CMAKE_SOURCE_DIR}/wave_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/autogen/WaveConfig.h)

set(SOURCE
  Tests.cpp
)

set(HEADERS
  TestMacros.h
  autogen/WaveConfig.h
)

set(WAVE_TESTS
	Tests/test_ternary.wv
	Tests/test_while.wv
	Tests/test_additive.wv
	Tests/test_alias.wv
	Tests/test_array.wv
	Tests/test_bit.wv
	Tests/test_const.wv
	Tests/test_dowhile.wv
	Tests/test_enum.wv
	Tests/test_for.wv
	Tests/test_functioncalls.wv
	Tests/test_goto.wv
	Tests/test_ifelse.wv
	Tests/test_increment.wv
	Tests/test_logical.wv
	Tests/test_multiplicative.wv
	Tests/test_plusminus.wv
	Tests/test_relational.wv
	Tests/test_shift.wv
	Tests/test_sizeof.wv
	Tests/test_switch.wv
	Tests/test_string.wv
	Tests/test_floats.wv
	Tests/test_implicitcasts.wv
	Tests/test_class.wv
	Tests/test_ref.wv
)

add_executable(WaveTests ${SOURCE} ${HEADERS} ${WAVE_TESTS})

source_group(" " FILES ${SOURCE} ${HEADERS})
source_group("Tests" FILES ${WAVE_TESTS})

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


