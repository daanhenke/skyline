#pragma once

#include "types.h"

#define PCI_BUS_COUNT 8
#define PCI_DEVICES_PER_BUS 32
#define PCI_FUNCTIONS_PER_DEVICE 8
#define PCI_FUNCTION_COUNT (PCI_BUS_COUNT * PCI_DEVICES_PER_BUS * PCI_FUNCTIONS_PER_DEVICE)

#define PCI_CLASS_MASS_STORAGE_DEVICE 1

#define PCI_SUBCLASS_SERIAL_ATA 6

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

pci_function_t pci_get_function(u64 index);
pci_function_t pci_probe_function(u32 bus, u32 device, u32 function);
void pci_probe_device(u32 bus, u32 device);
void pci_probe_bus(u32 bus);
void pci_init();