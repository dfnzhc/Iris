/**
 * @File Core.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2023/11/17
 * @Brief 
 */

#pragma once

#include "Defines.hpp"

namespace Iris
{

class IRIS_API ExtObj
{
public:
    inline void setVal(int val) { _val = val; }
    inline int  val() const { return _val; }

private:
    int _val = 0;
};

} // namespace Iris
