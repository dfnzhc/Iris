/**
 * @File TypeName.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2023/12/19
 * @Brief 
 */

#pragma once

#include <typeinfo>
#include "Core/Defines.hpp"

namespace Iris
{

template<typename T> constexpr const char* type_name() noexcept { return typeid(T).name(); }
template<typename T> constexpr const char* type_name(const T&) noexcept { return type_name<T>(); }

#define IRIS_DEFINE_TYPE_NAME(type, name) \
    template<> constexpr const char* type_name<type>() noexcept { return #name; }

IRIS_DEFINE_TYPE_NAME(std::string, string)
IRIS_DEFINE_TYPE_NAME(std::string_view, string_view)

IRIS_DEFINE_TYPE_NAME(u8, u8)
IRIS_DEFINE_TYPE_NAME(u16, u16)
IRIS_DEFINE_TYPE_NAME(u32, u32)
IRIS_DEFINE_TYPE_NAME(u64, u64)

IRIS_DEFINE_TYPE_NAME(i8, i8)
IRIS_DEFINE_TYPE_NAME(i16, i16)
IRIS_DEFINE_TYPE_NAME(i32, i32)
IRIS_DEFINE_TYPE_NAME(i64, i64)

IRIS_DEFINE_TYPE_NAME(f32, f32)
IRIS_DEFINE_TYPE_NAME(f64, f64)

#undef IRIS_DEFINE_TYPE_NAME

#define IRIS_TYPE_NAME(Type)                                                            \
    template<> constexpr const char* Iris::type_name<Type>() noexcept { return #Type; } \
    template<> constexpr const char* Iris::type_name<const Type>() noexcept { return "const "#Type; }

} // namespace Iris