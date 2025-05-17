cmake_minimum_required(VERSION 3.25.0)

declare_target(EngineGpu)

include_src(gpu_factory.h)
include_src(gpu_factory.cc)
include_src(gpu_device.h)
include_src(gpu_device.cc)
include_src(gpu_device_resource.h)
include_src(gpu_device_resource.cc)

make_library_target()
link_target(d3d12.dll)
link_target(dxgi.dll)
group_target(Engine)

add_subdirectory(hlsl)