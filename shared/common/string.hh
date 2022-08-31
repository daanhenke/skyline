#pragma once

#include <common/numeric.hh>

namespace string
{
    umax Length(const char* string);
    void ToWideString(const char* source, wchar_t* destination, umax destinationSize);
}
