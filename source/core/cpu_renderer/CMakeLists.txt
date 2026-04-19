cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME cpu_renderer)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_CPU_RENDERER_SOURCES
rasterizer.h
rasterizer.cc)

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_CPU_RENDERER_SOURCES})
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE graphics)

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")




