cmake_minimum_required(VERSION 3.25.0)

include_source_list_from_file(windowing/os_win32_windowing.cmake)

include_src(os_win32_includes.h)
include_src(os_win32_utils.h)
include_src(os_win32_utils.cc)

group_sources(/OS/Win32)