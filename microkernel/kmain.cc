#include <kmain.hh>
#include <entry/public/logging.hh>

namespace skyline
{
    void KernelMain()
    {
        entry::EarlyLog("Hello\n");
    }
}
