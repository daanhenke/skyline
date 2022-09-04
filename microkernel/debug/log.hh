#pragma once

#include <entry/public/logging.hh>

namespace skyline::debug
{
    inline void Log(const char* message)
    {
        entry::EarlyLog(message);
    }
}
