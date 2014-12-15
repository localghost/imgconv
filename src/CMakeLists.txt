include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TARGET_BASE "imgconv-base")
set(TARGET_IM "imgconv-im")
set(TARGET_UI "imgconv")

add_definitions("-std=c++11")

find_package(PkgConfig)

# it is required here since `ui` includes MagickCore headers
# via `im` headers
# TODO move it to `im` once the MagickCore is completely hidden
# from `ui`
pkg_search_module(magick REQUIRED MagickCore)
include_directories(${magick_INCLUDE_DIRS})
link_directories(${magick_LIBRARY_DIRS})
add_definitions("-DMAGICKCORE_HDRI_ENABLE=0")
add_definitions("-DMAGICKCORE_QUANTUM_DEPTH=16")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(base)
add_subdirectory(im)
add_subdirectory(ui)
