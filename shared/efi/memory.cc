#include <efi/memory.hh>
#include <efi/global.hh>

namespace efi
{
    inline void* Allocate(umax size)
    {
        void* result = nullptr;
        gBootServices->AllocatePool(MemoryType::BootServicesData, size, &result);
        return result;
    }

    inline void Free(void* ptr)
    {
        gBootServices->FreePool(ptr);
    }
}


void* operator new(size_t count)
{
    return efi::Allocate(count);
}

void operator delete(void* ptr) noexcept
{
    efi::Free(ptr);
}

void* operator new[](size_t count)
{
    return efi::Allocate(count);
}

void operator delete[](void* ptr) noexcept
{
    efi::Free(ptr);
}
