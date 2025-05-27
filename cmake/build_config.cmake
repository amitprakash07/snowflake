cmake_minimum_required(VERSION 3.25.0)

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

set(PROJECT_OUTPUT_DIR ${PROJECT_OUTPUT_DIR}/${PROJECT_PLATFORM})
set(PROJECT_INTERMEDIATE_DIR ${PROJECT_INTERMEDIATE_DIR}/${PROJECT_PLATFORM}/${CMAKE_BUILD_TYPE})
message("Project Output directory is ${PROJECT_OUTPUT_DIR}.")
if(WIN32)
    message("Generating for windows")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_OUTPUT_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_OUTPUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_OUTPUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_OUTPUT_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_OUTPUT_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_OUTPUT_DIR}/lib)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/lib)
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

if(WIN32)
    set(COMMON_LINKER_FLAGS             /MACHINE:X64)
else()
    set(COMMON_COMPILATION_FLAGS        -m64)
    set(COMMON_LINKER_FLAGS             -m64)
endif()

## Define common release config compilation flags
set(COMMON_RELEASE_COMPILATION_FLAGS "")

## Define common debug config compilation flags
set(COMMON_DEBUG_COMPILATION_FLAGS "")

## Define common release config linker flags
set(COMMON_RELEASE_LINKER_FLAGS "")

## Define common debug config linker flags
set(COMMON_DEBUG_LINKER_FLAGS "")

if(WIN32)
    ## Windows Release Compilation flags:
    ## /Z7 :Debug Information
    ## /GF :string pooling
    ## /MP :Multi-processor compilation
    ## /O2 :Optimization
    ## /MD :Multi-threaded DLL
    ## /GL :Whole program optimization

    ## Linker options-
    ## /LTCG : Use link time code generation
    ## /OPT:REF :References
    ## /DEBUG : generate debug information
    ## /OPT:ICF enable COMDATA folding
    ## /INCREMENTAL:NO : Incremental Link
    set(COMMON_RELEASE_COMPILATION_FLAGS    /Z7 /GF /MP4 /O2 /MD)
    set(COMMON_RELEASE_LINKER_FLAGS         "/LTCG /OPT:REF /DEBUG /OPT:ICF /INCREMENTAL:NO /MANIFEST:NO")

    ## Debug Compiler Flags:
    ## /RTC1 : Runtime check
    ## /Z7   : Debug format
    ## /Gm-  : turn off minimal rebuild
    ## /Od   : Optimization disabled
    ## /MDd  : CRT Multi-threaded debug

    ## Debug Linker flags:
    ## /INCREMENTAL:NO - disable incremental linking
    ## /DEBUG          - generate debug info
    ## /MANIFEST:NO    - no manifest
    set(COMMON_DEBUG_COMPILATION_FLAGS        /RTC1 /Z7 /Gm- /Od /MDd)
    set(COMMON_DEBUG_LINKER_FLAGS             "/MANIFEST:NO /DEBUG /INCREMENTAL:NO")
else()
    set(COMMON_DEBUG_COMPILATION_FLAGS        -g -O0 -D_DEBUG)
    set(COMMON_DEBUG_LINKER_FLAGS             "")
endif()

set(COMMON_LINK_ARCHIVE_FLAG //WHOLEARCHIVE)
set(COMMON_LINK_NO_ARCHIVE_FLAG -Wl,--no-whole-archive)