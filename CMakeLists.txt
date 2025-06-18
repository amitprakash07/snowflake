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


message("Processing ${PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR})")
project(${PROJECT_NAME} LANGUAGES C CXX)

include(FetchContent)
set(JSON_MultipleHeaders OFF)
set(JsonParser_Version "v3.12.0" CACHE STRING "Json Parser version" FORCE)
set(JsonParser_Path "${PROJECT_EXTERNAL_SOURCE_DIR}/json_parser/${JsonParser_Version}/" CACHE PATH "Json Parser path" FORCE)
FetchContent_Declare(
    JsonParser
    URL https://github.com/nlohmann/json/releases/download/${JsonParser_Version}/json.tar.xz
    SOURCE_DIR ${JsonParser_Path})
FetchContent_MakeAvailable(JsonParser)

set(OpenCV_Root ${PROJECT_EXTERNAL_SOURCE_DIR}/opencv/4.11.0)
set(OpenCV_Build_Dir ${OpenCV_Root}/build)
set(OpenCV_Include_Dir ${OpenCV_Build_Dir}/include)
set(OpenCV_Bin_Dir ${OpenCV_Build_Dir}/x64/vc16/bin)
set(OpenCV_Lib_Dir ${OpenCV_Build_Dir}/x64/vc16/lib)

add_library(OpenCV_Imported_Lib SHARED IMPORTED GLOBAL)
set_target_properties(OpenCV_Imported_Lib PROPERTIES IMPORTED_LOCATION ${OpenCV_Lib_Dir}/opencv_world4110.lib)

add_library(OpenCV_Imported_Lib_Debug SHARED IMPORTED GLOBAL)
set_target_properties(OpenCV_Imported_Lib_Debug PROPERTIES IMPORTED_LOCATION ${OpenCV_Lib_Dir}/opencv_world4110d.lib)

include(${PROJECT_CMAKE_MODULE_DIR}/build_config.cmake)

# Required for CMake version < 3.29
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ENGINE_DIR ${PROJECT_SRC_DIR}/engine)

add_subdirectory(${PROJECT_SRC_DIR}/engine)
add_subdirectory(${PROJECT_SRC_DIR}/projects/image_viewer)
add_subdirectory(${PROJECT_SRC_DIR}/tools/hex2bin)
add_subdirectory(${PROJECT_SRC_DIR}/sandbox)
message("End Processing ${PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR})")
