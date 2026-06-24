project(qt-stable-diffusion-utils
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 COMPONENTS
    Core
    Gui
    Quick
    Qml
  REQUIRED
)

set(QSDUTILS_HEADERS
    objectmodel.h
    pointer-macros.h
    property-macros.h
    qmlstringlist.h
    qsdpath.h
    qsdpathing.h
    qsdutils.h
)
set(QSDUTILS_CXX
    qmlstringlist.cpp
    qsdpath.cpp
    qsdpathing.cpp
    qsdutils.cpp
)

set(QSDUTILS_QML)
qt_add_library(qt-stable-diffusion-utils STATIC)
qt_add_qml_module(qt-stable-diffusion-utils
    URI QSDUTILS
    VERSION 1.0
    SOURCES
      ${QSDUTILS_HEADERS}
      ${QSDUTILS_CXX}
    # QML_FILES
    #   ${QHF_QML}
)


target_include_directories(qt-stable-diffusion-utils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
)

target_link_libraries(qt-stable-diffusion-utils PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
)
