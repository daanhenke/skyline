#include <arch/public.hh>
#include <arch/x86_64/interrupts.hh>

namespace skyline::arch
{
    void InitializeCPU()
    {
        interrupts::SetupIDT();
    }
}
