cmake_minimum_required(VERSION 3.9)

include(cmake/BuildType.cmake)

project(DASH-TUTORIAL CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

find_package(MPI)
find_package(DASH-MPI
  CONFIG
  HINTS $ENV{HOME}/share /usr/local/share /opt/share /opt/local/share
  )
include(external/dash.cmake)

option(DRBF_BUILD_BENCHMARKS "Build the benchmarks ?" ON)
if(${DRBF_BUILD_BENCHMARKS})
  find_package(benchmark
    CONFIG
    HINTS $ENV{HOME} /usr/local /opt /opt/local
  )
  include(external/benchmark.cmake)
  add_subdirectory(perf)
endif()

