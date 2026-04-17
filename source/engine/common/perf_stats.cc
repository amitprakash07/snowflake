#include <format>

#include "perf_stats.h"

uint64_t engine::Stat::stat_timer_id_counter_           = static_cast<uint64_t>(StatType::kTimer);
uint64_t engine::Stat::stat_counter_id_counter_         = static_cast<uint64_t>(StatType::kCounter);
uint64_t engine::IStatsBucket::stats_bucket_id_counter_ = 0;

engine::Stat::Stat(StatType type, const std::string& name)
    : type_(type)
    , name_(name)
{
    if (type_ == StatType::kTimer)
    {
        stat_id_ = ++stat_timer_id_counter_;
    }
    else if (type_ == StatType::kCounter)
    {
        stat_id_ = ++stat_counter_id_counter_;
    }
}

std::string engine::IStatsBucket::ToString() const
{
    std::string ret_string = std::format("\n{}\n", name_);

    for (const auto& [timer_name, timer_stat] : timer_stats_)
    {
        ret_string += std::format("\t{}:{:.2f} ms\n", timer_name, timer_stat->GetElapsedMilliseconds());
    }

    for (const auto& [counter_name, counter_stat] : counter_stats_)
    {
        ret_string += std::format("\t{}:{}\n", counter_name, counter_stat->GetCount());
    }

    return ret_string;
}

engine::IStatsBucket::IStatsBucket(const std::string& name)
    : name_(name)
    , stat_bucket_label_(StatType::kStatBucket)
{
    bucket_id_ = ++stats_bucket_id_counter_;
}

std::shared_ptr<engine::TimerStat> engine::IStatsBucket::GetOrCreateTimerStat(const std::string& name)
{
    if (!timer_stats_.contains(name))
    {
        timer_stats_[name] = std::make_shared<TimerStat>(name);
    }

    return timer_stats_[name];
}

std::shared_ptr<engine::CounterStat> engine::IStatsBucket::GetOrCreateCounterStat(const std::string& name)
{
    if (!counter_stats_.contains(name))
    {
        counter_stats_[name] = std::make_shared<CounterStat>(name);
    }

    return counter_stats_[name];
}
