cmake_minimum_required(VERSION 3.25.0)

include_source_list_from_file(win32/win32_platform.cmake)

include_src(platform.h)
# include_src(platform_file_system.h)
# include_src(platform_file_system.cc)

group_sources(/Platform)