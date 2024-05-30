cmake_minimum_required(VERSION 3.21.7)

set(LEET_CODE ${PROJECT_PREFIX}LeetCode)

set(LEET_CODE_SOURCES   ${CMAKE_CURRENT_SOURCE_DIR}/coding_problems.h
                        ${CMAKE_CURRENT_SOURCE_DIR}/coding_problem_list.h
                        ${CMAKE_CURRENT_SOURCE_DIR}/unique_email_address.h
                        ${CMAKE_CURRENT_SOURCE_DIR}/leet_code_main.cc)
add_executable(${LEET_CODE}${PROJECT_TARGET_SUFFIX} ${LEET_CODE_SOURCES})
set_target_properties(${LEET_CODE}${PROJECT_TARGET_SUFFIX} PROPERTIES FOLDER "SandBox")