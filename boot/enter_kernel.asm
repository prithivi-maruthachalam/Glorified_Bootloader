;this needs to be linked with the kernel.c file
[bits 32]


[extern main] ;the function in the kernel that's to be called
call main ;call the C function


jmp $