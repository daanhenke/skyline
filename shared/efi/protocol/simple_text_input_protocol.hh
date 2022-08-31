#pragma once

#include <efi/primitives.hh>
#include <efi/guids.hh>

namespace efi
{
    namespace guids
    {
        static Guid SimpleTextInputProtocol = {0x387477c1, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
    }

    typedef struct
    {
        u16 ScanCode;
        u16 UnicodeChar;
    } InputKey;

    typedef struct SimpleTextInputProtocol
    {
        status (*Reset)(SimpleTextInputProtocol* thiz, bool ExtendedVerification);
        status (*ReadKeyStroke)(SimpleTextInputProtocol* thiz, InputKey* key);
        event WaitForKey;
    } SimpleTextInputProtocol;
}
