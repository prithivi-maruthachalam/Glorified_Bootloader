#include "../drivers/screen.h"

void main(){
    kclear_screen();
    char x[] = "fgfdgf\n";
    char y[] = "ioioioi";
    kprint(x);
    kprint(y);
}