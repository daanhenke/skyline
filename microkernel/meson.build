project('microkernel', 'cpp')

executable('micro.efi', [
    '../shared/common/string.cc',
    '../shared/efi/global.cc',
    '../shared/efi/memory.cc',
    'kmain.cc',
    'entry/uefi/main.cc',
    'entry/uefi/logging.cc',
], link_args: [
    '-Wl,-subsystem:efi_application'
], include_directories: [
    include_directories('../shared')
])
