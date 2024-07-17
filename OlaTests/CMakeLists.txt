
configure_file(${CMAKE_SOURCE_DIR}/ola_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/autogen/OlaConfig.h)

set(SOURCE
  Tests.cpp
)

set(HEADERS
  TestMacros.h
  autogen/OlaConfig.h
)

set(WAVE_TESTS
	Tests/test_ternary.ola
	Tests/test_while.ola
	Tests/test_additive.ola
	Tests/test_alias.ola
	Tests/test_array.ola
	Tests/test_bit.ola
	Tests/test_dowhile.ola
	Tests/test_enum.ola
	Tests/test_for.ola
	Tests/test_functioncalls.ola
	Tests/test_goto.ola
	Tests/test_ifelse.ola
	Tests/test_increment.ola
	Tests/test_logical.ola
	Tests/test_multiplicative.ola
	Tests/test_plusminus.ola
	Tests/test_relational.ola
	Tests/test_shift.ola
	Tests/test_sizeof.ola
	Tests/test_switch.ola
	Tests/test_string.ola
	Tests/test_implicitcasts.ola
	Tests/test_class.ola
	Tests/test_ref.ola
	Tests/test_inheritance.ola
	Tests/test_polymorphism.ola
	Tests/test_overloading.ola
	Tests/test_constructors.ola
	Tests/test_returns.ola
)

add_executable(OlaTests ${SOURCE} ${HEADERS} ${WAVE_TESTS})

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

target_link_libraries(OlaTests PRIVATE gtest_main)

target_include_directories(OlaTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(OlaTests PRIVATE ${CMAKE_SOURCE_DIR}/OlaCompiler/)


