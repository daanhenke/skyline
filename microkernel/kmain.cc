#include <kmain.hh>

#include <entry/public/logging.hh>
#include <arch/public.hh>

namespace skyline
{
    void KernelMain()
    {
        entry::EarlyLog("Skyline Kernel 0.0.1\n");

        arch::InitializeCPU();
    }
}
