[org 0x7c00]

mov bx, HELLO_STRING
call print_string

call print_newline

mov bx, GOODBYE_STRING
call print_string

call print_newline

mov dx, 0x123A
call print_hex_data


;putting in an infinite loop for persistence
jmp $

;inlcuding files
%include "printing.asm"

;data
HELLO_STRING:
    db 'Hello World',0
GOODBYE_STRING:
    db 'Goodbye World',0


;padding with 510 - size of code so far - zeroes and magic number to ID as bootsector code
times 510 - ($-$$) db 0
dw 0xaa55