AS=nasm

all: stage1 stage2

build_directory:
	@echo Making build directory
	@mkdir -p build

stage1: build_directory
	@$(AS) stage1/main.s -I stage1 -I include -f bin -o build/stage1.bin

stage2: build_directory
	@$(AS) stage2/main.s -I stage1 -I include -f bin -o build/stage2.bin