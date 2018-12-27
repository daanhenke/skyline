#include "ahci.h"
#include "pci.h"
#include "log.h"
#include "types.h"

void ahci_probe_ports(ahci_hba_memory_t *ahci_mmio) {
	log_u32(LOG_STATUS, ahci_mmio);
	log_u32(LOG_STATUS, ahci_mmio->port_implemented);
}

void ahci_init() {
	for (u64 i = 0; i < PCI_FUNCTION_COUNT; i++) {
		pci_function_t func = pci_get_function(i);

		if (func.vendor_id == 0xFFFF) {
			break;
		}

		if (func.class == PCI_CLASS_MASS_STORAGE_DEVICE && func.subclass == PCI_SUBCLASS_SERIAL_ATA) {
			ahci_probe_ports((ahci_hba_memory_t *) func.bar[5]);
		}
	}
}