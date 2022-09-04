#pragma once

#include <common/numeric.hh>
#include <arch/common/stackframe.hh>

namespace sharedarch::x86_64
{
    void ReadStackFrame(StackFrame* target);
}
