#pragma once

#include <efi.hh>

namespace efi
{
    extern SystemTable* gSystemTable;
    extern BootServices* gBootServices;
    extern RuntimeServices* gRuntimeServices;
    extern SimpleTextOutputProtocol* gStdOut;
    extern SimpleTextOutputProtocol* gStdErr;
    extern handle gImageHandle;

    inline void InitializeGlobals(handle imageHandle, SystemTable* systemTable)
    {
        gImageHandle = imageHandle;
        gSystemTable = systemTable;

        gBootServices = systemTable->BootServices;
        gRuntimeServices = systemTable->RuntimeServices;

        gStdOut = systemTable->ConOut;
        gStdErr = systemTable->StdErr;

        gStdOut->ClearScreen(gStdOut);
    }
}
