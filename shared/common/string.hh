#pragma once

#include <common/numeric.hh>

namespace string
{
    umax Length(const char* string);
    void ToWideString(const char* source, wchar_t* destination, umax destinationSize);

    void Append(char* destination, const char* source);
    void AppendDecimal(char* destination, umax source);
    void AppendHexadecimal(char* destination, umax source);
}
