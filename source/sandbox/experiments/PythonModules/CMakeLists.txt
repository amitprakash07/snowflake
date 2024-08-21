cmake_minimum_required(VERSION 3.25.0)

declare_target(PythonModuleTest)

include_directories(${PROJECT_EXTERNAL_SOURCE_DIR}/Python/include)
link_directories(${PROJECT_EXTERNAL_SOURCE_DIR}/Python/x64)
include_src(python_module_test.cc)
make_shared_library_target()
link_target(python311)
set_target_properties(PythonModuleTest PROPERTIES OUTPUT_NAME spam)
set_target_properties(PythonModuleTest PROPERTIES SUFFIX .pyd)
group_sources("")
group_target("")