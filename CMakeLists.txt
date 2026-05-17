cmake_minimum_required(VERSION 3.20)
project(kvdb CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler hardening flags
add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    -O2
    -fno-omit-frame-pointer
)

# ─── Library target (core engine) ────────────────────────────────────────────
add_library(kvdb_core STATIC
    include/common/types.h
    include/common/status.h
    src/common/config.cpp
)
target_include_directories(kvdb_core PUBLIC include/)