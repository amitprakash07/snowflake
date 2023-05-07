cmake_minimum_required(VERSION 3.21.7)

set(VS_OLD_FILTER ${VS_FILTER_NAME})
set(VS_FILTER_NAME ${VS_FILTER_NAME}/Graphics)

include(${CMAKE_CURRENT_LIST_DIR}/common/graphics_common.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/debug_overlays/graphics_debug_overlays.cmake)

set(VS_FILTER_NAME ${VS_OLD_FILTER})