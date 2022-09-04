#pragma once

#include <common/numeric.hh>
#include <arch/x86_64/common.hh>

namespace sharedarch::x86_64
{
    typedef DescriptorRegister IDTR;

    typedef struct
    {
        u16 Offset1;
        u16 SegmentSelector;
        u8 IST;
        u8 GateType: 4;
        u8 Zero: 1;
        u8 DPL: 2;
        u8 Present: 1;
        u16 Offset2;
        u32 Offset3;
        u32 Reserved;
    } IDTEntry;
}
