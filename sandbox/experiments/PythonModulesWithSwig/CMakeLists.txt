cmake_minimum_required(VERSION 3.25.0)

declare_target(PythonModuleUseSwig)

set(SWIG_ROOT ${PROJECT_EXTERNAL_SOURCE_DIR}/swigwin-4.2.1)
find_package(SWIG 4.2.1 REQUIRED COMPONENTS python)

if(${SWIG_FOUND})
    message(STATUS "Swig found. Using swig version ${SWIG_VERSION} and executable ${SWIG_EXECUTABLE}")
else()
    message(FATAL "Swig not found")
endif()

include(UseSWIG)

find_package(AgilitySDK REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${AgilitySdk_Include})
include_directories(${PROJECT_EXTERNAL_SOURCE_DIR}/Python/include)
include_directories()
link_directories(${PROJECT_EXTERNAL_SOURCE_DIR}/Python/x64)

set_property(SOURCE python_module.i PROPERTY CPLUSPLUS ON)
swig_add_library(${PROJECT_TARGET_NAME} LANGUAGE python SOURCES python_module.i)
set_target_properties(PythonModuleTest PROPERTIES OUTPUT_NAME python_module_with_swig)
set_target_properties(PythonModuleTest PROPERTIES SUFFIX .pyd)
link_target(python311)
group_sources("")
group_target("")