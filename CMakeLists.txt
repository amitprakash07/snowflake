cmake_minimum_required(VERSION 3.21.7)

set(PROJECT_GIT_REPO_NAME "Snowflake")
set(PROJECT_NAME ${PROJECT_GIT_REPO_NAME})

message("Generating project files in ${PROJECT_BINARY_DIR}")

include(${CMAKE_SOURCE_DIR}/cmake/build_global_defs.cmake)
include(${PROJECT_CMAKE_MODULE_DIR}/build_options.cmake)

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

project(${PROJECT_NAME} LANGUAGES C CXX)
include(${PROJECT_CMAKE_MODULE_DIR}/build_config.cmake)

# Required for CMake version < 3.29
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(${PROJECT_SRC_DIR}/engine ${PROJECT_INTERMEDIATE_DIR}/engine)
add_subdirectory(${PROJECT_SRC_DIR}/tools ${PROJECT_INTERMEDIATE_DIR}/tools)
add_subdirectory(${PROJECT_SRC_DIR}/../sandbox ${PROJECT_INTERMEDIATE_DIR}/sandbox)