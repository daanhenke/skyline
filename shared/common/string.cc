#include <common/string.hh>

namespace string
{
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

    inline void SwapCharacters(char* a, char* b)
    {
        auto temp = *a;
        *a = *b;
        *b = temp;
    }

    void Reverse(char* string, umax length)
    {
        umax start = 0;
        umax end = length - 1;
        while (start < end)
        {
            SwapCharacters(string + start++, string + end--);
        }
    }

    char* AppendNumber(char* destination, umax source, int base, int padding = 0)
    {
        umax i = 0;
        bool isNegative = false;

        if (source == 0)
        {
            destination[i++] = '0';
            destination[i] = '\0';

            return destination + i;
        }

        if (source < 0 && base == 10)
        {
            isNegative = true;
            source = -source;
        }

        while (source > 0)
        {
            auto remainder = source % base;
            destination[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
            source /= base;
        }

        if (isNegative) destination[i++] = '-';

        while (i < padding)
        {
            destination[i++] = '0';
        }

        destination[i] = '\0';
        Reverse(destination, i);

        return destination + i;
    }
}
