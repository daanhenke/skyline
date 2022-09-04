#pragma once

namespace skyline::interrupts
{
    void SetupIDT();
    extern "C" void InterruptHandler();
}
