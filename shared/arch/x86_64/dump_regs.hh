#pragma once

#include <common/numeric.hh>

namespace sharedarch::x86_64
{
    typedef struct
    {
        umax RBP;
        umax RSP;
    } StackRegisters;

    extern "C" void GetStackRegisters(StackRegisters* regs);
    extern "C" umax GetInstructionPointer();
}
