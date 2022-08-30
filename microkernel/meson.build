project('microkernel', 'cpp')

executable('micro.efi', [
    'entry/uefi/main.cc'
], link_args: [
    '-Wl,-subsystem:efi_application'
])
