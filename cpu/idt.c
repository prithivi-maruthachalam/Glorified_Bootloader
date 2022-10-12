//code for setting up idt

#include "idt.h"

idt_gate_type idt[IDT_ENTRIES];
idt_register_type idt_reg;

void set_idt_gate(int n, u32 handler)
{
    idt[n].low_offset = (u16)handler & 0x0000FFFF;
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = (u16)(handler >> 16) & 0x0000FFFF;
}

void set_idt()
{
    idt_reg.base = (u32)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_type) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidt (%0)"
                         :
                         : "r"(&idt_reg));
}
