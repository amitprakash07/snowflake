cmake_minimum_required(VERSION 3.25.0)

set(CORE_PROJECT_NAME cpu_renderer)
project(${CORE_PROJECT_NAME})

set(CORE_CPU_RENDERER_SOURCES
rasterizer.h
rasterizer.cc)

add_library(${CORE_PROJECT_NAME} ${CORE_CPU_RENDERER_SOURCES})
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE graphics)

set_target_properties(${CORE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")




