#ifndef ENGINE_GRAPHICS_RENDER_STATS_H_
#define ENGINE_GRAPHICS_RENDER_STATS_H_

#include "engine/common/perf_stats.h"

namespace engine::graphics
{
    enum class RenderStatCountKind : uint8_t
    {
        kRasterizedPixelCount
    };

    class RenderStats : public IStatsBucket
    {
    public:
        void Init() override
        {
            rasterization_timer_      = GetOrCreateTimerStat("Duration");
            rasterized_pixel_counter_ = GetOrCreateCounterStat("PixelCount");
        }

        ~RenderStats() override = default;
        std::shared_ptr<TimerStat>   rasterization_timer_;
        std::shared_ptr<CounterStat> rasterized_pixel_counter_;

        friend class engine::StatsCollector;

    private:
        RenderStats(const std::string& name)
            : IStatsBucket(name)
        {
        }
    };
}  // namespace engine::graphics

#endif  // ENGINE_GRAPHICS_RENDER_STATS_H_