[org 0x7c00] ;offeset from the bootloader's current position in memory

;setting up stack
mov bp,0x9000 
mov sp, bp

;main greeting
mov bx, GREETING_STRING
call print_string

call switch_to_pm

;putting in an infinite loop for persistence
jmp $ ;hopefully, never executed

;inlcuding files
%include "printing.asm"
%include "32bit-gdt.asm"
%include "32bit-printing.asm"
%include "switching_to_32bit.asm"



[bits 32]
BEGIN_PM:
    mov ebx, MSG_PM_ENTRY
    call pm_print_string
    jmp $


;data
GREETING_STRING db 'Starting boot process in 16-bit real mode',0
MSG_PM_ENTRY db 'Loaded 32-bit protected mode',0


;padding with 510 - size of code so far - zeroes and magic number to ID as bootsector code
times 510 - ($-$$) db 0
dw 0xaa55