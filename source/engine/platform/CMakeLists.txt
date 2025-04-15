cmake_minimum_required(VERSION 3.25.0)

declare_target(EnginePlatform)

include_source_list_from_file(platform.cmake)

make_library_target()
group_target(Engine)
