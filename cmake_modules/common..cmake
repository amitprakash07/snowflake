cmake_minimum_required(VERSION 3.21.7)

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "")
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
else()
    set(CMAKE_BUILD_TYPE Release)
endif()