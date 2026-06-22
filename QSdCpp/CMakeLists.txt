project(qt-stable-diffusion-cpp
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

qt_add_executable(appqt_stable_diffusion_cpp
    main.cpp
)

set(QSD_HEADERS
  objectmodel.h pointer-macros.h property-macros.h  qmlstringlist.h
  qsdutils.h qsdbaseparam.cpp qsdenums.h qsdpath.h qsdpathing.h
  qsdtilingparams.h
  qsdembedding.h
  qsdaudio.h
  qsdimage.h
  qsdslgparams.h
  qsdguidanceparams.h
  qsdsampleparams.h
  qsdpmparams.h
  qsdcacheparams.h
  qsdlora.h
  qsdhiresparams.h
  qsdimggenparams.h
  qsdvidgenparams.h
  qsdctx.h
  qsdbackenddevice.h
  qsdupscaleparams.h
  hf/apiclient.h
)
# qsddownloaderparams.h
# qsddownloader.h

set(QSD_CXX
  qmlstringlist.cpp
  qsdutils.cpp qsdbaseparam.h qsdenums.cpp qsdpath.cpp qsdpathing.cpp
  qsdtilingparams.cpp
  qsdembedding.cpp
  qsdctxparams.h
  qsdctxparams.cpp
  qsdaudio.cpp
  qsdimage.cpp
  qsdslgparams.cpp
  qsdguidanceparams.cpp
  qsdsampleparams.cpp
  qsdpmparams.cpp
  qsdcacheparams.cpp
  qsdlora.cpp
  qsdhiresparams.cpp
  qsdimggenparams.cpp
  qsdvidgenparams.cpp
  qsdctx.cpp
  qsdbackenddevice.cpp
  qsdupscaleparams.cpp
  hf/apiclient.cpp
)
# qsddownloaderparams.h
# qsddownloader.cpp

set(QSD_QML
  main.qml
  QmlSdCtxParams.qml
  QmlSdSampleParams.qml
  QmlSdGuidanceParams.qml
  QmlSdSlgParams.qml
  QmlSdImgGenParams.qml
  QmlSdLora.qml
  QmlSdPmParams.qml
  QmlSdTilingParams.qml
  QmlSdCacheParams.qml
  QmlSdHiResParams.qml
  QmlSdEmbedding.qml
  TestZImage.qml
  QmlSdBackendManager.qml
)



qt_add_qml_module(appqt_stable_diffusion_cpp
    URI QSd
    VERSION 1.0
    SOURCES
      ${QSD_HEADERS}
      ${QSD_CXX}
    QML_FILES
      ${QSD_QML}
)

target_include_directories(appqt_stable_diffusion_cpp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>

    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hf>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hf>
)

target_link_libraries(appqt_stable_diffusion_cpp PRIVATE
    yaml-cpp
    ggml
    stable-diffusion
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Concurrent
    Qt6::Quick
    Qt6::Qml
)

include(GNUInstallDirs)
install(TARGETS appqt_stable_diffusion_cpp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
