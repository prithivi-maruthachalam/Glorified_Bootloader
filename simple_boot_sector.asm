;setup tty mode 
mov ah, 0x0e ;put int 10 into the high bit of the ax register

mov al, 'H' ;Move the character to be printed into the lowest bit of the ax register
int 0x10 ;call the interrupt to print on the screen
mov al, 'E'
int 0x10

;putting in an infinite loop for persistence
jmp $

;padding with 510 - size of code so far - zeroes and magic number to ID as bootsector code
times 510 - ($-$$) db 0
dw 0xaa55