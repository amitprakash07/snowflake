cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME EngineMaths)
project(${ENGINE_PROJECT_NAME})

set(ENGINE_MATH_SOURCE 
affine_transform.h
affine_transform.cc
axis_aligned_bounding_box.h
bounding_box.h
bounding_box.cc
utils.h
utils.cc
engine_math.h
engine_math.cc
matrix_4x4.h
matrix_4x4.cc
quaternion.h
quaternion.cc
ray_intersection.h
ray_intersection.cc
vector3.h
vector3.cc
vector4.h
vector4.cc
plane.h
plane.cc
sphere.h
sphere.cc
triangle.h
triangle.cc)

add_library(${ENGINE_PROJECT_NAME} ${ENGINE_MATH_SOURCE})
set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Engine"
    VS_SOLUTION_FOLDER "Engine")