set(SOURCES
   image.cpp
   imagefilter.cpp
   resizefilter.cpp
   )

set(HEADERS
   imageformat.h
   )

add_library(${TARGET_IM} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET_IM} ${TARGET_BASE} ${magick_LIBRARIES})
