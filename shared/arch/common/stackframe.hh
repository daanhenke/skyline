#pragma once

#include <common/numeric.hh>

namespace sharedarch
{
    typedef struct
    {
        umax NextFrame;
        umax ReturnAddress;
    } StackFrameEntry;

    typedef struct
    {
        StackFrameEntry Entries[16];
    } StackFrame;
}
