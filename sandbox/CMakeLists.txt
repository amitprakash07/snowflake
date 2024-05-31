cmake_minimum_required(VERSION 3.21.7)

append_target_folder(Sandbox)
add_subdirectory(leetcode ${PROJECT_INTERMEDIATE_DIR}/leetcode)

find_package(CUDAToolkit)

if(${CUDAToolkit_FOUND})
    enable_language(CUDA)
    set(PROJECT_PREFIX ${PROJECT_PREFIX})
    add_subdirectory(CUDA ${PROJECT_INTERMEDIATE_DIR}/CUDA)
else()
    message(STATUS "CUDA not found, skipping CUDA examples")
endif()
