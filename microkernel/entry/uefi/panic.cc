#include <entry/public/panic.hh>
#include <entry/public/logging.hh>

#include <efi/global.hh>
#include <arch/x86_64/wrappers.hh>

using namespace sharedarch;

namespace skyline::entry
{
    void EarlyPanic(const char* message)
    {
        EarlyLog("-----!PANIC!-----\nReason: \"");
        EarlyLog(message);
        EarlyLog("\"\n-----!PANIC!-----\n");
        EarlyLog("Halting...\n");

        x86_64::_hlt();
    }
}
