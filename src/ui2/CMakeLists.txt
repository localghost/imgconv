find_package(Qt5 COMPONENTS Qml Quick Widgets)

include_directories(${Qt5_INCLUDE_DIRS})

set(SOURCES
  main.cpp
)

set(HEADERS
)

set(UIS
    #Main.qml
    #MainForm.ui.qml
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_add_resources(RESOURCES resources.qrc)

add_executable("${TARGET_UI}2"
    MACOSX_BUNDLE
    ${SOURCES}
    ${UIS}
    ${GENERATED_SOURCES}
    ${RESOURCES}
    )
#target_link_libraries("${TARGET_UI}2" ${TARGET_BASE} ${TARGET_IM} )
qt5_use_modules("${TARGET_UI}2" Qml Quick Widgets)
