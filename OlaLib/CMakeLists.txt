
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

add_library(OlaLib ${SOURCE} ${HEADERS})

source_group(" " FILES ${SOURCE} ${HEADERS})

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
