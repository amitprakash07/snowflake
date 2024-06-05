cmake_minimum_required(VERSION 3.25.0)

message(DEBUG "Processing ${CMAKE_CURRENT_LIST_FILE}")
message(DEBUG "Project binary dir: ${PROJECT_BINARY_DIR}")
# Project Level vars
set(PROJECT_CMAKE_MODULE_DIR ${CMAKE_SOURCE_DIR}/cmake)

set(PROJECT_EXTERNAL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external)
set(PROJECT_SRC_DIR ${CMAKE_SOURCE_DIR}/source)
set(PROJECT_TEMP_DIR ${PROJECT_BINARY_DIR}/tmp)
set(PROJECT_INTERMEDIATE_DIR ${PROJECT_TEMP_DIR})
set(PROJECT_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/${PROJECT_TEMP_DIR}/output)

# Project target vars
set(PROJECT_TARGET_PREFIX "")
set(PROJECT_TARGET_NAME "")
set(PROJECT_TARGET_SUFFIX "")
set(PROJECT_TARGET_VS_SOLUTION_FOLDER "")

# source level vars
set(PROJECT_TARGET_SOURCES "")
set(PROJECT_TARGET_VS_SOURCE_GROUP_FILTER "")

# Default compiler
set(DEFAULT_C_COMPILER "C:\\Program\ Files\\LLVM\\bin\\clang.exe")
set(DEFAULT_CXX_COMPILER "C:\\Program\ Files\\LLVM\\bin\\clang++.exe")
set(DEFAULT_CXX_STANDARD 20)