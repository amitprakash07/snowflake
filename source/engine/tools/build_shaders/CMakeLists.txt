cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineToolsBuildShaders)
project(${ENGINE_PROJECT_NAME})
message("Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

set(ENGINE_TOOLS_BUILD_SHADER_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/main.cc)

add_executable(${ENGINE_PROJECT_NAME} ${ENGINE_TOOLS_BUILD_SHADER_SOURCES})
target_link_libraries(${ENGINE_PROJECT_NAME} EngineGpuShader)
target_link_options(${ENGINE_PROJECT_NAME} PUBLIC "/WHOLEARCHIVE")

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine/Tools"
    VS_SOLUTION_FOLDER "Engine/Tools")
message("End Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")