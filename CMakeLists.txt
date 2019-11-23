cmake_minimum_required(VERSION 3.8.2)

project(QtPidTuneHelper
  VERSION 1.0.0.0
  DESCRIPTION "Qt PID tunning helper"
  LANGUAGES C CXX)

option(GOS_QT_PID_TUNE_HELPER_BUILD_TESTS "Build tests" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(CLANG_TIDY_FIX_ERRORS
  "Perform fixes with Clang-Tidy even if compilation errors were found" OFF)
option(CLANG_TIDY_FIX "Perform fixes with Clang-Tidy" OFF)
option(CLANG_TIDY "Perform Clang-Tidy check" OFF)

set(TIDY_ARGUMENTS "-checks=*,-clang-analyzer-alpha.* "
  CACHE STRING "Arguments for Clang-Tidy check")
set(TIDY_FIX_ARGUMENTS "-list-checks=*,-clang-analyzer-alpha.* "
  CACHE STRING "Arguments for Clang-Tidy fix")
set(TIDY_FIX_ERRORS_ARGUMENTS "-checks=*,-clang-analyzer-alpha.* "
  CACHE STRING "Arguments for Clang-Tidy fix errors")

configure_file(
  "include/gos/qtpth/version.h.in"
  "include/gos/qtpth/version.h"
  @ONLY)
#list(APPEND qt_pid_tune_helper_public_headers
#  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/qtpidtunehelper/gos.h")

list(APPEND q_custom_plot_include
  ${q_custom_plot_amalgamate_include})
  
list(APPEND qt_pid_tune_helper_include
  ${q_custom_plot_include}
  "${CMAKE_CURRENT_BINARY_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

list(APPEND qt_pid_tune_helper_libraries
  libqcustomplot)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

set(qt_pid_tune_helper_target qpidtunehelper)

string(TIMESTAMP GOS_CURRENT_YEAR "%Y" UTC)
set(GOS_NAME "Geirmundur Orri Sigurdsson")
set(GOS_LEGALCOPYRIGHT "Copyright (C) ${GOS_CURRENT_YEAR} $GOS_COMPANYNAME}")

add_subdirectory(extern/qcustomplot)

if(CLANG_TIDY)
  find_program(CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
    if(CLANG_TIDY_FIX_ERRORS)
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}" "${TIDY_FIX_ERRORS_ARGUMENTS}-fix-errors")
      message(STATUS "Using clang-tidy with fix")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_FIX_ERRORS_ARGUMENTS}-fix-errors")
    elseif(CLANG_TIDY_FIX)
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "${TIDY_FIX_ARGUMENTS}-fix")
      message(STATUS "Using clang-tidy with fix")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_FIX_ARGUMENTS}-fix")
    else()
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}" "${TIDY_ARGUMENTS}")
      message(STATUS "Using clang-tidy")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_ARGUMENTS}")
    endif()
  endif()
endif()

add_subdirectory(src)

if (GOS_QT_PID_TUNE_HELPER_BUILD_TESTS)
  enable_testing()
  if (MSVC)
    #if (NOV_FORCE_SHARED_CRT)
      set(gtest_force_shared_crt ON CACHE BOOL "Use Shared CRT")
    #endif ()
  endif (MSVC)
  set(qt_pid_tune_helper_test_include
    ${qt_pid_tune_helper_include})
  set(qt_pid_tune_helper_test_libraries
    gtest
    gmock
    gmock_main)
  mark_as_advanced(
    gmock_build_tests
    gtest_build_samples
    gtest_build_tests)
  add_subdirectory(extern/googletest)
  add_subdirectory(tests)
endif ()

message(STATUS "")
message(STATUS "Qt PID tunning helper ${PROJECT_VERSION} BUILD SUMMARY")
message(STATUS "  Install prefix            : ${CMAKE_INSTALL_PREFIX}")

message(STATUS "  CMAKE_GENERATOR           : ${CMAKE_GENERATOR}")
message(STATUS "  CMAKE_SOURCE_DIR          : ${CMAKE_SOURCE_DIR}")
message(STATUS "  CMAKE_CURRENT_SOURCE_DIR  : ${CMAKE_CURRENT_SOURCE_DIR}")

message(STATUS "  BUILD_SHARED_LIBS         : ${BUILD_SHARED_LIBS}")

if (GOS_QT_PID_TUNE_HELPER_BUILD_TESTS)
message(STATUS "Building Tests")
message(STATUS "  GTest Force Shared CRT    : ${gtest_force_shared_crt}")
endif ()

message(STATUS "  C++ Compiler ID           : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  C++ Compiler Version      : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  C++ Compiler flags        : ${CMAKE_CXX_FLAGS}")
if (MSVC_VERSION)
message(STATUS "  MSVC Version              : ${MSVC_VERSION}")
endif (MSVC_VERSION)
if (gos_build_dependency_boost)
message(STATUS "  Boost version             : ${Boost_VERSION}")
message(STATUS "  Boost include dir         : ${Boost_INCLUDE_DIRS}")
message(STATUS "  Boost debug library dir   : ${Boost_LIBRARY_DIR_DEBUG}")
message(STATUS "  Boost release library dir : ${Boost_LIBRARY_DIR_RELEASE}")
endif ()
