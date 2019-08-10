cmake_minimum_required(VERSION 3.8)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the kyte source code and call cmake from there")
endif()

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

project(kyte VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(KYTE_CLI  "Build CLI."       ON)
option(KYTE_UTIL "Build Utilities." OFF)

add_subdirectory(libkyte)

if(KYTE_CLI)
  add_subdirectory(kyte)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
