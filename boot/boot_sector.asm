[org 0x7c00] 
;executed by defualt from the above adderss so this is used as offset for the folloing code
;calling this as a function is what gives control to the second stage bootloader(which is the kernel for now)

;pointers to kernel and second stages addresses
;should be changed to an actual second stage which then calls
 the kernel
SECOND_STAGE_BOOTLOADER_OFFSET equ 0x1000 ;position the kernel exists at 


;initialisation for the first stage bootloader ----------------------------------
mov [BOOT_DRIVE],dl ;boot drive is set in dl by the BIOS

;setting up stack
mov bp,0x9000 
mov sp, bp

;main greeting
mov bx, GREETING_STRING_REAL_MODE
call print_string
call print_newline


call load_kernel;to be changed to calling second stage kernel
call switch_to_pm

;putting in an infinite loop for persistence
jmp $ ;hopefully, never executed

;---------------------------------------------------------------------------------

;inlcuding files
%include "boot/printing.asm"
%include "boot/32bit-gdt.asm"
%include "boot/32bit-printing.asm"
%include "boot/switching_to_32bit.asm"
%include "boot/disk_access.asm"

[bits 16]
load_kernel: ;the function to perform 16 bit operations to load kernel code from disk
    mov bx, MSG_LOAD_KERNEL
    call print_string
    call print_newline

    mov bx, SECOND_STAGE_BOOTLOADER_OFFSET ;es:bx is where the data is loaded into
    mov dh, 20 ;number of sectors to read
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

    ;at this point the dummy function should've been called and returned becuase of the order


[bits 32]
BEGIN_PM:
    mov ebx, MSG_PM_ENTRY
    call pm_print_string
    
    call SECOND_STAGE_BOOTLOADER_OFFSET ;gives control to the main function of the kernel
    jmp $


;data
BOOT_DRIVE db 0 ;dl is a register and could be overwritten, so we store it here for use - putting in a stack and retrieveing is not necessary
GREETING_STRING_REAL_MODE db 'Starting boot process in 16-bit real mode',0
MSG_PM_ENTRY db 'Loaded 32-bit protected mode',0
MSG_LOAD_KERNEL db 'Loading kernel into memory from disk',0


;padding with 510 - size of code so far - zeroes and magic number to ID as bootsector code
times 510 - ($-$$) db 0
dw 0xaa55