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


void memcpy(void *destination, void *source, u64 length) {
    u8 *bsource = (u8 *) source;
    u8 *bdestination = (u8 *) destination;

    while (length > 0) {
        *bdestination = *bsource;
        *bdestination++;
        *bsource++;
        length--;
    }
}