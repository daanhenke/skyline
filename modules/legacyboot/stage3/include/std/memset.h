#pragma once
#include "types.h"

void* memset(void *location, u8 byte, u64 length);
void* memzero(void *location, u64 length);
void memcpy(void *destination, void *source, u64 length);