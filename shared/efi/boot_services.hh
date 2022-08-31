#pragma once

#include <efi/tables.hh>

namespace efi
{
    typedef struct BootServices
    {
        TableHeader Header;
        status (*Foo000)();
        status (*Foo001)();
        status (*Foo002)();
        status (*Foo003)();
        status (*Foo004)();
        status (*Foo005)();
        status (*Foo006)();
        status (*Foo007)();
        status (*Foo008)();
        status (*WaitForEvent)(umax numberOfEvents, event* events, umax* index);
    } BootServices;
}
