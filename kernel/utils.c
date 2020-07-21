#include "utils.h"
#include <stdio.h>

void mem_copy(char *from, char *to, int number){
    int i;
    for(i=0;i<number;i++){
        *(to+i) = *(from+i);
    }
}

void int_to_ascii(int num, char str[]){
    int i;
    i = 0;
    do{
        str[i++] = num%10 + '0';
    } while((num/=10) > 0);


    //reverse
    int j=0;
    i--;
    do{
        char temp;
        temp = str[i];
        str[i--] = str[j];
        str[j++] = temp;
    } while((i-j) > 1);
    str[++j] = '\0';

}