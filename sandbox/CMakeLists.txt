cmake_minimum_required(VERSION 3.21.7)

find_package(CUDAToolkit)

if(${CUDAToolkit_FOUND})
    enable_language(CUDA)
    set(PROJECT_PREFIX ${PROJECT_PREFIX}_SandBox_)
    add_subdirectory(CUDA)
else()
    message(STATUS "CUDA not found, skipping CUDA examples")
endif()
