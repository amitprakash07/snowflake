cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/windows_program.h
    ${CMAKE_CURRENT_LIST_DIR}/windows_program.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/OS/Win32/Windowing FILES ${CURRENT_SOURCES})
endif()