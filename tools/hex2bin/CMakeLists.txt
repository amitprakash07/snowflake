cmake_minimum_required(VERSION 3.21.7)

set(TOOL_NAME "Hex2Bin")

set(TOOL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/hex_to_bin.cc)
message("CMAKE_CURRENT_BINARY_DIR is ${CMAKE_CURRENT_BINARY_DIR}")
add_executable(${TOOL_NAME} ${TOOL_SOURCES})