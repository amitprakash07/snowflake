cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/input_controller.h
    ${CMAKE_CURRENT_LIST_DIR}/input_controller.cc
    ${CMAKE_CURRENT_LIST_DIR}/mouse_controller.h
    ${CMAKE_CURRENT_LIST_DIR}/mouse_controller.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Input FILES ${CURRENT_SOURCES})
endif()