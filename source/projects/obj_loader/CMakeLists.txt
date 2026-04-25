cmake_minimum_required(VERSION 3.25.0)

set(PROJECT_NAME obj_loader)
project(${PROJECT_NAME})

set(OBJ_LOADER_SOURCES obj_loader_main.cc)

include_directories(${PROJECT_SRC_DIR})
add_executable(${PROJECT_NAME} ${OBJ_LOADER_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE core)

add_dependencies(${PROJECT_NAME} core)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Projects"
                                                 VS_SOLUTION_FOLDER "Projects")
