/**
 * @File BaseTest.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2023/12/19
 * @Brief 
 */

#pragma once

#include <gtest/gtest.h>
#include <Iris/Base/TypeName.hpp>

using namespace Iris;

class DummyClass
{
    
};

IRIS_TYPE_NAME(DummyClass)

TEST(TreeBase, type_name)
{
    EXPECT_STREQ(type_name<bool>(), "bool");
    
    EXPECT_STREQ(type_name<int8_t>(), "i8");
    EXPECT_STREQ(type_name<uint8_t>(), "u8");

    EXPECT_STREQ(type_name<int16_t>(), "i16");
    EXPECT_STREQ(type_name<uint16_t>(), "u16");
    
    EXPECT_STREQ(type_name<int32_t>(), "i32");
    EXPECT_STREQ(type_name<uint32_t>(), "u32");
    
    EXPECT_STREQ(type_name<int64_t>(), "i64");
    EXPECT_STREQ(type_name<uint64_t>(), "u64");

    EXPECT_STREQ(type_name<f32>(), "f32");
    EXPECT_STREQ(type_name<f64>(), "f64");

    EXPECT_STREQ(type_name<std::string>(), "string");
    EXPECT_STREQ(type_name<std::string_view>(), "string_view");

    EXPECT_STREQ(type_name<DummyClass>(), "DummyClass");
}