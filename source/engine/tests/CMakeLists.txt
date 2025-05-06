cmake_minimum_required(VERSION 3.25.0)

declare_target(EngineTests)

include_src(test_win_main.cc)

make_win32_executable_target()
link_target(EngineGpu)
link_target(EngineMaths)
link_target(EnginePlatform)
link_target(EngineShared)
group_target(Engine)