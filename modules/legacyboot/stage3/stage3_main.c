#include "screen.h"
#include "log.h"
#include "pci.h"

void stage3_main()
{
	screen_clear();
	log_string(LOG_STATUS, "currently in stage3\n");
	pci_log();
}