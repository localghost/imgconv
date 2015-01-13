find_package(Qt5Widgets)
find_package(Qt5Concurrent)

set(SOURCES
  main.cpp
  mainwindow.cpp
  dialog.cpp
  pipelineeditor.cpp
  action.cpp
  resizeaction.cpp
  exportaction.cpp
  actionregistry.cpp
)

set(HEADERS
  mainwindow.h
  dialog.h
  pipelineeditor.h
  action.h
  resizeaction.h
  exportaction.h
  actionregistry.h
)

set(UIS
  mainwindow.ui
  dialog.ui
  pipelineeditor.ui
  resizeaction.ui
  exportaction.ui
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${TARGET_UI}
    MACOSX_BUNDLE
    ${SOURCES}
    ${UIS}
    ${GENERATED_SOURCES}
    )
target_link_libraries(${TARGET_UI} ${TARGET_BASE} ${TARGET_IM} ${Qt5Widgets} ${Qt5Concurrent})
qt5_use_modules(${TARGET_UI} Widgets Concurrent)
