#pragma once

#include <common/numeric.hh>

namespace efi
{
    typedef u64 status;

    typedef void* handle;
    typedef void* event;

    enum class MemoryType
    {
        Reserved = 0,
        LoaderCode,
        LoaderData,
        BootServicesCode,
        BootServicesData,
        RuntimeServicesCode,
        RuntimeServicesData,
        ConventionalMemory,
        UnusableMemory,
        ACPIReclaimMemory,
        ACPIMemoryNVS,
        MemoryMappedIO,
        MemoryMappedIOPortSpace,
        PalCode,
        PersistentMemory,
        Max
    };
}
