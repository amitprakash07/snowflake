cmake_minimum_required(VERSION 3.21.7)

declare_project(Engine)

find_package(AgilitySDK REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${AgilitySdk_Include})

include_source_list_from_file(algorithms/algorithms.cmake)
include_source_list_from_file(common/common.cmake)
include_source_list_from_file(graphics/graphics.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphics.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/physics/physics.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/networking/networking.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/maths/maths.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/input/input.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/os/win32/windowing/win32.windowing.cmake)

include_src(engine_defs.h)
include_src(engine_core.h)
include_src(engine_includes.h)
include_src(engine_core.cc)

make_library_target()
group_sources("")
group_target(Core)