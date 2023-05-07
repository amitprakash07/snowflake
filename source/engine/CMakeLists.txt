cmake_minimum_required(VERSION 3.21.7)

set(ENGINE_LIB_NAME ${PROJECT_PREFIX}Engine)

project(${}${ENGINE_LIB_NAME})
set(VS_FILTER_NAME ${VS_FILTER_NAME}/Engine)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/algorithms/algorithms.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/common/common.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphics.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/physics/physics.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/networking/networking.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/maths/maths.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/input/input.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/os/win32/windowing/win32.windowing.cmake)


set(CURRENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/engine_defs.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/engine_core.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/engine_includes.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/engine_core.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})
add_library(${ENGINE_LIB_NAME}${PROJECT_TARGET_SUFFIX} ${ENGINE_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME} FILES ${CURRENT_SOURCES})
endif()