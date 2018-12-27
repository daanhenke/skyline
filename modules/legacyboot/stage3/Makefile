AS=nasm
CC=x86_64-elf-gcc
OBJCOPY=objcopy

ASFLAGS := -f elf64
CCFLAGS := -std=gnu11 -Qn -g -m64 -mno-red-zone -mno-mmx -mfpmath=sse \
			-ffreestanding -fno-asynchronous-unwind-tables -Wall -Wextra -Wpedantic
LDFLAGS := -g -nostdlib -m64 -mno-red-zone -ffreestanding -lgcc -z \
			max-page-size=0x1000

STAGE3_OBJECTS = stage3_main.c.o screen.c.o log.c.o pci.c.o serial.c.o std/memset.c.o asm/start.s.o asm/instructions.s.o
STAGE3_INCLUDES = -Iinclude

stage3: $(STAGE3_OBJECTS)
	@$(CC) $(LDFLAGS) -T stage3.ld -o ../build/stage3.o $(STAGE3_OBJECTS)
	@$(OBJCOPY) -O binary -j .text ../build/stage3.o ../build/stage3.bin

%.c.o: %.c
	@$(CC) $(CCFLAGS) $(STAGE3_INCLUDES) -c $< -o $@

%.s.o: %.s
	@$(AS) $(ASFLAGS) $< -o $@
