#pragma once

#include <common/numeric.hh>

namespace sharedarch::x86_64
{
    typedef uptr GeneralPurposeRegisters[8];

    extern "C" void _hlt();

    extern "C" void _get_general_purpose_registers(GeneralPurposeRegisters regs);
}
