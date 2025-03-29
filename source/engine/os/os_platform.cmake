cmake_minimum_required(VERSION 3.25.0)

include_source_list_from_file(win32/os_win32.cmake)

include_src(os_file_system.h)
include_src(os_file_system.cc)

group_sources(/OS)