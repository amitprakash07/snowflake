cmake_minimum_required(VERSION 3.25.0)

message(STATUS "In Experiments")
append_target_folder(Experiments)
add_subdirectory(WriteToNetworkPort)
add_subdirectory(PythonModules)
add_subdirectory(PythonModulesWithSwig)
revert_target_folder()
