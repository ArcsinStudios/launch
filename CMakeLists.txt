cmake_minimum_required(VERSION 3.12)

project(LAUNCH VERSION 1.16.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(launch STATIC)

target_sources(launch PRIVATE
  include/arithing.cppm
  include/arithing_impl.cppm
  include/arithing_limits.cppm
  include/chroyes.cppm
  include/chroyes_impl.cppm
  include/clap.cppm
  include/clap_impl.cppm
  include/escseq.cppm
  include/escseq_impl.cppm
  include/exfmtio.cppm
  include/exfmtio_impl.cppm
  include/fmtio.cppm
  include/fmtio_concepts.cppm
  include/fmtio_impl.cppm
  include/genev.cppm
  include/genev_impl.cppm
  include/goodmath.cppm
  include/goodmath_impl.cppm
  include/goodrand.cppm
  include/goodrand_concepts.cppm
  include/goodrand_impl.cppm
  include/goodstr.cppm
  include/goodstr_impl.cppm
  include/hedgehog.cppm
  include/hedgehog_concepts.cppm
  include/hedgehog_impl.cppm
  include/launch.cppm
  include/leisure.cppm
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