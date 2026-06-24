project(qt-huggingface-example
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)
find_package(Qt6 6.2 COMPONENTS
    Core
    Gui
    Network
    Quick
    Qml
    Concurrent
  REQUIRED
)

set(QHF_EXAMPLE_QML
    main.qml
    HFTrending.qml
    HFCache.qml
    HFGet.qml
)

qt_add_executable(qt-huggingface-example main.cpp )

qt_add_qml_module(qt-huggingface-example
    URI QMLHFEXAMPLE
    VERSION 1.0
    SOURCES
    QML_FILES
      ${QHF_EXAMPLE_QML}
)

# qt-huggingface
# qt-stable-diffusion
target_link_libraries(qt-huggingface-example PRIVATE
    yaml-cpp
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Concurrent
    Qt6::Quick
    Qt6::Qml
    qt-stable-diffusion-utils qt-stable-diffusion-utilsplugin
    qt-huggingfaceplugin
)

include(GNUInstallDirs)
install(TARGETS qt-huggingface-example
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
