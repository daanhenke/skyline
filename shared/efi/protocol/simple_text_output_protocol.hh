#pragma once

#include <efi/primitives.hh>
#include <efi/guids.hh>

namespace efi
{
    namespace guids
    {
        static Guid SimpleTextOutputProtocol = {0x387477c2, 0x69c7, 0x11d2, {0x82, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
    }

    typedef struct
    {
        s32 MaxMode;
        s32 Mode;
        s32 Attributes;
        s32 CursorColumn;
        s32 CursorRow;
        bool CursorVisible;
    } SimpleTextOutputMode;

    typedef struct SimpleTextOutputProtocol
    {
        status (*Reset)(SimpleTextOutputProtocol* thiz, bool ExtendedVerification);
        status (*OutputString)(SimpleTextOutputProtocol* thiz, const wchar_t* string);
        status (*TestString)(SimpleTextOutputProtocol* thiz, const wchar_t* string);
        status (*QueryMode)(SimpleTextOutputProtocol* thiz, umax modeNumber, umax* columns, umax* rows);
        status (*SetMode)(SimpleTextOutputProtocol* thiz, umax modeNumber);
        status (*SetAttribute)(SimpleTextOutputProtocol* thiz, umax attribute);
        status (*ClearScreen)(SimpleTextOutputProtocol* thiz);
        status (*SetCursorPosition)(SimpleTextOutputProtocol* thiz, umax column, umax row);
        status (*EnableCursor)(SimpleTextOutputProtocol* thiz, bool visible);
        SimpleTextOutputMode* Mode;
    } SimpleTextOutputProtocol;
}
