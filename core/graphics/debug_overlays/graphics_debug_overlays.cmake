cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/debug_menu.h
    ${CMAKE_CURRENT_LIST_DIR}/debug_menu.cc
    ${CMAKE_CURRENT_LIST_DIR}/debug_shapes.h
    ${CMAKE_CURRENT_LIST_DIR}/debug_shapes.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Debug\ Overlays FILES ${CURRENT_SOURCES})
endif()