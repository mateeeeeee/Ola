
set(SOURCE
  wavelib.cpp
)

set(HEADERS
  waveassert.h
  waveio.h
  wavemath.h
  wavestring.h
)

add_library(WaveLib ${SOURCE} ${HEADERS})

source_group(" " FILES ${SOURCE} ${HEADERS})

target_include_directories(WaveLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
target_link_libraries(WaveLib PRIVATE legacy_stdio_definitions)
endif()

install(TARGETS WaveLib DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/WaveLib)

#add_custom_command(TARGET WaveLib POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:WaveLib> ${PROJECT_BINARY_DIR}/WaveLib.lib
#)
