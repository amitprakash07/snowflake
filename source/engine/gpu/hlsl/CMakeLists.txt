cmake_minimum_required(VERSION 3.25.0)

project(EngineGpuCompileHlsl)

find_package(DxcCompiler REQUIRED)

set(ENGINE_DATA_SHADERS_HLSL_DIR ${PROJECT_DATA_DIR}/engine/shaders/hlsl)
set(DxcCompiler dxc.exe)

message("CMAKE_CURRENT_BINARY_DIR is ${CMAKE_CURRENT_BINARY_DIR}")
add_executable(EngineGpuCompileHlsl hlsl_compile.cc)
target_link_libraries(EngineGpuCompileHlsl EnginePlatform)
# add_custom_target(EngineGpuCompileHlsl
#     COMMAND ${CMAKE_COMMAND} -E echo "Compiling HLSL shaders to ${ENGINE_DATA_SHADERS_HLSL_DIR}"
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_OUTPUT_DIR}/shaders/hlsl
#     COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${DxcCompiler_Bin}/ ${PROJECT_OUTPUT_DIR}/bin/
#     COMMAND ${DxcCompiler} --version
#     COMMAND "./${DxcCompiler} -E test_dxc_compilation_cs -T cs_6_0 -Fo ${PROJECT_OUTPUT_DIR}/shaders/hlsl/compile_test.dxil ${ENGINE_DATA_SHADERS_HLSL_DIR}/compile_test.hlsl")

set_target_properties(EngineGpuCompileHlsl
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")