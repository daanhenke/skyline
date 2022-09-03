#pragma once

#include <common/numeric.hh>
#include <arch/public.hh>

#define Panic(reason) KPanic(reason, __FUNCTION__, __FILE__, __LINE__)

namespace skyline::debug
{
    struct GeneralPurposeRegisterDump;
    typedef struct
    {
        umax UsableGroups;
        arch::GeneralPurposeRegisterDump* GP;
    } PanicDump;

    void KPanic(const char* reason, const char* function, const char* fileName, int lineNumber, PanicDump* dump);
    inline void KPanic(const char* reason, const char* function, const char* fileName, int lineNumber)
    {
        arch::EarlyDumpGeneralPurposeRegisters();

        PanicDump dump;
        dump.UsableGroups = 255; // TODO: IMPLEMENT THIS
        dump.GP = arch::EarlyGetGeneralPurposeRegistersDump();

        KPanic(reason, function, fileName, lineNumber, &dump);
    }

}
