cmake_minimum_required(VERSION 3.25.0)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../engine)
append_target_folder(Sandbox)

find_package(CUDAToolkit)
if(${CUDAToolkit_FOUND})
    enable_language(CUDA)
    set(PROJECT_PREFIX ${PROJECT_PREFIX})
    add_subdirectory(CUDA)
else()
    message(STATUS "CUDA not found, skipping CUDA examples")
endif()

add_subdirectory(coding_problems)
add_subdirectory(experiments)

revert_target_folder()
