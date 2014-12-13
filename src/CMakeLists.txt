include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TARGET_IM "imgconv-im")
set(TARGET_UI "imgconv")

find_package(PkgConfig)

add_definitions("-std=c++11")


pkg_search_module(magick REQUIRED MagickCore)

include_directories(${magick_INCLUDE_DIRS})
link_directories(${magick_LIBRARY_DIRS})

add_subdirectory(im)
add_subdirectory(ui)
