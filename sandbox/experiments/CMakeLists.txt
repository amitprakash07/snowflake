cmake_minimum_required(VERSION 3.21.7)

append_target_folder(Sandbox)
add_subdirectory(experiments/WriteToNetworkPort)

set_target_properties(${LEET_CODE}${PROJECT_TARGET_SUFFIX} PROPERTIES FOLDER ${PROJECT_TARGET_FOLDER})