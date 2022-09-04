#pragma once

#include <common/numeric.hh>

namespace sharedarch::x86_64
{
    typedef struct
    {
        u16 Size;
        u64 Offset: 48;
    } DescriptorRegister;
}
