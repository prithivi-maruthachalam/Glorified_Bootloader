#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

void main(){
    kclear_screen();
    isr_install(); //to set up the interrupt descriptor table and the handlers
    kprint("Installed interrupts\n");

    asm volatile("sti");
    //init_timer(50);
    init_keyboard();
}