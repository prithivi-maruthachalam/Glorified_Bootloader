#ifndef UTILS_H
#define UTILS_H
#include "../cpu/dtypes.h"
void mem_copy(char *from, char *to, int number);
void int_to_ascii(int num, char *str);
void memory_set(u8 *dest, u8 val, u32 len);
#endif