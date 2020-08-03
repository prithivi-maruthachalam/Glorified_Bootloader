#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/kstrings.h"

void main(){
    kclear_screen();
    isr_install(); //to set up the interrupt descriptor table and the handlers
    kprint("Installed software interrupts\n");

    irq_install();
    kprint("Installed hardware interrupts\n");
}

void user_input(char *input){
    if(strcmp(input,"END") == 0){
        kprint("Halting CPU. So long bitches!");
        asm volatile("hlt");
    }
    kprint("Input: ");
    kprint(input);
    kprint("\n>> ");
}