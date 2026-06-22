# nvidia
set(QSDCPP_CUDA_TOOLKIT_ROOT_DIR    "/usr/local/cuda-13.1"              CACHE STRING "Where the cuda toolkit is ")
set(QSDCPP_CUDA_COMPILER            "/usr/local/cuda-13.1/bin/nvcc"     CACHE STRING "full path to the nvcc compiler")
set(QSDCPP_CUDA_HOST_COMPILER       "/usr/bin/g++-15"                   CACHE STRING "the compiler that nvcc is compiled with")
set(QSDCPP_CUDA_ARCHITECTURES       "120"                               CACHE STRING "version of the cuda api")

set(CMAKE_CUDA_TOOLKIT_ROOT_DIR "${QSDCPP_CUDA_TOOLKIT_ROOT_DIR}")
set(CMAKE_CUDA_COMPILER         "${QSDCPP_CUDA_COMPILER}")
set(CMAKE_CUDA_HOST_COMPILER    "${QSDCPP_CUDA_HOST_COMPILER}")
set(CMAKE_CUDA_ARCHITECTURES    "${QSDCPP_CUDA_ARCHITECTURES}")
set(CMAKE_CUDA_PROPAGATE_HOST_FLAGS OFF)
enable_language(CUDA)

find_package(CUDAToolkit REQUIRED)
set(JOB_CUDA_LIBS
    CUDA::cudart
    CUDA::cublas
    CUDA::cusparse
    CUDA::curand
)
