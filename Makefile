.PHONY: microkernel-x86_64-uefi microkernel-x86_64-limine

# Microkernel flavours
microkernel-x86_64-uefi:
	[ -d "./build/x86_64/uefi" ] || mkdir -p "./build/x86_64/uefi"
	meson setup --cross-file ./meson/x86_64-clang-uefi.ini ./microkernel ./build/x86_64/uefi
	meson compile -C ./build/x86_64/uefi

# Packaging
folder-x86_64-uefi: microkernel-x86_64-uefi
	[ -d "./dist/x86_64/uefi/efi/boot" ] || mkdir -p "./dist/x86_64/uefi/efi/boot"
	cp ./build/x86_64/uefi/micro.efi ./dist/x86_64/uefi/efi/boot/bootx64.efi

# Needed for uefi in qemu
build/artifacts/ovmf.bin:
	[ -d "./build/artifacts" ] || mkdir -p "./build/artifacts"
	curl https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd --output $@

# Qemu presets
qemu-x86_64-uefi: folder-x86_64-uefi ./build/artifacts/ovmf.bin
	qemu-system-x86_64 \
		-bios ./build/artifacts/ovmf.bin \
		-drive file=fat:rw:./dist/x86_64/uefi,format=raw
