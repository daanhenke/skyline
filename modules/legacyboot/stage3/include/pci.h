#pragma once

#include "types.h"

typedef struct {
	u32 bus;
	u32 device;
	u32 function;

	u32 header_type;

	u16 device_id;
	u16 vendor_id;

	u16 class;
	u16 subclass;

	u32 bar[6];
} pci_function_t;

u32 pci_read32(u32 bus, u32 device, u32 function, u32 offset);

void pci_init();