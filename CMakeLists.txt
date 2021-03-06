cmake_minimum_required(VERSION 3.15)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the kyte source code and call cmake from there")
endif()

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

project(kyte VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(KYTE_COMPILER "Generate kytec target"                           ON )
option(KYTE_DOCS     "Generate documentation target (Requires Sphynx)" OFF)
option(KYTE_GEN_STL  "Generate STL files (Requires Python)"            OFF)
option(KYTE_GRAMMAR  "Build grammar (Requires Bison and re2c)"         OFF)
option(KYTE_INSTALL  "Generate install targets"                        OFF)
option(KYTE_TESTS    "Generate test target"                            OFF)

add_subdirectory(dependencies)

add_subdirectory(kyte)

if(KYTE_COMPILER)
  add_subdirectory(kytec)
endif()

if(KYTE_DOCS)
  add_subdirectory(docs)
endif()

add_subdirectory(kytestl)

if(KYTE_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
