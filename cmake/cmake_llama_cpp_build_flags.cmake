##
## Build time flags for building llama.cpp
set(LLAMA_USE_SYSTEM_GGML OFF)
set(LLAMA_WASM_MEM64 OFF)
set(BUILD_SHARED_LIBS OFF)
set(LLAMA_SANITIZE_THREAD    OFF)
set(LLAMA_SANITIZE_ADDRESS   OFF)
set(LLAMA_SANITIZE_UNDEFINED OFF)

# utils
set(LLAMA_BUILD_COMMON ON)

# extra artifacts
set(LLAMA_BUILD_TESTS     OFF)
set(LLAMA_BUILD_TOOLS     OFF)
set(LLAMA_BUILD_EXAMPLES  OFF)
set(LLAMA_BUILD_SERVER    ON)
set(LLAMA_BUILD_APP       OFF)
set(LLAMA_BUILD_UI        OFF)
set(LLAMA_USE_PREBUILT_UI OFF)

set(LLAMA_TOOLS_INSTALL OFF)
set(LLAMA_TESTS_INSTALL OFF)

# 3rd party
set(LLAMA_OPENSSL ON)
set(LLAMA_LLGUIDANCE  ON)
if (LLAMA_LLGUIDANCE)
    find_program(CARGO_EXECUTABLE cargo REQUIRED)
    if (TARGET llama-common AND TARGET llguidance_ext)
        add_dependencies(llama-common llguidance_ext)
    endif()

    include_directories(SYSTEM BEFORE
        "${CMAKE_BINARY_DIR}/llguidance/source/libs/llguidance/include"
        "${CMAKE_BINARY_DIR}/llguidance/source/parser"
    )
endif()
