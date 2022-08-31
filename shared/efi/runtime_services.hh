#pragma once

#include <efi/tables.hh>

namespace efi
{
    typedef struct RuntimeServices
    {
        TableHeader Header;
    } RuntimeServices;
}
