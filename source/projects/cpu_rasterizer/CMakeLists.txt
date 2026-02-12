cmake_minimum_required(VERSION 3.25.0)

set(PROJECT_NAME CpuRasterizer)
project(${PROJECT_NAME})

set(CPU_RASTERIZER_SOURCES cpu_rasterizer_main.cc)

include_directories(${PROJECT_SRC_DIR})
add_executable(${PROJECT_NAME} ${CPU_RASTERIZER_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE EngineMaths EngineGraphics)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Projects"
                                                 VS_SOLUTION_FOLDER "Projects")