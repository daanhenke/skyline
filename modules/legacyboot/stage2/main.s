bits 16
org 0x9000

[map all build/stage2.map]

stage2_main:
	; do our 16 bit stuff
	call real_main

	; switch to 32 bits & do 32 bit stuff
bits 32
	call protected_main

	; switcch to 64 bits & do 64 bit stuff
bits 64
	call long_main

	; switch back to 16 bits so we can still use some of our stage1 functions
bits 16

%include "include/pointers.s"
%include "stage1/globals.s"

%include "stage1/strings.s"
%include "stage1/screen.s"

%include "stage2/modes/real.s"
%include "stage2/modes/protected.s"
%include "stage2/modes/long.s"

%include "stage2/strings.s"
%include "stage2/pointers.s"
%include "stage2/a20.s"
%include "stage2/long.s"
%include "stage2/sse.s"