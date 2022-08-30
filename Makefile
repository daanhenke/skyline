.PHONY: microkernel-x86_64-uefi microkernel-x86_64-limine

microkernel-x86_64-uefi:
	[ -d "./build/x86_64/uefi" ] || mkdir -p "./build/x86_64/uefi"
	meson setup --cross-file ./meson/x86_64-clang-uefi.ini ./microkernel ./build/x86_64/uefi
	meson compile -C ./build/x86_64/uefi
