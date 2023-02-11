cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/physics_system.h
    ${CMAKE_CURRENT_LIST_DIR}/physics_system.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Physics FILES ${CURRENT_SOURCES})
endif()