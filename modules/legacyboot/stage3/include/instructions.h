#pragma once
#include "types.h"

void enable_interrupts();
void disable_interrupts();

u8 inb(u16 port);
void outb(u16 port, u8 value);

u16 inw(u16 port);
void outw(u16 port, u16 value);

u32 ind(u16 port);
void outd(u16 port, u32 value);