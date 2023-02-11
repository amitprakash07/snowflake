cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/client.h
    ${CMAKE_CURRENT_LIST_DIR}/client.cc
    ${CMAKE_CURRENT_LIST_DIR}/network_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/network_manager.cc
    ${CMAKE_CURRENT_LIST_DIR}/network_player.h
    ${CMAKE_CURRENT_LIST_DIR}/network_player.cc
    ${CMAKE_CURRENT_LIST_DIR}/server.h
    ${CMAKE_CURRENT_LIST_DIR}/server.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Networking FILES ${CURRENT_SOURCES})
endif()