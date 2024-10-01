cmake_minimum_required(VERSION 3.25.0)

declare_target(CodingProblems)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_src(interface.h)
include_src(list.h)
include_src(main.cc)
include_source_list_from_file(leetcode/leetcode.cmake)
include_source_list_from_file(others/others.cmake)

make_executable_target()
target_link_libraries(CodingProblems EngineShared)
group_sources("")
group_target(CodingProblems)