cmake_minimum_required(VERSION 3.21.7)

message("PROJECT_INTERMEDIATE_DIR dir is ${PROJECT_INTERMEDIATE_DIR}")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/hex2bin ${PROJECT_INTERMEDIATE_DIR}/hex2bin)
