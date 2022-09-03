#include <efi.hh>

#include <kmain.hh>
#include <entry/public/logging.hh>
#include <entry/public/panic.hh>

namespace efi
{
    extern "C" status UefiMain(handle imageHandle, SystemTable* systemTable)
    {
        InitializeGlobals(imageHandle, systemTable);

        gStdErr->OutputString(gStdErr, L"StdErr works!!!!!!!\r\n");

        skyline::KernelMain();

        skyline::debug::Panic("skyline::KernelMain() returned?!");
        return 1;
    }
}
