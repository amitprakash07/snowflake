cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/octree.h
    ${CMAKE_CURRENT_LIST_DIR}/octree.cc
    ${CMAKE_CURRENT_LIST_DIR}/sort.h
    ${CMAKE_CURRENT_LIST_DIR}/sort.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Algorithms FILES ${CURRENT_SOURCES})
endif()