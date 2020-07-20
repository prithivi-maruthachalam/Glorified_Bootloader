#include "../drivers/screen.h"
#include "utils.h"

void main(){
    kclear_screen();
    int i=0;
    for(i=0;i<25;i++){
        char str[255];
        int_to_ascii(i,str);
        kprint_at(str,i,0);
    }

    kprint("fyhrftg\n");
    kprint("dgfdg\n");
    kprint("fdgdfghfdh");
}