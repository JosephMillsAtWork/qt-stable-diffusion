cmake_minimum_required(VERSION 3.16)
project("qt-stable-diffusion")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(yaml-cpp REQUIRED)

include(cmake/cmake_nvidia.cmake)
include(cmake/cmake_ggml_build_flags.cmake)
include(cmake/cmake_sd_cpp_build_flags.cmake)

add_subdirectory(stable-diffusion.cpp)
add_subdirectory(QSdCpp)
