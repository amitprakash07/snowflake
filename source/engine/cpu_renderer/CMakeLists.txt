cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineRenderCpu)
project(${ENGINE_PROJECT_NAME})
message("Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

set(ENGINE_CPU_RENDERER_SOURCES
raster_primitives.h
raster_primitives.cc
rasterizer.h
rasterizer.cc)

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_CPU_RENDERER_SOURCES})
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE EngineGraphics)

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")

message("End Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")


