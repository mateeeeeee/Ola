
set(SOURCE
  main.cpp
)

set(TEST_FILES
	Test/test.ola
)

add_executable(OlaPlayground ${SOURCE} ${TEST_FILES})
set_target_properties(OlaPlayground PROPERTIES OUTPUT_NAME OlaPlayground)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE} ${TEST_FILES})

target_include_directories(OlaPlayground PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(OlaPlayground PRIVATE ${CMAKE_SOURCE_DIR}/OlaCompiler/)

target_link_libraries(OlaPlayground PRIVATE OlaCompiler)

install(TARGETS OlaPlayground DESTINATION bin)

