#pragma once

#include <common/numeric.hh>

namespace string
{
    inline umax Length(const char* string)
    {
        auto stringStart = string;
        while (*string++ != '\0');

        return string - stringStart;
    }

    inline bool IsDigit(char character)
    {
        return (character >= '0') && (character <= '9');
    }

    void ToWideString(const char* source, wchar_t* destination, umax destinationSize);

    void Reverse(char* string, umax length);

    inline char* Append(char* destination, const char* source)
    {
        while (*source != '\0') *destination++ = *source++;
        *destination = '\0';
        return destination;
    }

    char* AppendNumber(char* destination, umax source, int base, int padding);

    inline char* AppendDecimal(char* destination, umax source, int padding = 0)
    {
        return AppendNumber(destination, source, 10, padding);
    }

    inline char* AppendHexadecimal(char* destination, umax source, int padding = 0)
    {
        return AppendNumber(destination, source, 16, padding);
    }
}
