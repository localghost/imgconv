set(SOURCES
   image.cpp
   imagefilter.cpp
   resizefilter.cpp
   )

add_library(${TARGET_IM} STATIC ${SOURCES})
target_link_libraries(${TARGET_IM} ${magick_LIBRARIES}) 
set_target_properties(${TARGET_IM} PROPERTIES COMPILE_DEFINITIONS "MAGICKCORE_HDRI_ENABLE=0;MAGICKCORE_QUANTUM_DEPTH=16") 
