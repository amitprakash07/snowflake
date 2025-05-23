cmake_minimum_required(VERSION 3.25.0)

declare_target(Engine)

find_package(AgilitySDK REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${AgilitySdk_Include})

add_subdirectory(common)
add_subdirectory(platform)
add_subdirectory(maths)
add_subdirectory(gpu)
add_subdirectory(tests)
include_source_list_from_file(graphics/graphics.cmake)
include_source_list_from_file(physics/physics.cmake)
include_source_list_from_file(networking/networking.cmake)
include_source_list_from_file(input/input.cmake)
# include_source_list_from_file(platform/os_platform.cmake)

include_src(engine_defs.h)
include_src(engine_core.h)
include_src(engine_includes.h)
include_src(engine_core.cc)

make_library_target()
group_sources("")
group_target(Engine)