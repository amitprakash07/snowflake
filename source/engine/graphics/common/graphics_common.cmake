cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/camera.cc
    ${CMAKE_CURRENT_LIST_DIR}/frame_time.h
    ${CMAKE_CURRENT_LIST_DIR}/frame_time.cc    
    ${CMAKE_CURRENT_LIST_DIR}/mesh_object.h
    ${CMAKE_CURRENT_LIST_DIR}/mesh_object.cc
    ${CMAKE_CURRENT_LIST_DIR}/object_interface.h
    ${CMAKE_CURRENT_LIST_DIR}/scene.h
    ${CMAKE_CURRENT_LIST_DIR}/scene.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Common FILES ${CURRENT_SOURCES})
endif()