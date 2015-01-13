set(SOURCES
  image.cpp
  imageaction.cpp
  resizeaction.cpp
  exportaction.cpp
  actionregistry.cpp
)

set(HEADERS
  imageformat.h
  imageaction.h
  resizeaction.h
  exportaction.h
  actionregistry.h
  handle.h
  exceptioninfo.h
)

add_library(${TARGET_IM} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET_IM} ${TARGET_BASE} ${Magick_LIBRARIES} ${Boost_LIBRARIES})
