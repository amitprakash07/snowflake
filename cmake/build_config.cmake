cmake_minimum_required(VERSION 3.21.7)

# Default configs
set(CMAKE_SIZEOF_VOID_P 8)
set(CMAKE_BUILD_TYPE Debug)

set(PROJECT_PLATFORM "x64")
set(PROJECT_TARGET_SUFFIX "")

if(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
    set(PROJECT_PLATFORM "x86")
    set(CMAKE_SIZEOF_VOID_P 4)
    set(PROJECT_TARGET_SUFFIX "_x86")
endif()

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "")
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_DEBUG_POSTFIX "_d")

message("Generating project files for ${PROJECT_PLATFORM} platform.")

set(PROJECT_OUT_DIR ${PROJECT_OUT_DIR}/${PROJECT_PLATFORM})
set(PROJECT_INTERMEDIATE_DIR ${PROJECT_INTERMEDIATE_DIR}/${PROJECT_PLATFORM}/${CMAKE_BUILD_TYPE})
message("Project Output directory is ${PROJECT_OUT_DIR}.")
if(WIN32)
    message("Generating for windows")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_OUT_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_OUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_OUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_OUT_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_OUT_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_OUT_DIR}/lib)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUT_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUT_DIR}/lib)
endif()

# Common compiler flags
if(UNIX)
    if(${USE_GCC})
        set(USE_CXX_COMPILER gcc)
    endif()
    set(USE_CXX_STANDARD_FLAG -std=c++${DEFAULT_CXX_STANDARD})
elseif(WIN32)
    if(${USE_MSVC})
        set(USE_CXX_COMPILER msvc)
    endif()
    set(USE_CXX_STANDARD_FLAG /std:c++${DEFAULT_CXX_STANDARD})
endif()

add_compile_options(${USE_CXX_STANDARD_FLAG})