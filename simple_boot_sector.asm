;putting in an infinite loop
loop:
    jmp loop

;padding wit 510 - size of code so far - zeroes
times 510 - ($-$$) db 0

;number to indicate that this is a boot sector file
dw 0xaa55