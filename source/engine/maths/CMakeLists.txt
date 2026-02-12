cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineMaths)
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
source_group("LinearAlgebra" FILES ${ENGINE_MATHS_LINEAR_ALGEBRA_SOURCE})

set(ENGINE_MATHS_GEOMETRY_SOURCE
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
ray_intersection.cc)
source_group("Geometry" FILES ${ENGINE_MATHS_GEOMETRY_SOURCE})

set(ENGINE_MATH_SOURCE 
${ENGINE_MATHS_LINEAR_ALGEBRA_SOURCE}
${ENGINE_MATHS_GEOMETRY_SOURCE}
${ENGINE_MATHS_GRAPHICS_SOURCE})

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_MATH_SOURCE})
set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")