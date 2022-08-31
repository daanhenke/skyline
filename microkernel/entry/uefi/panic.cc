#include <entry/public/panic.hh>
#include <entry/public/logging.hh>

#include <efi/global.hh>

namespace skyline::entry
{
    void EarlyPanic(const char* message)
    {
        EarlyLog("-----!PANIC!-----\nReason: \"");
        EarlyLog(message);
        EarlyLog("\"\nPress any key to return to the uefi bootloader\nThe system might be unstable from this point on :(\n-----!PANIC!-----\n");

        efi::gBootServices->WaitForEvent(1, &efi::gSystemTable->ConIn->WaitForKey, nullptr);
    }
}
