cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineGpuShader)
project(${ENGINE_PROJECT_NAME})
message("Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

find_package(DxcCompiler REQUIRED)

set(ENGINE_SHADER_DIR ${PROJECT_DATA_DIR}/engine/shaders)
set(DxcCompiler dxc.exe)

set(ENGINE_SHADERS_HLSL ${ENGINE_SHADER_DIR}/hlsl/compile_test.hlsl
                        ${ENGINE_SHADER_DIR}/hlsl/compile_test_copy.hlsl)
source_group(Shaders/hlsl FILES ${ENGINE_SHADERS_HLSL})

include_directories(${DxcCompiler_Include})
set(ENGINE_SHADERS ${ENGINE_SHADERS_HLSL})

add_library(${ENGINE_PROJECT_NAME}  STATIC  ${CMAKE_CURRENT_LIST_DIR}/shader_handler.h
                                            ${CMAKE_CURRENT_LIST_DIR}/shader_handler.cc
                                            ${ENGINE_SHADER_DIR}/asset_shaders.json
                                            ${ENGINE_SHADERS})

                                    
target_compile_definitions(${ENGINE_PROJECT_NAME} PRIVATE ENGINE_SHADER_DIR=${ENGINE_SHADER_DIR})

source_group(Shaders FILES ${ENGINE_SHADER_DIR}/asset_shaders.json)

set_source_files_properties(${ENGINE_SHADERS} PROPERTIES VS_SETTINGS "ExcludedFromBuild=true")

message(DxcCompiler_Lib is ${DxcCompiler_Lib})
target_link_libraries(${ENGINE_PROJECT_NAME} EngineShared
                                             EnginePlatform
                                             nlohmann_json::nlohmann_json
                                             ${DxcCompiler_Lib}/dxcompiler.lib
                                             ole32.lib)

add_custom_command(TARGET ${ENGINE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying dxc to the output directory"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_OUTPUT_DIR}/shaders/hlsl
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${DxcCompiler_Bin}/ ${PROJECT_OUTPUT_DIR}/bin/
    COMMAND ${CMAKE_COMMAND} -E echo "Version of the dxc compiler is"
    COMMAND ${DxcCompiler} --version)

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")
message("End Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")
