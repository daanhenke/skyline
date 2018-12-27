#include "serial.h"
#include "types.h"
#include "devices.h"
#include "instructions.h"

void serial_init(u16 port) {
    outb(port + 1, 0x00);
    outb(port + 3, 0x80);
    outb(port + 0, 0x03);
    outb(port + 1, 0x00);
    outb(port + 3, 0x03);
    outb(port + 2, 0xC7);
    outb(port + 4, 0x0B);
}

bool serial_can_read(u16 port) {
    return inb(port + 5) & 1;
}

bool serial_can_write(u16 port) {
    return inb(port + 5) & 0x20;
}

u8 serial_read(u16 port) {
    while(serial_can_read(port) == FALSE);
    return inb(port);
}

void serial_write(u16 port, u8 data) {
    while(serial_can_write(port) == FALSE);
    outb(port, data);
}