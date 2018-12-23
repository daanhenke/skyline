strings_stage2.start_message db "starting...", 0x0D, 0x0A, 0x00
strings_stage2.panic db "panicking! halting cpu", 0x0D, 0x0A, 0x00

strings_stage2.couldnt_enable_a20 db "could not enable A20 line", 0x0D, 0x0A, 0x00
strings_stage2.enabled_a20 db "enabled A20 line", 0x0D, 0x0A, 0x00

strings_stage2.long_success db "cpu supports long mode", 0x0D, 0x0A, 0x00
strings_stage2.long_no_cpuid db "cpu does not support cpuid instruction", 0x0D, 0x0A, 0x00
strings_stage2.long_no_info db "cpu does not support processor info function", 0x0D, 0x0A, 0x00
strings_stage2.long_no_long db "cpu does not support support 64 bit mode", 0x0D, 0x0A, 0x00

strings_stage2.sse_success db "sse enabled", 0x0D, 0x0A, 0x00
strings_stage2.sse_no_fx db "cpu does not support FXSAVE/FXRSTOR", 0x0D, 0x0A, 0x00
strings_stage2.sse_no_sse1 db "cpu does not support SSE1", 0x0D, 0x0A, 0x00
strings_stage2.sse_no_sse2 db "cpu does not support SSE2", 0x0D, 0x0A, 0x00