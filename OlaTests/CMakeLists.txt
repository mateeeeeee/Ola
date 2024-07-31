configure_file(${CMAKE_SOURCE_DIR}/ola_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/autogen/OlaConfig.h)

set(SOURCE
  Tests.cpp
)

set(HEADERS
  TestMacros.h
  autogen/OlaConfig.h
)

set(OLA_LLVM_TESTS
	Tests/LLVM/test_ternary.ola
	Tests/LLVM/test_while.ola
	Tests/LLVM/test_additive.ola
	Tests/LLVM/test_alias.ola
	Tests/LLVM/test_array.ola
	Tests/LLVM/test_bit.ola
	Tests/LLVM/test_dowhile.ola
	Tests/LLVM/test_enum.ola
	Tests/LLVM/test_for.ola
	Tests/LLVM/test_functioncalls.ola
	Tests/LLVM/test_goto.ola
	Tests/LLVM/test_ifelse.ola
	Tests/LLVM/test_increment.ola
	Tests/LLVM/test_logical.ola
	Tests/LLVM/test_multiplicative.ola
	Tests/LLVM/test_plusminus.ola
	Tests/LLVM/test_relational.ola
	Tests/LLVM/test_shift.ola
	Tests/LLVM/test_sizeof.ola
	Tests/LLVM/test_switch.ola
	Tests/LLVM/test_string.ola
	Tests/LLVM/test_implicitcasts.ola
	Tests/LLVM/test_class.ola
	Tests/LLVM/test_ref.ola
	Tests/LLVM/test_inheritance.ola
	Tests/LLVM/test_polymorphism.ola
	Tests/LLVM/test_overloading.ola
	Tests/LLVM/test_constructors.ola
	Tests/LLVM/test_returns.ola
)

set(OLA_CUSTOM_TESTS
	Tests/Custom/test_ternary.ola
	Tests/Custom/test_while.ola
	Tests/Custom/test_additive.ola
	Tests/Custom/test_alias.ola
	Tests/Custom/test_array.ola
	Tests/Custom/test_bit.ola
	Tests/Custom/test_dowhile.ola
	Tests/Custom/test_enum.ola
	Tests/Custom/test_for.ola
	Tests/Custom/test_functioncalls.ola
	Tests/Custom/test_goto.ola
	Tests/Custom/test_ifelse.ola
	Tests/Custom/test_increment.ola
	Tests/Custom/test_logical.ola
	Tests/Custom/test_multiplicative.ola
	Tests/Custom/test_plusminus.ola
	Tests/Custom/test_relational.ola
	Tests/Custom/test_shift.ola
	Tests/Custom/test_sizeof.ola
	Tests/Custom/test_switch.ola
	Tests/Custom/test_string.ola
	Tests/Custom/test_implicitcasts.ola
	Tests/Custom/test_class.ola
	Tests/Custom/test_ref.ola
	Tests/Custom/test_inheritance.ola
	Tests/Custom/test_polymorphism.ola
	Tests/Custom/test_overloading.ola
	Tests/Custom/test_constructors.ola
	Tests/Custom/test_returns.ola
)

add_executable(OlaTests ${SOURCE} ${HEADERS} ${OLA_LLVM_TESTS} ${OLA_CUSTOM_TESTS})

source_group(" " FILES ${SOURCE} ${HEADERS})
source_group("Tests/LLVM" FILES ${OLA_LLVM_TESTS})
source_group("Tests/Custom" FILES ${OLA_CUSTOM_TESTS})

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


