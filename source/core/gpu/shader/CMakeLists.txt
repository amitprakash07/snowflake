cmake_minimum_required(VERSION 3.25.0)

set(CORE_PROJECT_NAME EngineGpuShader)
project(${CORE_PROJECT_NAME})
message("Processing ${CORE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

find_package(DxcCompiler REQUIRED)

set(CORE_SHADER_DIR ${PROJECT_DATA_DIR}/engine/shaders)
set(DxcCompiler dxc.exe)

set(CORE_SHADERS_HLSL ${CORE_SHADER_DIR}/hlsl/compile_test.hlsl
                        ${CORE_SHADER_DIR}/hlsl/compile_test_copy.hlsl)
source_group(Shaders/hlsl FILES ${CORE_SHADERS_HLSL})

include_directories(${DxcCompiler_Include})
set(CORE_SHADERS ${CORE_SHADERS_HLSL})

add_library(${CORE_PROJECT_NAME}  STATIC  ${CMAKE_CURRENT_LIST_DIR}/shader_handler.h
                                            ${CMAKE_CURRENT_LIST_DIR}/shader_handler.cc
                                            ${CORE_SHADER_DIR}/asset_shaders.json
                                            ${CORE_SHADERS})

                                    
target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE CORE_SHADER_DIR=${CORE_SHADER_DIR})

source_group(Shaders FILES ${CORE_SHADER_DIR}/asset_shaders.json)

set_source_files_properties(${CORE_SHADERS} PROPERTIES VS_SETTINGS "ExcludedFromBuild=true")

message(DxcCompiler_Lib is ${DxcCompiler_Lib})
target_link_libraries(${CORE_PROJECT_NAME} EngineShared
                                             EnginePlatform
                                             nlohmann_json::nlohmann_json
                                             ${DxcCompiler_Lib}/dxcompiler.lib
                                             ole32.lib)

add_custom_command(TARGET ${CORE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying dxc to the output directory"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_OUTPUT_DIR}/shaders/hlsl
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${DxcCompiler_Bin}/ ${PROJECT_OUTPUT_DIR}/bin/
    COMMAND ${CMAKE_COMMAND} -E echo "Version of the dxc compiler is"
    COMMAND ${DxcCompiler} --version)

set_target_properties(${CORE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")
message("End Processing ${CORE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")
