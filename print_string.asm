print_string:
    pusha

    ;while(string[i] != 0){print string[i]; i++}
    start:
        mov al, [bx]; 'bx is the address of the first position of the string'
        cmp al, 0 ;check if string[i] is equal to 0
        je done ;jump to end if they're equal

        mov ah, 0x0e ;set to TTY mode
        int 0x10 ;call the interrupt to print

        add bx, 1 ;adding one byte to the address pointer
        jmp start
    
    done:
        popa
        ret


print_newline:
    pusha

    mov ah, 0x0e ;set to TTY mode
    mov al, 0x0a ;set to newline character
    int 0x10 ;cal the interrupt to print
    mov al, 0x0d ;set to carriage return
    int 0x10

    popa
    ret