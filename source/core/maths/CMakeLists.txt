cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME maths)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_MATHS_LINEAR_ALGEBRA_SOURCE
vector3.h
vector3.cc
vector4.h
vector4.cc
utils.h
utils.cc
matrix_4x4.h
matrix_4x4.cc
quaternion.h
quaternion.cc)

add_library(maths_linear_algebra STATIC ${ENGINE_MATHS_LINEAR_ALGEBRA_SOURCE})
set_target_properties(maths_linear_algebra
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")

set(ENGINE_MATHS_GEOMETRY_SOURCE
geometry_primitives.h
primitive.h
axis_aligned_bounding_box.h
bounding_box.h
bounding_box.cc
plane.h
plane.cc
sphere.h
sphere.cc
triangle.h
triangle.cc
affine_transform.h
affine_transform.cc
ray_intersection.h
ray_intersection.cc
point.h
point.cc
line_segment.h
geometry.h)

add_library(maths_geometry STATIC ${ENGINE_MATHS_GEOMETRY_SOURCE})
target_link_libraries(maths_geometry maths_linear_algebra)
set_target_properties(maths_geometry
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")

add_library(${ENGINE_PROJECT_NAME} INTERFACE)
target_link_libraries(${ENGINE_PROJECT_NAME} INTERFACE maths_linear_algebra maths_geometry)