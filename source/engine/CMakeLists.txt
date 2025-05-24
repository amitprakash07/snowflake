cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME Engine)
project(${ENGINE_PROJECT_NAME})

find_package(AgilitySDK REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${AgilitySdk_Include})

add_subdirectory(common)
add_subdirectory(platform)
add_subdirectory(maths)
add_subdirectory(gpu)
add_subdirectory(tests)
add_subdirectory(tools/build_shaders)

# include_source_list_from_file(graphics/graphics.cmake)
# include_source_list_from_file(physics/physics.cmake)
# include_source_list_from_file(networking/networking.cmake)
# include_source_list_from_file(input/input.cmake)

set(ENGINE_SOURCES  engine_defs.h
                    engine_core.h 
                    engine_includes.h
                    engine_core.cc)

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_SOURCES})

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")