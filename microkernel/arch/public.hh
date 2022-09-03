#pragma once

namespace skyline::arch
{
    void InitializeCPU();


    struct GeneralPurposeRegisterDump;
    extern "C" void EarlyDumpGeneralPurposeRegisters();
    extern "C" GeneralPurposeRegisterDump* EarlyGetGeneralPurposeRegistersDump();
}
