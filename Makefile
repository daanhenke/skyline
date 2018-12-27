LEGACY_IMG=skyline-legacy-x64.img

all: legacy

run: legacy
	@qemu-system-x86_64 -hda build/$(LEGACY_IMG) -d in_asm,int -D /tmp/qemu -no-shutdown -no-reboot -monitor telnet:127.0.0.1:1234,server,nowait

legacy: build_directory legacyboot
	@echo Building legacy image
	@dd if=/dev/zero of=build/$(LEGACY_IMG) bs=512 count=1024
	@sfdisk build/$(LEGACY_IMG) < legacy.sfdisk
	@dd if=build/legacyboot/stage1.bin of=build/$(LEGACY_IMG) bs=1 skip=0 count=446 conv=notrunc
	@dd if=build/legacyboot/stage2.bin of=build/$(LEGACY_IMG) bs=512 seek=1 count=4 conv=notrunc
	@dd if=build/legacyboot/stage3.bin of=build/$(LEGACY_IMG) bs=512 seek=5 count=20 conv=notrunc

build_directory:
	@echo Making build directory
	@mkdir -p build

legacyboot: build_directory
	@echo Building legacyboot
	@$(MAKE) --no-print-directory -C modules/legacyboot
	@echo Copying artifacs
	@mkdir -p build/legacyboot
	@cp -r modules/legacyboot/build/* build/legacyboot
