cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EnginePlatform)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_PLATFORM_COMMON_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/platform.h
                                    ${CMAKE_CURRENT_LIST_DIR}/platform_systems.h
                                    ${CMAKE_CURRENT_LIST_DIR}/platform_objects.h)
source_group(Platform FILES ${ENGINE_PLATFORM_SOURCES})

if(WIN32)
    set(ENGINE_PLATFORM_SOURCES ${CMAKE_CURRENT_LIST_DIR}/win32/win32_resource.h
                                ${CMAKE_CURRENT_LIST_DIR}/win32/win32_includes.h
                                ${CMAKE_CURRENT_LIST_DIR}/win32/win32_platform.cc
                                ${CMAKE_CURRENT_LIST_DIR}/win32/win32_platform_objects.cc
                                ${CMAKE_CURRENT_LIST_DIR}/win32/win32_windowing.cc)

    source_group(Platform/Win32 FILES ${ENGINE_PLATFORM_SOURCES})
endif()

add_library(${ENGINE_PROJECT_NAME}  ${ENGINE_PLATFORM_COMMON_SOURCES}
                                    ${ENGINE_PLATFORM_SOURCES})

target_link_libraries(${ENGINE_PROJECT_NAME} EngineShared)

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")
