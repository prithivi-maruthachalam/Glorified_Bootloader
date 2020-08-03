unsigned char port_byte_in(unsigned short port){
    unsigned char result;
    // Reads a byte from port
    //Reads the value from al into result when done
    //edx is loaded with port
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data){
    //Loads data into a port
    //Reads the data into eax
    //Loads the port into edx
    __asm__("out %%al, %%dx" :: "a"(data),"d"(port));
}

unsigned short port_word_in(unsigned short port){
    //Reads a Word from the port
    //ax is used because word is longer than a byte
    unsigned short result;
    __asm__("in %%dx, %%ax": "=a"(result) : "d"(port));

    return result;
}

void port_word_out(unsigned short port, unsigned short data){
    __asm__("out %%ax, %%dx" :: "a"(data),"d"(port));   
}