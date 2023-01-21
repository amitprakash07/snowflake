cmake_minimum_required(VERSION 3.21.7)

set(ENGINE_LIB_NAME "Engine")

project(${ENGINE_LIB_NAME})
set(VS_FILTER_NAME ${VS_FILTER_NAME}/Engine)

include(${CMAKE_CURRENT_SOURCE_DIR}/algorithms/algorithms.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/common/common.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphics.cmake)

set(CURRENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/engine_defs.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/engine_core.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/engine_core.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})
add_library(${ENGINE_LIB_NAME} ${ENGINE_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME} FILES ${CURRENT_SOURCES})
endif()