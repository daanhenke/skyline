#include <arch/x86_64/stackframe.hh>
#include <arch/x86_64/dump_regs.hh>
#include <debug/log.hh>
#include <common/string.hh>

namespace sharedarch::x86_64
{
    void ReadStackFrame(StackFrame* target)
    {
        auto& frames = target->Entries;

        StackRegisters stk;
        GetStackRegisters(&stk);

        auto nextFrame = stk.RBP;
        frames[0].ReturnAddress = GetInstructionPointer();
        frames[0].NextFrame = nextFrame;

        auto i = 1;
        while (nextFrame != 0)
        {
            skyline::debug::Log("frame\n");
            frames[i].ReturnAddress = *reinterpret_cast<umax*>(nextFrame + 8);
            nextFrame = *reinterpret_cast<umax*>(nextFrame);
            frames[i].NextFrame = nextFrame;

            i++;
        }
    }
}
