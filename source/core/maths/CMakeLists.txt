cmake_minimum_required(VERSION 3.25.0)

set(CORE_PROJECT_NAME maths)
project(${CORE_PROJECT_NAME})

set(CORE_MATHS_LINEAR_ALGEBRA_SOURCE
    linear_algebra/vector3.h
    linear_algebra/vector3.cc
    linear_algebra/vector4.h
    linear_algebra/vector4.cc
    linear_algebra/utils.h
    linear_algebra/utils.cc
    linear_algebra/matrix_4x4.h
    linear_algebra/matrix_4x4.cc
    linear_algebra/quaternion.h
    linear_algebra/quaternion.cc)
    
add_library(maths_linear_algebra STATIC ${CORE_MATHS_LINEAR_ALGEBRA_SOURCE})
target_include_directories(maths_linear_algebra
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/linear_algebra
    PRIVATE
    # matrix_4x4.cc needs plane.h (not pulled via link to avoid a circular static-lib dependency)
    ${CMAKE_CURRENT_LIST_DIR}/geometry)
set_target_properties(maths_linear_algebra
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")

set(CORE_MATHS_GEOMETRY_SOURCE
    geometry/geometry_primitives.h
    geometry/primitive.h
    geometry/axis_aligned_bounding_box.h
    geometry/bounding_box.h
    geometry/bounding_box.cc
    geometry/plane.h
    geometry/plane.cc
    geometry/sphere.h
    geometry/sphere.cc
    geometry/triangle.h
    geometry/triangle.cc
    geometry/affine_transform.h
    geometry/affine_transform.cc
    geometry/ray_intersection.h
    geometry/ray_intersection.cc
    geometry/point.h
    geometry/point.cc
    geometry/line_segment.h
    geometry/geometry.h
    geometry/geometry_common.h)

add_library(maths_geometry STATIC ${CORE_MATHS_GEOMETRY_SOURCE})
target_link_libraries(maths_geometry PUBLIC maths_linear_algebra)
target_include_directories(maths_geometry
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/geometry)
set_target_properties(maths_geometry
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")

add_library(${CORE_PROJECT_NAME} INTERFACE)
target_link_libraries(${CORE_PROJECT_NAME} INTERFACE maths_linear_algebra maths_geometry)
