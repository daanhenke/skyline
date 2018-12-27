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

u32 pci_read_hdr(u32 bus, u32 device, u32 function) {
	return pci_read32(bus, device, function, 0x0c) & 0xFF;
}

u32 pci_read_bar(u32 bus, u32 device, u32 function, u8 bar_index) {
	return pci_read32(bus, device, function, (0x10 + sizeof(u32) * bar_index));
}

u8 pci_log_function(u32 bus, u32 device, u32 function) {
	u32 vendor = pci_read_vendor(bus, device, function);
	if (vendor == 0xFFFF) return FALSE;

	u32 deviceid = pci_read_deviceid(bus, device, function);

	u32 class = pci_read_class(bus, device, function);
	u32 subclass = pci_read_subclass(bus, device, function);

	u32 bar0 = pci_read_bar(bus, device, function, 0);
	u32 bar1 = pci_read_bar(bus, device, function, 1);
	u32 bar2 = pci_read_bar(bus, device, function, 2);
	u32 bar3 = pci_read_bar(bus, device, function, 3);
	u32 bar4 = pci_read_bar(bus, device, function, 4);
	u32 bar5 = pci_read_bar(bus, device, function, 5);

	log_string_raw(LOG_STATUS, "--device start--\n");

	log_string_raw(LOG_WARNING, "deviceid: ");
	log_u16(LOG_WARNING, deviceid);
	log_string_raw(LOG_WARNING, "\n");

	log_string_raw(LOG_WARNING, "vendor: ");
	log_u16(LOG_WARNING, vendor);
	log_string_raw(LOG_WARNING, "\n");

	log_string_raw(LOG_WARNING, "class / subclass:");
	log_u16(LOG_WARNING, class);
	log_string_raw(LOG_WARNING, " : ");
	log_u16(LOG_WARNING, subclass);
	log_string_raw(LOG_WARNING, "\n");

	log_string_raw(LOG_WARNING, "bars:\n");
	log_u32(LOG_WARNING, bar0);
	log_string_raw(LOG_WARNING, "\n");
	log_u32(LOG_WARNING, bar1);
	log_string_raw(LOG_WARNING, "\n");
	log_u32(LOG_WARNING, bar2);
	log_string_raw(LOG_WARNING, "\n");
	log_u32(LOG_WARNING, bar3);
	log_string_raw(LOG_WARNING, "\n");
	log_u32(LOG_WARNING, bar4);
	log_string_raw(LOG_WARNING, "\n");
	log_u32(LOG_WARNING, bar5);
	log_string_raw(LOG_WARNING, "\n");

	log_string_raw(LOG_STATUS, "--device end--\n");

	return TRUE;
}

void pci_log_device(u32 bus, u32 device) {
	u32 first_device = pci_log_function(bus, device, 0);
	if (!first_device) {
		return;
	}

	u32 hdr = pci_read_hdr(bus, device, 0);
	if (hdr & 0x80) {
		for (u32 function = 1; function < 8; function++) {
			pci_log_function(bus, device, function);
		}
	}
}

void pci_log_bus(u32 bus) {
	for (u32 device = 0; device < 32; device++) {
		pci_log_device(bus, device);
	}
}

void pci_log() {
	log_string(LOG_STATUS, "reading pci bus 0\n");
	pci_log_bus(0);

	u32 hdr = pci_read_hdr(0, 0, 0);
	if (hdr & 0x80) {
		for (u32 bus = 1; bus < 8; bus++) {
			u32 vendor = pci_read_vendor(0, 0, bus);
			if (vendor != 0xFFFF) {
				log_string(LOG_STATUS, "reading pci bus ");
				log_u8(LOG_STATUS, bus);
				log_string_raw(LOG_STATUS, "\n");
				pci_log_bus(bus);
			}
		}
	}
}