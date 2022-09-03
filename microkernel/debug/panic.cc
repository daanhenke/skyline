#include <debug/panic.hh>
#include <entry/public/panic.hh>

namespace skyline::debug
{
    void KPanic(const char* reason, const char* function, const char* fileName, int lineNumber, PanicDump* dump)
    {
        entry::EarlyPanic(reason, dump, function, fileName, lineNumber);
    }
}
