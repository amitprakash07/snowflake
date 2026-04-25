#ifndef CORE_GRAPHICS_RENDER_STATS_H_
#define CORE_GRAPHICS_RENDER_STATS_H_

#include "core/common/core.h"
#include "core/common/perf_stats.h"
#include "core/graphics_common/render_primitives.h"

namespace amit::graphics
{
    enum class RenderStatCounter : uint8_t
    {
        kRasterizedPixelCount = 0,
        kRenderStatCounterTypesCount
    };

    inline std::string_view EnumTypeToString(RenderStatCounter counter_type)
    {
        switch (counter_type)
        {
        case RenderStatCounter::kRasterizedPixelCount:
            return "Rasterized Pixel Count";
        case RenderStatCounter::kRenderStatCounterTypesCount:
            break;
        }
        return "InvalidRenderStatCounterType";
    }

    class DrawCallStats : public IStatsBucket
    {
    public:
        friend class amit::StatsCollector;
        friend class ScopedDrawCallStats;

    private:
        DrawCallStats(const std::string& name)
            : IStatsBucket(name)
            , draw_call_stat_id_(IdGenerator::GetNextId())
        {
        }

        void Init() override
        {
            draw_timer_ = GetOrCreateTimerStat("Duration");
            draw_timer_->StartTimer();
        }

        template <RenderPrimitiveType PrimitiveType>
        void StartPrimitiveStats(const RenderPrimitive<PrimitiveType>& primitive)
        {
            const ObjectId& primitive_id = primitive.GetId();
            if (primitive_draw_stats_.contains(primitive_id))
            {
                return;
            }

            primitive_draw_stats_[primitive_id]                 = std::make_shared<PrimitiveDrawStats>();
            std::shared_ptr<PrimitiveDrawStats> primitive_stats = primitive_draw_stats_[primitive_id];

            primitive_stats->draw_timer_ = GetOrCreateTimerStat("Duration");

            for (size_t i = 0; i < static_cast<size_t>(RenderStatCounter::kRenderStatCounterTypesCount); ++i)
            {
                std::string counter_name      = std::string(EnumTypeToString(static_cast<RenderStatCounter>(i)));
                primitive_stats->counters_[i] = GetOrCreateCounterStat(counter_name);
            }

            primitive_stats->draw_timer_->StartTimer();
        }

        template <RenderPrimitiveType PrimitiveType>
        void IncrementPrimitiveStatCount(const RenderPrimitive<PrimitiveType>& primitive,
                                         RenderStatCounter                     count_kind,
                                         uint64_t                              count = 1)
        {
            const ObjectId& primitive_id = primitive.GetId();
            std::shared_ptr<CounterStat> stat_counter =
                primitive_draw_stats_[primitive_id]->counters_[static_cast<size_t>(count_kind)];
            stat_counter->Increment(count);
        }

        template <RenderPrimitiveType PrimitiveType>
        void EndPrimitiveStats(const RenderPrimitive<PrimitiveType>& primitive)
        {
            primitive_draw_stats_[primitive.GetId()]->draw_timer_->EndTimer();
        }

        void EndStats()
        {
            if (draw_timer_)
            {
                draw_timer_->EndTimer();
            }
        }

        struct PrimitiveDrawStats
        {
            std::shared_ptr<TimerStat> draw_timer_;
            std::array<std::shared_ptr<CounterStat>,
                       static_cast<size_t>(RenderStatCounter::kRenderStatCounterTypesCount)>
                counters_;
        };

        std::unordered_map<ObjectId, std::shared_ptr<PrimitiveDrawStats>> primitive_draw_stats_;
        ObjectId                                                          draw_call_stat_id_;
        std::shared_ptr<TimerStat>                                        draw_timer_;
    };

    class ScopedDrawCallStats
    {
    public:
        ScopedDrawCallStats(bool collect_stats, const std::string& name = "DrawCallStats")
            : collect_stats_(collect_stats)
        {
            if (collect_stats_)
            {
                draw_call_stats_ = StatsCollector::GetInstance().GetOrCreateStatsBucket<DrawCallStats>(name);
            }
        }

        template <RenderPrimitiveType PrimitiveType>
        void StartPrimitiveDraw(const RenderPrimitive<PrimitiveType>& primitive)
        {
            if (!collect_stats_)
            {
                return;
            }

            draw_call_stats_->StartPrimitiveStats(primitive);
        }

        template <RenderPrimitiveType PrimitiveType>
        void IncrementPrimitiveStatCount(const RenderPrimitive<PrimitiveType>& primitive,
                                         RenderStatCounter                     count_kind,
                                         uint64_t                              count = 1)
        {
            if (!collect_stats_)
            {
                return;
            }

            draw_call_stats_->IncrementPrimitiveStatCount(primitive, count_kind, count);
        }

        template <RenderPrimitiveType PrimitiveType>
        void EndPrimitiveDraw(const RenderPrimitive<PrimitiveType>& primitive)
        {
            if (!collect_stats_)
            {
                return;
            }

            draw_call_stats_->EndPrimitiveStats(primitive);
        }

        ScopedDrawCallStats(const ScopedDrawCallStats&)            = delete;
        ScopedDrawCallStats& operator=(const ScopedDrawCallStats&) = delete;

        ~ScopedDrawCallStats()
        {
            EndScope();
        }

    private:
        void EndScope()
        {
            if (!collect_stats_)
            {
                return;
            }

            if (draw_call_stats_)
            {
                draw_call_stats_->EndStats();
            }
        }

        std::shared_ptr<DrawCallStats> draw_call_stats_;
        bool                           collect_stats_;
    };

}  // namespace amit::graphics

#endif  // CORE_GRAPHICS_RENDER_STATS_H_