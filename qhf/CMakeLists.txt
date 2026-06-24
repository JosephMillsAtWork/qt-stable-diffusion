# Goals. Query hugging face to build a cache of "package mainifest" each "package mainifest"  has all sorts of data this data needs to be put into
# a cache and then compressed up to save on space. it all really comes from the call GET const QString &ns, const QString &repo  ->  models/%1/%2
# because we get back the QFuture<QJsonObject> on all api calls.... I can just store the json.
# I will have to create the approrate qproperty <--> huggingface api json objects. That is where the objects HuggingFacePackageManifest which has the MVC of the HuggingFaceFileManifest
# HuggingFaceCache job is to manage the cache reading and writing to the compression using the zstd -> HuggingFacePackageManifest
# HuggingFaceCache::search will look at local cache not using the api. HuggingFaceCache::policy will call the api looking for the versions changes.
# HuggingFaceHub::update calls out to the api and fills up the cache. HuggingFaceHub::upgrade  upgrades the models that are already installed (gathered from the cache and policy)
# HuggingFaceHub::install HuggingFaceHub::remove , installs or removes "packages"
# exxposure to Qml should be limited more on that after the middleware is finished.

# THE MAJOR Design (Blockers) point atm.
# should the objects that are stored be from msgpack-cxx ?
# should the objects that are stored be from QJSON or NlohmannJson ?

project(qt-huggingface
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)

find_package(zstd
    REQUIRED
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LibSodium  REQUIRED libsodium)

find_package(Qt6 6.2 COMPONENTS
    Core
    Gui
    Network
    Quick
    Qml
    Concurrent
  REQUIRED
)

set(QHF_HEADERS
    apiclient.h                         # abstract base client | 100% done
    huggingfaceapi.h                    # hugging face api callback functions all functions here return a QFuture<QJsonObject> |  90% done
    huggingfacefilemanifest.h           # file mainifest from huggings faces api calls | schema started
    huggingfacepackagemanifest.h        # package mainifest for huggingface api | schema started
    huggingfacecache.h                  # local cache storage for huggingface api | 0% done
    huggingfaceuser.h                   # the user storage area.
    huggingfaceusermanager.h            # the manager of all the users
    huggingfacedownloader.h             # download manager (threaded can run multi-downloads at a time) | 25% done
    huggingfacehub.h                    # entry point | 0% done
    huggingfacerepoinfo.h
)

set(QHF_CXX
    apiclient.cpp
    huggingfaceapi.cpp
    huggingfacepackagemanifest.cpp
    huggingfacefilemanifest.cpp
    huggingfacecache.cpp
    huggingfaceuser.cpp
    huggingfaceusermanager.cpp
    huggingfacedownloader.cpp
    huggingfacehub.cpp
    huggingfacerepoinfo.cpp
)

set(QHF_QML
    ## later
)

qt_add_library(qt-huggingface STATIC)
qt_add_qml_module(qt-huggingface
    URI QHF
    VERSION 1.0
    SOURCES
      ${QHF_HEADERS}
      ${QHF_CXX}
    # QML_FILES
    #   ${QHF_QML}
)


target_include_directories(qt-huggingface PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
)

target_link_libraries(qt-huggingface PRIVATE
    ${LibSodium_LIBRARIES}
    zstd::libzstd
    qt-stable-diffusion-utils
    qt-sodium
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Concurrent
    Qt6::Quick
    Qt6::Qml
)
