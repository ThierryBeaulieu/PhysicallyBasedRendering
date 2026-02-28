cmake_minimum_required(VERSION 3.20)
project(PBRSandbox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output binaries to build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ── Optional: enable compile_commands.json for clangd/IDEs ──
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── Collect sources ──
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(pbr_sandbox ${SOURCES})

target_include_directories(pbr_sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# ── Compiler warnings ──
target_compile_options(pbr_sandbox PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:
        -Wall -Wextra -Wpedantic -O2
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /O2
    >
)

# ── Create output directory ──
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/output)