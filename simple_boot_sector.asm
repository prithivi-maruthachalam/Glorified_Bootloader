[org 0x7c00] ;offeset from the bootloader's current position in memory

;main greeting
mov bx, GREETING_STRING
call print_string

call print_newline
call print_newline

;setting up stack at a far away point from current point
mov bp, 0x8000
mov sp,bp ;moving start to base

mov bx, 0x9000 ;that's the location we want to read to with an es offset, which is set by default
mov dh, 2 ;number of sectors to read - parameter for disk_load
call disk_load

mov dx, [0x9000] ;retrieve the frist word and put it in the parameter for print_hex
call print_hex_data

call print_newline

mov dx, [0x9000 + 512] ;first word loaded from second sector
call print_hex_data


;putting in an infinite loop for persistence
jmp $

;inlcuding files
%include "printing.asm"
%include "disk_access.asm"

;data
GREETING_STRING:
    db 'Starting boot process in 16-bit real mode',0



;padding with 510 - size of code so far - zeroes and magic number to ID as bootsector code
times 510 - ($-$$) db 0
dw 0xaa55


;putting in false data to be read
times 256 dw 0xdada
times 256 dw 0xfaa3