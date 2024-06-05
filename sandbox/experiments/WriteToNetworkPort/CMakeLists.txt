cmake_minimum_required(VERSION 3.25.0)

declare_target(WriteToNetworkPort)
include_src(write_to_network.cc)
make_executable_target()
group_sources("")
group_target("")

