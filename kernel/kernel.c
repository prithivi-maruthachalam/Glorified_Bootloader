#include "../drivers/ports.h"

void dummy(){
    /*
        
    */
}

void main(){
    port_byte_out(0x3d4,14);
    int position = port_byte_in(0x3d5);
    position = position << 8;

    port_byte_out(0x3d4,15);

    position += port_byte_in(0x3d5);
    int offset = position * 2;

    char *vga = (char *)0xb8000;
    vga[offset] = 'X';
    vga[offset + 1] = 0x0f;
}