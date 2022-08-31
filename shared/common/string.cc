#include <common/string.hh>

namespace string
{
    inline umax Length(const char* string)
    {
        auto stringStart = string;
        while (*string++ != '\0');

        return string - stringStart;
    }

    void ToWideString(const char* source, wchar_t* destination, umax destinationSize)
    {
        auto sourceLength = Length(source);
        if (sourceLength * sizeof(wchar_t) >= destinationSize) return;

        umax sourceIndex = 0, destinationIndex = 0;
        while (sourceIndex < sourceLength)
        {
            auto currentChar = source[sourceIndex++];

            // Inject carriage-returns for unix esque linebreaks
            if (currentChar == '\n')
            {
                destination[destinationIndex++] = L'\r';
            }

            destination[destinationIndex++] = static_cast<wchar_t>(currentChar);
        }

        destination[destinationIndex] = L'\0';
    }
}
