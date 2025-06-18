cmake_minimum_required(VERSION 3.25.0)

set(PROJECT_NAME ImageViewer)
project(${PROJECT_NAME})

set(IMAGE_VIEWER_SOURCE image_viewer_win_main.cc)

include_directories(${ENGINE_DIR})
add_executable(${PROJECT_NAME} WIN32 ${IMAGE_VIEWER_SOURCE})
target_link_libraries(${PROJECT_NAME}   EngineImage)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Projects"
                                                 VS_SOLUTION_FOLDER "Projects")