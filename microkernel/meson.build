project('microkernel', 'cpp', default_options: [
    'cpp_std=c++20'
])

executable('micro.efi', [
    '../shared/common/string.cc',
    '../shared/efi/global.cc',
    '../shared/efi/memory.cc',
    'kmain.cc',
    'entry/uefi/main.cc',
    'entry/uefi/logging.cc',
    'entry/uefi/panic.cc',
], link_args: [
    '-Wl,-subsystem:efi_application'
], include_directories: [
    include_directories('../shared')
])
