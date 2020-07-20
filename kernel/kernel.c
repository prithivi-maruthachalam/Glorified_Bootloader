#include "../drivers/screen.h"

void main(){
    kclear_screen();
    char x[] = "fgfdgf\n";
    kprint(x);
    char y[] = "What?atatatatatata";
    kprint(y);
}