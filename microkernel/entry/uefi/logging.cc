#include <entry/public/logging.hh>

#include <common/string.hh>

#include <efi/global.hh>

namespace skyline::entry
{
    void EarlyLog(const char* message)
    {
        auto messageLength = string::Length(message);
        auto wideMessage = new wchar_t[messageLength + 1];

        string::ToWideString(message, wideMessage, sizeof(wchar_t) * (messageLength + 1));
        efi::gStdOut->OutputString(efi::gStdOut, wideMessage);
        delete wideMessage;
    }
}
