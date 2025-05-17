cmake_minimum_required(VERSION 3.25.0)


set(PROJECT_NAME "Snowflake")
message("Generating project files in ${CMAKE_BINARY_DIR}")

#inlcude all the CMake global variables
include(${CMAKE_SOURCE_DIR}/cmake/build_global_defs.cmake)

message(DEBUG "Project CMake module dir is ${PROJECT_CMAKE_MODULE_DIR}")
include(${PROJECT_CMAKE_MODULE_DIR}/build_options.cmake)
include(${PROJECT_CMAKE_MODULE_DIR}/macros.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_CMAKE_MODULE_DIR})

set(USE_CXX_COMPILER ${DEFAULT_CXX_COMPILER})
set(USE_C_COMPILER ${DEFAULT_C_COMPILER})

if(UNIX)
    if(${USE_GCC})
        set(USE_CXX_COMPILER gcc)
    endif()
elseif(WIN32)
    if(${USE_MSVC})
        set(USE_CXX_COMPILER msvc)
    endif()
endif()

include(${PROJECT_CMAKE_MODULE_DIR}/build_config.cmake)
project(${PROJECT_NAME} LANGUAGES C CXX)

# Required for CMake version < 3.29
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(${PROJECT_SRC_DIR}/engine)
add_subdirectory(${PROJECT_SRC_DIR}/tools)
add_subdirectory(${PROJECT_SRC_DIR}/sandbox)
