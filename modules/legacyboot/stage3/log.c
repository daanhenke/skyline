#include "log.h"
#include "screen.h"
#include "types.h"

void log_string(u8 level, const char* string) {
	screen_print_string_attr("[LOG] ", level);
	log_string_raw(level, string);
}

void log_string_raw(u8 level, const char* string) {
	screen_print_string_attr(string, level);
}


//TODO: make this less horrible
void log_u4(u8 level, u8 number) {
	const char* lookup_table = "0123456789ABCDEF";
	char created_string[2] = "0";

	created_string[0] = lookup_table[number & 0xF];
	log_string_raw(level, created_string);
}

void log_u8(u8 level, u8 number) {
	log_u4(level, (number & 0xF0) >> 4);
	log_u4(level, number & 0xF);
}

void log_u16(u8 level, u16 number) {
	log_u8(level, (number & 0xFF00) >> 8);
	log_u8(level, number & 0xFF);
}

void log_u32(u8 level, u32 number) {
	log_u16(level, (number & 0xFFFF0000) >> 16);
	log_u16(level, number & 0xFFFF);
}

void log_u64(u8 level, u64 number) {
	log_u32(level, (number & 0xFFFFFFFF00000000) >> 32);
	log_u32(level, number & 0xFFFFFFFF);
}