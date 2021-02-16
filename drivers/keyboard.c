#include "keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "screen.h"
#include "../libc/kstrings.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define SC_MAX 57
//scancodes
#define BACKSPACE 0x0E
#define ENTER 0x1C

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static char key_buffer[256];

static void keyboard_callback(registers_table regs){
    //PIC leaves the scancode here - PIC think PIC do
    u8 scancode = port_byte_in(0x60);

    if(scancode > SC_MAX){
        return;
    }
    if(scancode == BACKSPACE){
        backspace(key_buffer);
        kprint_backspace();
    } else if(scancode == ENTER){
        kprint("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        //can't just append because letter needs to be reused
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }

    UNUSED(regs);
}

void init_keyboard(){
    register_interrupt_handler(IRQ1, keyboard_callback);
}
