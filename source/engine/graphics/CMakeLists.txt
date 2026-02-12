cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineGraphics)
project(${ENGINE_PROJECT_NAME})
message("Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

#camera.h
#camera.cc
#frame_time.h
#frame_time.cc    
#mesh_object.h
#mesh_object.cc
#object_interface.h
#scene.h
#scene.cc

set(ENGINE_GRAPHICS_SOURCES
pixel.h
color.h
ppm_image.h
ppm_image.cc)

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_GRAPHICS_SOURCES})

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")

message("End Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")


