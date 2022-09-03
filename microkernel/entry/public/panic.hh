#pragma once

#include <debug/panic.hh>

namespace skyline::entry
{
    void EarlyPanic(const char* message, debug::PanicDump* dump, const char* function, const char* fileName, int lineNumber);
}
