cmake_minimum_required(VERSION 3.21.7)

find_package(CUDAToolkit REQUIRED)
enable_language(CUDA)

set(PROJECT_PREFIX ${PROJECT_PREFIX}_SandBox_)


add_subdirectory(CUDA)
