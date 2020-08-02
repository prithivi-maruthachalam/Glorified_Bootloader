#include "mem.h"
#include "../cpu/dtypes.h"

void mem_copy(char *from, char *to, int number){
    int i;
    for(i=0;i<number;i++){
        *(to+i) = *(from+i);
    }
}
/*
void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}*/

