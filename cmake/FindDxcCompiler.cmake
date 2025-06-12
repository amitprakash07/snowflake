# FindDxcCompiler.cmake

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.24)

set(DxcCompiler_Found FALSE CACHE BOOL "DXC Compiler exists" FORCE)
set(DxcCompiler_Version "dxc_2025_02_20" CACHE STRING "DXC Compiler  version" FORCE)
set(DxcCompiler_Path "${PROJECT_EXTERNAL_SOURCE_DIR}/dxc_compiler/${DxcCompiler_Version}/" CACHE PATH "DXC Compiler path" FORCE)
set(DxcCompiler_Include "" CACHE PATH "DXC Compiler include path" FORCE)
set(DxcCompiler_Lib "" CACHE PATH "DXC Compiler library path" FORCE)
set(DxcCompiler_Bin "" CACHE PATH "DXC Compiler binaries path" FORCE)

include(FetchContent)

FetchContent_Declare(
    DxcCompiler
    URL https://github.com/microsoft/DirectXShaderCompiler/releases/download/v1.8.2502/dxc_2025_02_20.zip
    SOURCE_DIR ${DxcCompiler_Path}
)

function(download_dxc_compiler)
    find_path(DXC_COMPILER_INCLUDE_DIR NAMES d3d12.h PATHS ${DxcCompiler_Path}/inc/ NO_CACHE)

    if(DXC_COMPILER_INCLUDE_DIR)
        return()
    endif()

    FetchContent_MakeAvailable(DxcCompiler)
    message(STATUS "DXC Compiler already downloaded in ${DxcCompiler_Path}")
endfunction()

# Define a function to find the DXC Compiler
function(find_dxc_compiler)
    # Search for the DXC Compiler
    message("Searching in ${DxcCompiler_Path}")

    download_dxc_compiler()
    find_path(DXC_COMPILER_INCLUDE_DIR NAMES dxcapi.h PATHS ${DxcCompiler_Path}/inc/ NO_CACHE)

    # Check if the DXC Compiler is found
    if(DXC_COMPILER_INCLUDE_DIR)
        message(STATUS "DXC Compiler found: ${DXC_COMPILER_INCLUDE_DIR}")
        set(${DxcCompiler_Found} TRUE CACHE BOOL "DXC Compiler exists" FORCE)
        set(DxcCompiler_Include ${DxcCompiler_Path}/inc/ CACHE PATH "DXC Compiler include path" FORCE)
        set(DxcCompiler_Lib ${DxcCompiler_Path}/lib/x64/ CACHE PATH "DXC Compiler library path" FORCE)
        set(DxcCompiler_Bin ${DxcCompiler_Path}/bin/x64/ CACHE PATH "DXC Compiler binary path" FORCE)
    else()
        message(FATAL_ERROR "DXC Compiler not found")
    endif()
endfunction()

# Call the function to find the DXC Compiler
find_dxc_compiler()