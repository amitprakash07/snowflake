cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineGpu)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_GPU_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/gpu_factory.h
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_factory.cc
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device.h
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device.cc
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device_resource.h
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device_resource.cc)

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_GPU_SOURCES})
target_link_libraries(${ENGINE_PROJECT_NAME} d3d12.dll dxgi.dll)
set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")

add_subdirectory(shader)