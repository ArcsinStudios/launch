cmake_minimum_required(VERSION 3.12)

project(LAUNCH VERSION 1.15.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(launch STATIC)

target_sources(launch PRIVATE
  src/arithing_impl.cpp
  src/chroyes_impl.cpp
  src/clap_impl.cpp
  src/escseq_impl.cpp
  src/exfmtio_impl.cpp
  src/fmtio_impl.cpp
  src/genev_impl.cpp
  src/goodmath_impl.cpp
  src/goodstr_impl.cpp
  src/hedgehog_impl.cpp
)

target_include_directories(launch PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)