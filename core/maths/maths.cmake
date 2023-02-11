cmake_minimum_required(VERSION 3.21.7)

set(CURRENT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/affine_transform.h
    ${CMAKE_CURRENT_LIST_DIR}/affine_transform.cc
    ${CMAKE_CURRENT_LIST_DIR}/axis_aligned_bounding_box.h
    ${CMAKE_CURRENT_LIST_DIR}/bounding_box.h
    ${CMAKE_CURRENT_LIST_DIR}/bounding_box.cc
    ${CMAKE_CURRENT_LIST_DIR}/math_util_funcs.h
    ${CMAKE_CURRENT_LIST_DIR}/math_util_funcs.cc
    ${CMAKE_CURRENT_LIST_DIR}/math.h
    ${CMAKE_CURRENT_LIST_DIR}/math.cc
    ${CMAKE_CURRENT_LIST_DIR}/matrix_4x4.h
    ${CMAKE_CURRENT_LIST_DIR}/matrix_4x4.cc
    ${CMAKE_CURRENT_LIST_DIR}/quaternion.h
    ${CMAKE_CURRENT_LIST_DIR}/quaternion.cc
    ${CMAKE_CURRENT_LIST_DIR}/ray_intersection.h
    ${CMAKE_CURRENT_LIST_DIR}/ray_intersection.cc
    ${CMAKE_CURRENT_LIST_DIR}/triangle.h
    ${CMAKE_CURRENT_LIST_DIR}/triangle.cc
    ${CMAKE_CURRENT_LIST_DIR}/vector2.h
    ${CMAKE_CURRENT_LIST_DIR}/vector2.cc
    ${CMAKE_CURRENT_LIST_DIR}/vector3.h
    ${CMAKE_CURRENT_LIST_DIR}/vector3.cc
    ${CMAKE_CURRENT_LIST_DIR}/vector4.h
    ${CMAKE_CURRENT_LIST_DIR}/vector4.cc)

set(ENGINE_SOURCES ${ENGINE_SOURCES} ${CURRENT_SOURCES})

if(WIN32)
    source_group(${VS_FILTER_NAME}/Maths FILES ${CURRENT_SOURCES})
endif()