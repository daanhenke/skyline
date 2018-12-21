LEGACY_IMG=skyline-legacy-x64.img

all: legacy

run: legacy
	@qemu-system-i386 -hda build/$(LEGACY_IMG)

legacy: build_directory legacyboot
	@echo Building legacy image
	@dd if=/dev/zero of=build/$(LEGACY_IMG) bs=512 count=1024
	@sfdisk build/$(LEGACY_IMG) < legacy.sfdisk
	@dd if=build/legacyboot/stage1.bin of=build/$(LEGACY_IMG) bs=1 skip=0 count=446 conv=notrunc
	@dd if=build/legacyboot/stage2.bin of=build/$(LEGACY_IMG) bs=512 seek=1 count=9 conv=notrunc

build_directory:
	@echo Making build directory
	@mkdir -p build

legacyboot: build_directory
	@echo Building legacyboot
	@$(MAKE) --no-print-directory -C modules/legacyboot
	@echo Copying artifacs
	@mkdir -p build/legacyboot
	@cp -r modules/legacyboot/build/* build/legacyboot