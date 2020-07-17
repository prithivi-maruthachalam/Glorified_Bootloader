void dummy(){
    /*
        
    */
}

void main(){
    char* VIDEO_MEMORY = (char *)0xb8000;
    *VIDEO_MEMORY = 'X';
}