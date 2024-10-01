cmake_minimum_required(VERSION 3.25.0)

append_target_folder(Experiments)
add_subdirectory(WriteToNetworkPort)
add_subdirectory(PythonModules)
add_subdirectory(PythonModulesWithSwig)
add_subdirectory(scratch_pad)
revert_target_folder()
