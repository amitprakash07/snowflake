cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/additional_types.h
    ${CMAKE_CURRENT_LIST_DIR}/hashed_string.h
    ${CMAKE_CURRENT_LIST_DIR}/hashed_string.cc
    ${CMAKE_CURRENT_LIST_DIR}/message_handler_interface.h
    ${CMAKE_CURRENT_LIST_DIR}/messaging_system.h
    ${CMAKE_CURRENT_LIST_DIR}/messaging_system.cc
    ${CMAKE_CURRENT_LIST_DIR}/object_controller_interface.h
    ${CMAKE_CURRENT_LIST_DIR}/rtti.h
    ${CMAKE_CURRENT_LIST_DIR}/rtti.cc
    ${CMAKE_CURRENT_LIST_DIR}/shared_pointer.h
    ${CMAKE_CURRENT_LIST_DIR}/shared_pointer.cc
    ${CMAKE_CURRENT_LIST_DIR}/shared_pointer.inl
    ${CMAKE_CURRENT_LIST_DIR}/string_pool.h
    ${CMAKE_CURRENT_LIST_DIR}/string_pool.cc
    ${CMAKE_CURRENT_LIST_DIR}/string_util.h
    ${CMAKE_CURRENT_LIST_DIR}/string_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/time_helper.h
    ${CMAKE_CURRENT_LIST_DIR}/time_helper.inl
    ${CMAKE_CURRENT_LIST_DIR}/unique_ptr.h
    ${CMAKE_CURRENT_LIST_DIR}/unique_ptr.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Common FILES ${CURRENT_SOURCES})
endif()