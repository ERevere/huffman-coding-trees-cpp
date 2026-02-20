cmake_minimum_required(VERSION 3.20)

project(huffman_coding_trees_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(huffman_core
  src/bit_io.cpp
  src/decoder.cpp
  src/encoder.cpp
  src/format.cpp
  src/huffman_tree.cpp
)

target_include_directories(huffman_core
  PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(huffman_core PRIVATE -Wall -Wextra)

add_executable(huffman_cli src/main.cpp)
target_link_libraries(huffman_cli PRIVATE huffman_core)
target_compile_options(huffman_cli PRIVATE -Wall -Wextra)
