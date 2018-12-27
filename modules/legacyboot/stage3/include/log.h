#pragma once
#include "screen.h"
#include "types.h"

#define LOG_ERROR (COLOR(COLOR_RED, COLOR_BLACK))
#define LOG_WARNING (COLOR(COLOR_YELLOW, COLOR_BLACK))
#define LOG_STATUS COLOR(COLOR_GRAY, COLOR_BLACK)
#define LOG_SUCCESS COLOR(COLOR_GREEN, COLOR_BLACK)

void log_string(u8 level, const char* string);
void log_string_raw(u8 level, const char* string);

void log_u4(u8 level, u8 number);
void log_u8(u8 level, u8 number);
void log_u16(u8 level, u16 number);
void log_u32(u8 level, u32 number);
void log_u64(u8 level, u64 number);