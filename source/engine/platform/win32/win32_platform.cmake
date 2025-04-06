cmake_minimum_required(VERSION 3.25.0)

include_src(win32_resource.h)
include_src(win32_includes.h)
include_src(win32_platform.cc)
include_src(win32_windowing.cc)

group_sources(/Platform/Win32)