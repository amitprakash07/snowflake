cmake_minimum_required(VERSION 3.21.7)

set(TOOL_NAME ${PROJECT_PREFIX}ScratchPad)

set(TOOL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/scratch_pad.cc)
add_executable(${TOOL_NAME}${PROJECT_TARGET_SUFFIX} ${TOOL_SOURCES})
set_target_properties(${TOOL_NAME}${PROJECT_TARGET_SUFFIX} PROPERTIES FOLDER "Tools")