#pragma once

#include <efi/primitives.hh>

namespace efi
{
    typedef struct
    {
        u32 d1;
        u16 d2;
        u16 d3;
        u8 d4[8];
    } Guid;
}
