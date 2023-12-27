/**
 * @File LogTest.cpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2023/12/27
 * @Brief 
 */

#include <gtest/gtest.h>
#include <Base/Log.hpp>

using namespace Iris;

TEST(Log, Basic)
{
    const auto str = "世界";
       
    Debug("你好 {} 👽42", str);
    Info("你好 {} 👽42", str);
    Warn("你好 {} 👽42", str);
    Error("你好 {} 👽42", str);
    Fatal("你好 {} 👽42", str);
}