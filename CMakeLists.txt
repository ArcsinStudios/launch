cmake_minimum_required(VERSION 3.16)

project(LAUNCH VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(launch STATIC)

target_sources(launch PRIVATE
  arithing_impl.cpp
  chroyes_impl.cpp
  clap_impl.cpp
  escseq_impl.cpp
  exfmtio_impl.cpp
  fmtio_impl.cpp
  goodmath_impl.cpp
  goodstr_impl.cpp
  hedgehog_impl.cpp
)

target_include_directories(launch PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)