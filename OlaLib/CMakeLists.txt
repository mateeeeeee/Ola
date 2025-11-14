
set(SOURCE
  olalib.cpp
)

set(HEADERS
  olaassert.h
  olaio.h
  olamath.h
  olastring.h
  olafile.h
)

set(OLA_STD_FILES
    std/assert.ola
    std/file.ola
    std/io.ola
    std/math.ola
    std/string.ola
)

add_library(OlaLib ${SOURCE} ${HEADERS} ${OLA_STD_FILES})

source_group(" " FILES ${SOURCE} ${HEADERS})
source_group("std" FILES ${OLA_STD_FILES})

target_include_directories(OlaLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
target_link_libraries(OlaLib PRIVATE legacy_stdio_definitions)
endif()

if(APPLE)
    set_target_properties(OlaLib PROPERTIES
        OSX_ARCHITECTURES "arm64;x86_64"
    )
endif()

install(TARGETS OlaLib DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/OlaLib)
