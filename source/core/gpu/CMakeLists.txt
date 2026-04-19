cmake_minimum_required(VERSION 3.25.0)

set(CORE_PROJECT_NAME gpu)
project(${CORE_PROJECT_NAME})

set(CORE_GPU_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/gpu_factory.h
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_factory.cc
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device.h
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device.cc
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device_resource.h
                        ${CMAKE_CURRENT_LIST_DIR}/gpu_device_resource.cc)

add_library(${CORE_PROJECT_NAME} ${CORE_GPU_SOURCES})

target_link_libraries(${CORE_PROJECT_NAME} d3d12.dll dxgi.dll)
set_target_properties(${CORE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")