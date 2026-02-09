set(SOURCE
  TestLexer.cpp
  TestParser.cpp
  TestSema.cpp
  TestIR.cpp
  TestInterpreter.cpp
  TestIRPasses.cpp
  TestMachineIR.cpp
  TestRegisterAlloc.cpp
)

set(SOURCE_E2E
  TestE2E.cpp
)

set(SOURCE_INTERPRETER
  TestE2EInterpreter.cpp
)

set(OLA_TESTS
	Tests/test_additive.ola
	Tests/test_alias.ola
	Tests/test_array.ola
	Tests/test_bit.ola
	Tests/test_class.ola
	Tests/test_const.ola
	Tests/test_constructors.ola
	Tests/test_dowhile.ola
	Tests/test_enum.ola
	Tests/test_floats.ola
	Tests/test_for.ola
	Tests/test_functioncalls.ola
	Tests/test_goto.ola
	Tests/test_ifelse.ola
	Tests/test_implicitcasts.ola
	Tests/test_increment.ola
	Tests/test_inheritance.ola
	Tests/test_literals.ola
	Tests/test_logical.ola
	Tests/test_multiplicative.ola
	Tests/test_overloading.ola
	Tests/test_plusminus.ola
	Tests/test_polymorphism.ola
	Tests/test_ptr.ola
	Tests/test_ref.ola
	Tests/test_relational.ola
	Tests/test_returns.ola
	Tests/test_shift.ola
	Tests/test_sizeof.ola
	Tests/test_string.ola
	Tests/test_switch.ola
	Tests/test_ternary.ola
	Tests/test_while.ola
	Tests/test_dereference.ola
	Tests/test_new.ola
	Tests/test_vector.ola
	Tests/test_pair.ola
	Tests/test_foreach.ola
	Tests/test_auto.ola
	Tests/test_recursion.ola
	Tests/test_scope.ola
	Tests/test_static.ola
	Tests/test_default_params.ola
)

add_executable(OlaTests ${SOURCE})
add_executable(OlaTestsE2E ${SOURCE_E2E})
add_executable(OlaTestsInterpreter ${SOURCE_INTERPRETER})

source_group(" " FILES ${SOURCE})
source_group("Tests" FILES ${OLA_TESTS})

set(GOOGLETEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
add_subdirectory(${GOOGLETEST_PATH} ${CMAKE_BINARY_DIR}/googletest)

target_link_libraries(OlaTests PRIVATE gtest_main OlaCompiler)
target_link_libraries(OlaTestsE2E PRIVATE gtest_main OlaCompiler)
target_link_libraries(OlaTestsInterpreter PRIVATE gtest_main OlaCompiler)

target_include_directories(OlaTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(OlaTestsE2E PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(OlaTestsInterpreter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Force-include core type headers so compiler types (Bool, Int, etc.) are available in test files
if(MSVC)
    target_compile_options(OlaTests PRIVATE
        /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
        /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
    )
    target_compile_options(OlaTestsE2E PRIVATE
        /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
        /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
    )
    target_compile_options(OlaTestsInterpreter PRIVATE
        /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
        /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(OlaTests PRIVATE
        "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
        "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
    )
    target_compile_options(OlaTestsE2E PRIVATE
        "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
        "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
    )
    target_compile_options(OlaTestsInterpreter PRIVATE
        "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
        "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
    )
endif()

# Configure the path to Ola executable for tests
if(CMAKE_CONFIGURATION_TYPES)
    set(OLA_EXE_PATH "$<TARGET_FILE:OlaDriver>")
else()
    set(OLA_EXE_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Ola${CMAKE_EXECUTABLE_SUFFIX}")
endif()

target_compile_definitions(OlaTests PRIVATE
    OLA_EXE_PATH="${OLA_EXE_PATH}"
    OLA_TESTS_PATH="${CMAKE_SOURCE_DIR}/OlaTests/"
)

target_compile_definitions(OlaTestsE2E PRIVATE
    OLA_EXE_PATH="${OLA_EXE_PATH}"
    OLA_TESTS_PATH="${CMAKE_SOURCE_DIR}/OlaTests/"
)

target_compile_definitions(OlaTestsInterpreter PRIVATE
    OLA_EXE_PATH="${OLA_EXE_PATH}"
    OLA_TESTS_PATH="${CMAKE_SOURCE_DIR}/OlaTests/"
)

if(LLVM_FOUND)
    add_executable(OlaTestsLLVM TestE2ELLVM.cpp)
    target_link_libraries(OlaTestsLLVM PRIVATE gtest_main OlaCompiler)
    target_include_directories(OlaTestsLLVM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    if(MSVC)
        target_compile_options(OlaTestsLLVM PRIVATE
            /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
            /FI"${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(OlaTestsLLVM PRIVATE
            "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Types.h"
            "SHELL:-include ${CMAKE_SOURCE_DIR}/OlaCompiler/Core/Defines.h"
        )
    endif()
    target_compile_definitions(OlaTestsLLVM PRIVATE
        OLA_EXE_PATH="${OLA_EXE_PATH}"
        OLA_TESTS_PATH="${CMAKE_SOURCE_DIR}/OlaTests/"
    )
endif()
