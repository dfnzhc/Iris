/**
 * @File Log.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2023/12/12
 * @Brief 
 */

#pragma once

#include <Core/Defines.hpp>
#include <functional>
#include <source_location>
#include <string_view>
#include <sstream>

namespace Iris
{

class IRIS_API Log
{
public:
    enum class Level
    {
        Debug,
        Info,
        Warn,
        Error,
        Fatal,
    };

    static void log(Level level, std::string_view msg);

    static void  set_level(Level level);
    static Level level();

    using notify_t = std::function<void(std::string_view)>;
    static void subscribe(std::string_view name, notify_t&& notify);
    static void unsubscribe(std::string_view name);
};

namespace detail
{

inline std::string FormatMessageWithSourceInfo(std::string_view msg, const std::source_location& location)
{
    std::stringstream ss;
    ss << "File: "
       << location.file_name() << "("
       << location.line() << ":"
       << location.column() << ") `"
       << location.function_name() << "`: "
       << msg;

    return ss.str();
}

} // namespace detail

// clang-format off
inline void Debug(const std::string_view msg) { Log::log(Log::Level::Debug, msg); }
inline void Info(const std::string_view msg) { Log::log(Log::Level::Info, msg); }
inline void Warn(const std::string_view msg) { Log::log(Log::Level::Warn, msg); }

inline void Error(const std::string_view msg, const std::source_location location = std::source_location::current()) { Log::log(Log::Level::Error, detail::FormatMessageWithSourceInfo(msg, location)); }
inline void Fatal(const std::string_view msg, const std::source_location location = std::source_location::current()) { Log::log(Log::Level::Fatal, detail::FormatMessageWithSourceInfo(msg, location)); }

template<typename... Args>
inline void Debug(std::format_string<Args...> fmt, Args&&... args) { Debug(std::format(fmt, std::forward<Args>(args)...)); }

template<typename... Args>
inline void Info(std::format_string<Args...> fmt, Args&&... args) { Info(std::format(fmt, std::forward<Args>(args)...)); }

template<typename... Args>
inline void Warn(std::format_string<Args...> fmt, Args&&... args) { Warn(std::format(fmt, std::forward<Args>(args)...)); }

template<typename... Args>
inline void Error(std::format_string<Args...> fmt, Args&&... args) { Log::log(Log::Level::Error, std::format(fmt, std::forward<Args>(args)...)); }

template<typename... Args>
inline void Fatal(std::format_string<Args...> fmt, Args&&... args) { Log::log(Log::Level::Fatal, std::format(fmt, std::forward<Args>(args)...)); }
// clang-format on

} // namespace Iris