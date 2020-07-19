#include "../drivers/screen.h"

void main(){
    kclear_screen();
    char x[] = "fgfdgdfdf";
    kprint_at(x, 1, 6);
}