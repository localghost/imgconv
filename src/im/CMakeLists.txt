set(SOURCES
   image.cpp
   imagefilter.cpp
   resizefilter.cpp
   )

add_library(${TARGET_IM} STATIC ${SOURCES})
target_link_libraries(${TARGET_IM} ${magick_LIBRARIES}) 
