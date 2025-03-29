cmake_minimum_required(VERSION 3.25.0)

include_src(win32_platform_includes.h)
include_src(win32_platform.h)
include_src(win32_platform.cc)
# include_src(os_win32_window_handler.h)
# include_src(os_win32_window_handler.cc)

group_sources(/Platform/Win32)