#include <efi.hh>

#include <kmain.hh>
#include <entry/public/logging.hh>

namespace efi
{
    extern "C" status UefiMain(handle imageHandle, SystemTable* systemTable)
    {
        InitializeGlobals(imageHandle, systemTable);

        gStdErr->OutputString(gStdErr, L"StdErr works!!!!!!!\r\n");

        skyline::KernelMain();

        skyline::entry::EarlyLog("KernelMain() returned!\r\n");
        gBootServices->WaitForEvent(1, &systemTable->ConIn->WaitForKey, nullptr);
        return 0;
    }
}
