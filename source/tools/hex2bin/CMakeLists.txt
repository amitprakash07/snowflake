cmake_minimum_required(VERSION 3.25.0)

declare_target(Hex2Bin)

include_src(hex_to_bin.cc)
make_executable_target()
group_sources("")
group_target(Tools)
