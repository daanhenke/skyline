#include "screen.h"
#include "log.h"
#include "pci.h"
#include "devices.h"
#include "serial.h"
#include "ahci.h"
#include "page.h"

void stage3_main()
{
    screen_clear();
    log_string(LOG_STATUS, "currently in stage3\n");

    serial_init(COM1);
    log_string(LOG_STATUS, "enabled serial on COM1\n");

    pci_init();
    ahci_init();
    log_string(LOG_SUCCESS, "still alive!\n");
}
