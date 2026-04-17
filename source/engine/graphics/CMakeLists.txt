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
ppm_image.cc
rasterizer.h
rasterizer.cc
viewport.h
raster_primitives.h
raster_primitives.cc
color.cc
text_overlay.h
text_overlay.cc)

file(GLOB FONT8X8_HEADERS CONFIGURE_DEPENDS
  "${PROJECT_EXTERNAL_SOURCE_DIR}/font8x8/*.h")

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_GRAPHICS_SOURCES})

target_sources(${ENGINE_PROJECT_NAME} PRIVATE ${FONT8X8_HEADERS})
set_source_files_properties(${FONT8X8_HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE)
source_group("external/font8x8" FILES ${FONT8X8_HEADERS})

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")

target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE ${PROJECT_EXTERNAL_SOURCE_DIR}/font8x8/)

message("End Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")


