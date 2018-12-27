#include "types.h"
#include "screen.h"
#include "std/memset.h"

static int current_x = 0;
static int current_y = 0;

void screen_set_char_attr(int x, int y, char character, char attributes)
{
	volatile char *video = (volatile char *) VIDEO_MEMORY;
	unsigned int index = (y * SCREEN_WIDTH + x) * 2;

	video[index] = character;
	video[index + 1] = attributes;
}

void screen_print_string_attr(const char* string, char attributes) {
	unsigned int index = 0;
	char current_char = '1';

	while (TRUE) {
		current_char = string[index];
		index++;

		// handle control characters
		if (current_char == '\0') {
			break;
		}
		if (current_char == '\n') {
			current_y++;
			current_x = 0;
		}
		if (current_char == '\r') {
			current_x = 0;
		}
		if (current_char == ' ') {
			current_x++;
		}

		// fix our current position if it's out of bounds
		if (current_x >= SCREEN_WIDTH) {
			current_x = 0;
			current_y++;
		}
		if (current_y >= SCREEN_HEIGHT) {
			// TODO: make the screen scroll instead of overwriting text
			current_y = 0;
		}

		// if our character is printable print it
		if (current_char >= '!' && current_char <= '~') {
			screen_set_char_attr(current_x, current_y, current_char, attributes);
			current_x++;
		}
	}
}

void screen_clear() {
	memset(VIDEO_MEMORY, 0, (SCREEN_WIDTH * SCREEN_HEIGHT) * 2);
}