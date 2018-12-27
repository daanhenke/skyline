#pragma once

#include "types.h"

u32 pci_read32(u32 bus, u32 device, u32 function, u32 offset);

void pci_log();