#include <efi.hh>

namespace efi
{
    extern "C" status UefiMain(handle imageHandle, SystemTable* systemTable)
    {
        systemTable->ConOut->OutputString(systemTable->ConOut, L"ConOut works\r\n");
        systemTable->StdErr->OutputString(systemTable->ConOut, L"StdErr works\r\n");

        systemTable->BootServices->WaitForEvent(1, &systemTable->ConIn->WaitForKey, nullptr);
        return 0;
    }
}
