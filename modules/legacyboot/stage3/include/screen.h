#pragma once

#define VIDEO_MEMORY 0x000B8000

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_PURPLE 5
#define COLOR_BROWN 6
#define COLOR_GRAY 7
#define COLOR_DARKGRAY 8
#define COLOR_LIGHTBLUE 9
#define COLOR_LIGHTGREEN 10
#define COLOR_LIGHTCYAN 11
#define COLOR_LIGHTRED 12
#define COLOR_LIGHTPURPLE 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

#define COLOR(fg, bg) (fg | (bg << 4))

void screen_set_char_attr(int x, int y, char character, char attributes);
void screen_print_string_attr(const char* string, char attributes);
void screen_clear();
