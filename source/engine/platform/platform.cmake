cmake_minimum_required(VERSION 3.25.0)

if(WIN32)
    include_source_list_from_file(win32/win32_platform.cmake)
endif()

include_src(platform.h)

group_sources(/Platform)