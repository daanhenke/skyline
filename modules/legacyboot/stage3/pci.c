#include "pci.h"
#include "types.h"
#include "log.h"
#include "devices.h"
#include "instructions.h"

u32 pci_read32(u32 bus, u32 device, u32 function, u32 offset) {
	u32 address = (1u << 31) | (bus << 16) | (device << 11) | (function << 8) | offset;
	outd(PCI_CONFIG_ADDRESS, address);
	return ind(PCI_CONFIG_DATA);
}

u32 pci_read_deviceid(u32 bus, u32 device, u32 function) {
	return (pci_read32(bus, device, function, 0x00) >> 16) & 0xFFFF;
}

u32 pci_read_vendor(u32 bus, u32 device, u32 function) {
	return pci_read32(bus, device, function, 0x00) & 0xFFFF;
}

u32 pci_read_class(u32 bus, u32 device, u32 function) {
	return pci_read32(bus, device, function, 0x08) >> 24;
}

u32 pci_read_subclass(u32 bus, u32 device, u32 function) {
	return (pci_read32(bus, device, function, 0x08) >> 16) & 0xFF;
}

u32 pci_read_header_type(u32 bus, u32 device, u32 function) {
	return pci_read32(bus, device, function, 0x0c) & 0xFF;
}

u32 pci_read_bar(u32 bus, u32 device, u32 function, u8 bar_index) {
	return pci_read32(bus, device, function, (0x10 + sizeof(u32) * bar_index));
}

bool pci_has_function(u32 bus, u32 device, u32 function) {
	u32 vendor = pci_read_vendor(bus, device, function);
	
	if (vendor == 0xFFFF) {
		return FALSE;
	}

	return TRUE;
}

#define PCI_BUS_COUNT 8
#define PCI_DEVICES_PER_BUS 32
#define PCI_FUNCTIONS_PER_DEVICE 8
#define PCI_FUNCTION_COUNT (PCI_BUS_COUNT * PCI_DEVICES_PER_BUS * PCI_FUNCTIONS_PER_DEVICE)
static pci_function_t functions[PCI_FUNCTION_COUNT];

pci_function_t pci_probe_function(u32 bus, u32 device, u32 function) {
	u64 function_array_index = 0;
	while (TRUE) {
		if (functions[function_array_index].vendor_id == 0xFFFF) {
			break;
		}
		else {
			function_array_index++;
		}
	}

	functions[function_array_index].bus = bus;
	functions[function_array_index].device = device;
	functions[function_array_index].function = function;

	functions[function_array_index].header_type = pci_read_header_type(bus, device, function);

	functions[function_array_index].device_id = pci_read_deviceid(bus, device, function);
	functions[function_array_index].vendor_id = pci_read_vendor(bus, device, function);

	for (u64 i = 0; i < 6; i++) {
		functions[function_array_index].bar[i] = pci_read_bar(bus, device, function, i);
	}

	return functions[function_array_index];
}

void pci_probe_device(u32 bus, u32 device) {
	bool isValidDevice = pci_has_function(bus, device, 0);
	if (!isValidDevice) {
		return;
	}

	pci_function_t firstFunction = pci_probe_function(bus, device, 0);
	if (firstFunction.header_type & 0x80) {
		for (u64 i = 0; i < 8; i++) {
			pci_probe_function(bus, device, i);
		}
	}
}

void pci_probe_bus(u32 bus) {
	for (u64 i = 0; i < PCI_DEVICES_PER_BUS; i++) {
		pci_probe_device(bus, i);
	}
}

void pci_init() {
	for (u64 i = 0; i < PCI_FUNCTION_COUNT; i++) {
		functions[i].vendor_id = 0xFFFF;
	}

	for (u64 i = 0; i < PCI_BUS_COUNT; i++) {
		pci_probe_bus(i);
		log_string(LOG_STATUS, "scanning a bus...\n");
	}
}