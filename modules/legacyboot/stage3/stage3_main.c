#include "screen.h"
#include "log.h"
#include "pci.h"
#include "devices.h"

void stage3_main()
{
	screen_clear();
    log_string(LOG_STATUS, "currently in stage3\n");
    serial_write(COM1, 'a');
    for (u64 i = 0; i < 26; i++) {
        log_string(LOG_STATUS, "line");
        log_u8(LOG_STATUS, i);
        log_string_raw(LOG_STATUS, "\n");
        serial_write(COM1, 'y');
    }
	screen_scroll_up();
    //pci_log();
}