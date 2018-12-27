#pragma once
#include "types.h"

typedef volatile struct {
    u32 command_list_base_lower;
    u32 command_list_base_upper;
    u32 fis_base_address_lower;
    u32 fis_base_address_upper;
    u32 interrupt_status;
    u32 interrupt_enable;
    u32 command;
    u32 reserved0;
    u32 task_file_data;
    u32 signature;
    u32 sata_status;
    u32 sata_control;
    u32 sata_error;
    u32 sata_active;
    u32 command_issue;
    u32 sata_notification;
    u32 reserved1[11];
    u32 vendor[4];
} ahci_hba_port_t;

typedef volatile struct {
    u32 host_capabilities;
    u32 global_host_control;
    u32 interrupt_status;
    u32 port_implemented;
    u32 version;
    u32 command_completion_coalescing_control;
    u32 command_completion_coalescing_ports;
    u32 enclosure_management_location;
    u32 enclosure_management_control;
    u32 host_capabilities_extended;
    u32 bios_handoff_control;

    u8 reserved[0x74];
    u8 vendor[0xE0];
    ahci_hba_port_t ports[32];

} ahci_hba_memory_t;

void ahci_probe_ports(ahci_hba_memory_t *ahci_mmio);
void ahci_init();