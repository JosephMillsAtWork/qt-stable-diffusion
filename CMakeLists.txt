cmake_minimum_required(VERSION 3.16)
project("qt6-stable-diffusion")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_QML_EXAMPLES "Build the examples for qt-stable-diffusion and qt6-huggingface" ON)

include(GNUInstallDirs)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

include(cmake/cmake_nvidia.cmake)
include(cmake/cmake_ggml_build_flags.cmake)
include(cmake/cmake_sd_cpp_build_flags.cmake)
include(cmake/cmake_llama_cpp_build_flags.cmake)

add_subdirectory(stable-diffusion.cpp)
add_subdirectory(llama.cpp) # needs cargo

add_subdirectory(qsdutils)

add_subdirectory(qggml)
add_subdirectory(qsodium)
add_subdirectory(qtdeclarative-sodium)

add_subdirectory(qhf)
add_subdirectory(qsd)

if(BUILD_QML_EXAMPLES)
    add_subdirectory(examples)
endif()
