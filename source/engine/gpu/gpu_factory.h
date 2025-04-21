#ifndef ENGINE_GPU_GPU_FACTORY_H_
#define ENGINE_GPU_GPU_FACTORY_H_

#include <vector>

#include <dxgi1_6.h>

namespace engine
{
    class GpuDevice;

    class GpuFactory
    {
    public:
        [[nodiscard]] bool Initialize();
        GpuFactory();

        [[nodiscard]] uint8_t GetDeviceCount() const;

        [[nodiscard]] GpuDevice* GetDevice(uint8_t device_adapter = 0) const;

        GpuFactory(GpuFactory&)  = delete;
        GpuFactory(GpuFactory&&) = delete;

        GpuFactory& operator=(const GpuFactory&)  = delete;
        GpuFactory& operator=(const GpuFactory&&) = delete;

    private:
        IDXGIFactory2*                  dxgi_factory_;
        std::vector<IDXGIAdapter1*>     available_adapters_;
        mutable std::vector<GpuDevice*> adapter_devices_;
    };

}  // namespace engine

#endif