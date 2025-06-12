cmake_minimum_required(VERSION 3.25.0)

set(TOOLS_PROJECT_NAME Hex2Bin)
project(${TOOLS_PROJECT_NAME})
message("Processing ${TOOLS_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

add_executable(${TOOLS_PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/hex_to_bin.cc)

set_target_properties(${TOOLS_PROJECT_NAME}
    PROPERTIES
    FOLDER "Tools"
    VS_SOLUTION_FOLDER "Tools")
message("End Processing ${TOOLS_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")


