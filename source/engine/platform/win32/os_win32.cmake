cmake_minimum_required(VERSION 3.25.0)

include_src(os_win32_includes.h)
include_src(os_win32_utils.h)
include_src(os_win32_utils.cc)
include_src(os_win32_window_handler.h)
include_src(os_win32_window_handler.cc)

group_sources(/Platform/Win32)