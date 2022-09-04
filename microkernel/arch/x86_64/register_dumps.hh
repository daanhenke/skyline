#pragma once

#include <common/numeric.hh>

namespace skyline::arch
{
    struct GeneralPurposeRegisterDump
    {
        umax RAX;
        umax RBX;
        umax RCX;
        umax RDX;

        umax RSI;
        umax RDI;
        umax RBP;
        umax RSP;

        umax R8;
        umax R9;
        umax R10;
        umax R11;
        umax R12;
        umax R13;
        umax R14;
        umax R15;
    };
}
