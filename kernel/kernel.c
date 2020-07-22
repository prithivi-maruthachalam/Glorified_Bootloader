#include "../drivers/screen.h"
#include "utils.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main(){
    kclear_screen();
    kprint("Entered kernel main\n");
    isr_install(); //to set up the interrupt descriptor table and the handlers
    kprint("ISR installed\n");
    //call interrupts to test
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}