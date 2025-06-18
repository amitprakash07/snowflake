cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineImage)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_IMAGE_SOURCE image.h
                        image.cc
                        load_jpeg.cc
                        load_png.cc
                        load_ppm.cc)

message(${OpenCV_Include_Dir})
file(GLOB_RECURSE External_OpenCV_Sources LIST_DIRECTORIES false ${OpenCV_Include_Dir}/*.h ${OpenCV_Include_Dir}/*.hpp)
source_group(External/OpenCV2 FILES ${External_OpenCV_Sources})

# foreach(file_name ${External_OpenCV_Sources})
#     message(${file_name})
# endforeach()

get_target_property(OpenCV_Imported_Lib_Location OpenCV_Imported_Lib IMPORTED_LOCATION)
get_target_property(OpenCV_Imported_Lib_Debug_Location OpenCV_Imported_Lib_Debug IMPORTED_LOCATION)

include_directories(${OpenCV_Include_Dir})
add_library(${ENGINE_PROJECT_NAME}  ${ENGINE_IMAGE_SOURCE}
                                    ${External_OpenCV_Sources})
target_link_libraries(${ENGINE_PROJECT_NAME}    EnginePlatform
                                                $<$<CONFIG:DEBUG>:${OpenCV_Imported_Lib_Debug_Location}>
                                                $<$<CONFIG:RELEASE>:${OpenCV_Imported_Lib_Location}>)
set_source_files_properties(${External_OpenCV_Sources} PROPERTIES VS_SETTINGS "ExcludedFromBuild=true")

add_custom_command(TARGET ${ENGINE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying OpenCV binaries to the output directory"
    COMMAND ${CMAKE_COMMAND} -E copy ${OpenCV_Bin_Dir}/opencv_world4110.dll ${PROJECT_OUTPUT_DIR}/bin/
    COMMAND ${CMAKE_COMMAND} -E copy ${OpenCV_Bin_Dir}/opencv_world4110d.dll ${PROJECT_OUTPUT_DIR}/bin/)

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")