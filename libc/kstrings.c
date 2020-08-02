#include "kstrings.h"

void int_to_ascii(int num, char *str){
    int i;
    i = 0;
    if(num < 0){
        num = (-num);
    }
    do{
        str[i++] = num%10 + '0';
    } while((num/=10) > 0);

    if(i < 0){
        str[i++] = '-';
    }
    str[i] = '\0';
    
    reverse(str);

}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char string[], char c){
    int len = strlen(string);
    string[len] = c;
    string[len+1] = '\0';
}

void backspace(char string[]){
    int len = strlen(string);
    string[len-1] = '\0';
}


// <0 if stringA < stringB
// >0 is stringA > stringB
// 0 is stringA == stringB
int strcmp(char stringA[], char stringB[]){
    int i;
    for(i=0;stringA[i] == stringB[i];i++){
        if(stringA[i] == '\0') return 0;
    }

    return stringA[i] - stringB[i];
}
