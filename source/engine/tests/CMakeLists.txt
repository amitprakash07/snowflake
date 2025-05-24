cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineTests)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_TESTS_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/test_win_main.cc)

add_executable(${ENGINE_PROJECT_NAME} WIN32 ${ENGINE_TESTS_SOURCES})
target_link_libraries(${ENGINE_PROJECT_NAME}    EngineShared
                                                EngineMaths
                                                EnginePlatform
                                                EngineGpu
                                                EngineGpuShader)

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")