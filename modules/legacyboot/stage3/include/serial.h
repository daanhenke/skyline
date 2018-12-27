#pragma once
#include "types.h"

void serial_init(u16 port);

bool serial_can_read(u16 port);
bool serial_can_write(u16 port);

u8 serial_read(u16 port);
void serial_write(u16 port, u8 data);

void serial_write_string(u16 port, const char *string);