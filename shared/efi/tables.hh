#pragma once

#include <efi/primitives.hh>
#include <efi/guids.hh>

#include <efi/protocol/simple_text_input_protocol.hh>
#include <efi/protocol/simple_text_output_protocol.hh>

namespace efi
{
    typedef struct
    {
        u64 Signature;
        u32 Revision;
        u32 HeaderSize;
        u32 CRC32;
        u32 Reserved;
    } TableHeader;

    typedef struct
    {
        Guid VendorGuid;
        void* VendorTable;
    } ConfigurationTable;

    struct BootServices;
    struct RuntimeServices;

    typedef struct
    {
        TableHeader Header;
        wchar_t* FirmwareVendor;
        u32 FirmwareRevision;
        handle ConInHandle;
        SimpleTextInputProtocol* ConIn;
        handle ConOutHandle;
        SimpleTextOutputProtocol* ConOut;
        handle StdErrHandle;
        SimpleTextOutputProtocol* StdErr;
        RuntimeServices* RuntimeServices;
        BootServices* BootServices;
        umax NumberOfTableEntries;
        ConfigurationTable* ConfigurationTable;
    } SystemTable;
}
