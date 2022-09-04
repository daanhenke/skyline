#include <arch/public.hh>

#include <arch/x86_64/stackframe.hh>

namespace skyline::arch
{
    void GetStackFrame(sharedarch::StackFrame* stackFrame)
    {
        sharedarch::x86_64::ReadStackFrame(stackFrame);
    }
}
