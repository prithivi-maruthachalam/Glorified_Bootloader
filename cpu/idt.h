//header for setting up idt
#ifndef IDT_H
#define IDT_H

#include "dtypes.h"

#define KERNEL_CS 0x08 //the address of te code segment register

//struct that defines each interrupt gate(handler)
//note a gate is just an entity that specifies an handler
typedef struct{
    u16 low_offset; //low 16 bits of handler function
    u16 sel; //segment  selector
    u8 always0;
    u8 flags; /*7: Interrupt present,
                6-5 Privilege level 0=kernel,3=user,
                4 0 for interrupt gate
                3-0 1110 for dec 14 - 32 bit interrupt gate*/
    u16 high_offset; //high 16 bites of handlers
} __attribute__((packed)) idt_gate_type;

//a pointer to the id-table - the array of handlers
typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_type;

#define IDT_ENTRIES 256 //for each interrupt
idt_gate_type idt[IDT_ENTRIES];
idt_register_type idt_reg; //this is will have to be ulitimately loaded


//in idt.c
void set_idt_gate(int n, u32 handler);
void set_idt();

#endif