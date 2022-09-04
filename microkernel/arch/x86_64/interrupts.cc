#include <arch/x86_64/interrupts.hh>
#include <debug/panic.hh>
#include <debug/log.hh>
#include <common/string.hh>

#include <arch/x86_64/idt.hh>

namespace skyline::interrupts
{
    using namespace sharedarch;

    x86_64::IDTEntry gIDT[128];
    extern "C" const u8* gInterruptHandlerStubs;

    void SetupIDT()
    {
        debug::Log("Setting up IDT\n");

        char buff[512];
        auto end = string::Append(buff, "Stubs @ ");
        end = string::AppendHexadecimal(end, reinterpret_cast<umax>(&gInterruptHandlerStubs));
        end = string::Append(end, "\n");
        debug::Log(buff);
    }

    void InterruptHandler()
    {
        debug::Panic("Received interrupt!");
    }
}
