#include "utils.h"

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

    str[i] = '\0';
/*
    //reverse
    char temp;
    int j;
    for(j=0;j<i;j++,i--){
        temp = str[j];
        str[j] = str[i];
        str[i] = str[j];
    }

    str[j] = '\0';
*/
}