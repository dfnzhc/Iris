/**
 * @File Log.cpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2023/12/12
 * @Brief 
 */

#include <mutex>
#include <unordered_map>
#include <format>
#include <iostream>
#include "Log.hpp"

using namespace Iris;

namespace
{

std::mutex sMutex;

Log::Level sLevel =
#ifdef IRIS_IN_DEBUG
    Log::Level::Debug;
#else
    Log::Level::Info;
#endif

std::unordered_map<std::string_view, Log::notify_t> sSubscribers;

const char* LogLevelString(Log::Level level)
{
    return std::vector{"调试", "通知", "警告", "错误", "致命"}[static_cast<u32>(level)];
}

} // namespace

void Log::log(Level level, std::string_view msg)
{
    std::lock_guard lock{sMutex};

    if (level < sLevel)
        return;
    
    const auto s = std::format("[{}]: {}\n", LogLevelString(level), msg);
    
    auto& os = level < Level::Error ? std::clog : std::cerr;
    os << s;
    os.flush();
    
    if (not sSubscribers.empty())
    {
        for (const auto& [_, notify] : sSubscribers)
            notify(s);
    }
}

void Log::set_level(Log::Level level)
{
    std::lock_guard lock{sMutex};
    sLevel = level;
}

Log::Level Log::level()
{
    std::lock_guard lock{sMutex};
    return sLevel;
}

void Log::subscribe(std::string_view name, Log::notify_t&& notify)
{
    std::lock_guard lock{sMutex};
    sSubscribers.emplace(name, std::move(notify));
}

void Log::unsubscribe(std::string_view name)
{
    std::lock_guard lock{sMutex};
    sSubscribers.extract(name);
}
