cmake_minimum_required(VERSION 3.25.0)

declare_target(EngineTests)

include_src(test_win_main.cc)

make_win32_executable_target()
group_target(Engine)