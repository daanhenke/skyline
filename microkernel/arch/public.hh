#pragma once

#include <arch/common/stackframe.hh>

namespace skyline::arch
{
    void InitializeCPU();


    struct GeneralPurposeRegisterDump;
    extern "C" void EarlyDumpGeneralPurposeRegisters();
    extern "C" GeneralPurposeRegisterDump* EarlyGetGeneralPurposeRegistersDump();

    void GetStackFrame(sharedarch::StackFrame* stackFrame);
}
