#include <kmain.hh>

#include <entry/public/logging.hh>
#include <arch/public.hh>
#include <common/string.hh>

#include <arch/x86_64/interrupts.hh>

namespace skyline
{
    void KernelMain()
    {
        entry::EarlyLog("Skyline Kernel 0.0.1\n");

        char buff[512];
        auto newLoc = string::Append(buff, "Test: ");
        newLoc = string::AppendDecimal(newLoc, 1337);
        newLoc = string::Append(newLoc, "\n");
        entry::EarlyLog(buff);

        arch::InitializeCPU();

        interrupts::InterruptHandler();
        void (*CrashSystem)() = nullptr;
        CrashSystem();
    }
}
