project('microkernel', 'cpp')

executable('micro.efi', [
    'entry/uefi/main.cc'
], link_args: [
    '-Wl,-subsystem:efi_application'
], include_directories: include_directories('../shared'))
