project('microkernel', 'cpp', default_options: [
    'cpp_std=c++20'
])

nasm = find_program('nasm')
nasm_gen = generator(nasm, output: '@BASENAME@.obj', arguments: [ '-f', 'win64', '@INPUT@', '-o', '@OUTPUT@' ])

asm_objects = nasm_gen.process([
    '../shared/arch/x86_64/asm/wrappers.S'
])

executable('micro.efi', [
    '../shared/common/string.cc',

    '../shared/efi/global.cc',
    '../shared/efi/memory.cc',

    'kmain.cc',

    'arch/x86_64/cpu.cc',

    'entry/uefi/main.cc',
    'entry/uefi/logging.cc',
    'entry/uefi/panic.cc',
    asm_objects
], link_args: [
    '-Wl,-subsystem:efi_application'
], include_directories: [
    include_directories('../shared')
])
