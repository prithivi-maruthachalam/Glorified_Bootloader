#include "timer.h"
#include "../drivers/screen.h"
#include "isr.h"
#include "ports.h"
#include "../libc/kstrings.h"

//the variable that the interrupt will update
u32 tick = 0;

static void timer_callback(registers_table regs){
    tick++;

    char tick_ASCII[256];
    int_to_ascii(tick,tick_ASCII);
}

void init_timer(u32 frequency){
    register_interrupt_handler(IRQ0, timer_callback); //IRQ0 is for the Programmable Interrupt Timer

    u32 divisor = 1193180 / frequency; //the divided the default frequency to give the required frequency
    u8 low = (u8)(divisor & 0xFF);
    u8 high = (u8)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36); //command
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}