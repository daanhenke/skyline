#include "std/memset.h"

void* memset(void *location, u8 byte, u64 length) {
	u8 *destination = location;

	while (length > 0) {
		*destination = byte;
		destination++;
		length--;
	}

	return location;
}

void *memzero(void *location, u64 length) {
	return memset(location, 0, length);
}