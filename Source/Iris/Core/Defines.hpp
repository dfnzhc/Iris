/**
 * @File Defines.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2023/11/17
 * @Brief 
 */

#pragma once

#include <cstdint>
#include <cstddef>

// -------------------------
//关于平台、编译器、语言的宏定义

#if defined(_MSC_VER)
#    define IRIS_API_EXPORT __declspec(dllexport)
#    define IRIS_API_IMPORT __declspec(dllimport)
#elif defined(__clang__) || defined
#    define IRIS_API_EXPORT __attribute__((visibility("default")))
#    define IRIS_API_IMPORT __attribute__((visibility("default")))
#else
#    define IRIS_API_EXPORT
#    define IRIS_API_IMPORT
#endif

#ifdef IRIS_DLL
#    define IRIS_API IRIS_API_EXPORT
#else
#    define IRIS_API IRIS_API_IMPORT
#endif

#define IRIS_NODISCARD [[nodiscard]]
#define IRIS_UNUSED [[maybe_unused]]

namespace Iris
{

#ifdef _DEBUG
#    define IRIS_IN_DEBUG
constexpr auto kIsDebug = true;
#endif

#ifdef NDEBUG
#    define IRIS_IN_RELEASE
constexpr auto kIsRelease = true;
#endif

// -------------------------
// 数字类型的别名
// -------------------------

// @formatter:off
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;

using Uint = unsigned int;
using Size = std::size_t;

constexpr i8  kI8Min  = INT8_MIN;
constexpr i16 kI16Min = INT16_MIN;
constexpr i32 kI32Min = INT32_MIN;
constexpr i64 kI64Min = INT64_MIN;

constexpr u8  kI8Max  = INT8_MAX;
constexpr u16 kI16Max = INT16_MAX;
constexpr u32 kI32Max = INT32_MAX;
constexpr u64 kI64Max = INT64_MAX;

constexpr u8  kU8Max  = UINT8_MAX;
constexpr u16 kU16Max = UINT16_MAX;
constexpr u32 kU32Max = UINT32_MAX;
constexpr u64 kU64Max = UINT64_MAX;
// @formatter:on

} // namespace Iris
