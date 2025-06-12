cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineImage)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_IMAGE_SOURCE image.h
                        image.cc)

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_IMAGE_SOURCE})
set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")