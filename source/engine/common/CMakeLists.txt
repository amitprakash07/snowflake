cmake_minimum_required(VERSION 3.25.0)

set(PROJECT_TARGET_NAME EngineShared)
project(${PROJECT_TARGET_NAME} LANGUAGES CXX)

set(ENGINE_SHARED_CORE_SRC  ${CMAKE_CURRENT_LIST_DIR}/additional_types.h
                            ${CMAKE_CURRENT_LIST_DIR}/message_handler_interface.h
                            ${CMAKE_CURRENT_LIST_DIR}/messaging_system.h
                            ${CMAKE_CURRENT_LIST_DIR}/messaging_system.cc
                            ${CMAKE_CURRENT_LIST_DIR}/core_objects.h
                            ${CMAKE_CURRENT_LIST_DIR}/rtti.h
                            ${CMAKE_CURRENT_LIST_DIR}/rtti.cc
                            ${CMAKE_CURRENT_LIST_DIR}/defs.h)
source_group(Core FILES ${ENGINE_SHARED_CORE_SRC})

set(ENGINE_SHARED_ALLOCATION    ${CMAKE_CURRENT_LIST_DIR}/shared_pointer.h
                                ${CMAKE_CURRENT_LIST_DIR}/shared_pointer.cc
                                ${CMAKE_CURRENT_LIST_DIR}/unique_ptr.h
                                ${CMAKE_CURRENT_LIST_DIR}/unique_ptr.cc)
source_group(Allocation FILES ${ENGINE_SHARED_ALLOCATION})

set(ENGINE_SHARED_DATA_CONTAINERS_SRC   ${CMAKE_CURRENT_LIST_DIR}/linked_list.h
                                        ${CMAKE_CURRENT_LIST_DIR}/linked_list.inl
                                        ${CMAKE_CURRENT_LIST_DIR}/tree.h
                                        ${CMAKE_CURRENT_LIST_DIR}/tree.inl
                                        ${CMAKE_CURRENT_LIST_DIR}/heap_container.h
                                        ${CMAKE_CURRENT_LIST_DIR}/heap_container.inl
                                        ${CMAKE_CURRENT_LIST_DIR}/stack.h
                                        ${CMAKE_CURRENT_LIST_DIR}/stack.inl
                                        ${CMAKE_CURRENT_LIST_DIR}/queue.h
                                        ${CMAKE_CURRENT_LIST_DIR}/queue.inl
                                        ${CMAKE_CURRENT_LIST_DIR}/dequeue.h
                                        ${CMAKE_CURRENT_LIST_DIR}/dequeue.inl
                                        ${CMAKE_CURRENT_LIST_DIR}/doubly_linked_list.h
                                        ${CMAKE_CURRENT_LIST_DIR}/doubly_linked_list.inl
                                        ${CMAKE_CURRENT_LIST_DIR}/octree.h
                                        ${CMAKE_CURRENT_LIST_DIR}/octree.cc)
source_group(DataContainers FILES ${ENGINE_SHARED_DATA_CONTAINERS_SRC})

set(ENGINE_SHARED_UTILITY_HELPERS ${CMAKE_CURRENT_LIST_DIR}/util.h
                                    ${CMAKE_CURRENT_LIST_DIR}/util.cc                                    
                                    ${CMAKE_CURRENT_LIST_DIR}/time_helper.h
                                    ${CMAKE_CURRENT_LIST_DIR}/time_helper.inl
                                    ${CMAKE_CURRENT_LIST_DIR}/sort.h
                                    ${CMAKE_CURRENT_LIST_DIR}/sort.cc)
source_group(UtilityHelpers FILES ${ENGINE_SHARED_UTILITY_HELPERS})

set(ENGINE_SHARED_STRINGS   ${CMAKE_CURRENT_LIST_DIR}/string_util.h
                            ${CMAKE_CURRENT_LIST_DIR}/string_util.cc
                            ${CMAKE_CURRENT_LIST_DIR}/string_pool.h
                            ${CMAKE_CURRENT_LIST_DIR}/string_pool.cc
                            ${CMAKE_CURRENT_LIST_DIR}/to_str.h
                            ${CMAKE_CURRENT_LIST_DIR}/to_str.inl
                            ${CMAKE_CURRENT_LIST_DIR}/hashed_string.h
                            ${CMAKE_CURRENT_LIST_DIR}/hashed_string.cc)
source_group(Strings FILES ${ENGINE_SHARED_STRINGS})


set(ENGINE_SHARED_MATHS_UTIL  ${CMAKE_CURRENT_LIST_DIR}/maths_util.h)
source_group(MathsUtil FILES ${ENGINE_SHARED_MATHS_UTIL})

add_library(${PROJECT_TARGET_NAME})
target_sources(${PROJECT_TARGET_NAME} PRIVATE ${ENGINE_SHARED_CORE_SRC}
                                             ${ENGINE_SHARED_ALLOCATION}
                                             ${ENGINE_SHARED_DATA_CONTAINERS_SRC}
                                             ${ENGINE_SHARED_UTILITY_HELPERS}
                                             ${ENGINE_SHARED_STRINGS}
                                             ${ENGINE_SHARED_MATHS_UTIL})
set_target_properties(${PROJECT_TARGET_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    OUTPUT_NAME "EngineShared"
    FOLDER "Engine")

