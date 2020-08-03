#include "../cpu/ports.h"
#include "screen.h"
#include "../libc/mem.h"

//Declaration for private functions
int get_cursor_offset(); //gets the current position of the cursor in video memory
void set_cursor_offset(int offset); //moves cursor to a certain position in video memory

int get_offset(int row, int col); //uses coords to return position in video memory
//uses video memory position to return row and col
int get_offset_row(int offset); 
int get_offset_col(int offset);

int print_char(char c, int row, int col, char attr); //attr describes the color

int scroll_handling(int offset); //takes care of all vertical scrolling

/*public functions declared in screen.h*/
void kprint_at(char *text, int row, int col){
    int offset;
    if(row >= 0 && col >=0){
        offset = get_offset(row,col);
    } else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    
    int i = 0;
    while(text[i]){
        offset = print_char(text[i++],row,col,WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *text){
    kprint_at(text,-1,-1); //neg 1 to set to current cursor position
}

void kclear_screen(){
    int vidCellsSize = MAX_COLS * MAX_ROWS;
    int i;
    unsigned char *vid_mem = (unsigned char*)VIDEO_ADDRESS;
    for(i=0;i<vidCellsSize;i++){
        vid_mem[i*2] = ' ';
        vid_mem[i*2 + 1] = WHITE_ON_BLACK;
    }

    set_cursor_offset(get_offset(0,0));
}

void kprint_backspace(){
    int last_offset = get_cursor_offset() - 2;
    int row = get_offset_row(last_offset);
    int col = get_offset_col(last_offset);
    print_char(0x08,row,col, WHITE_ON_BLACK);
}

/*private functions*/
int print_char(char c, int row, int col, char attr){
    unsigned char *vid_mem = (unsigned char*) VIDEO_ADDRESS;
    if(!attr){
        attr = WHITE_ON_BLACK;
    }

    if(row >= MAX_ROWS || col >= MAX_COLS){
        //let's say this is an error for now
        vid_mem[2*MAX_COLS*MAX_ROWS - 2] = 'E';
        vid_mem[2*MAX_ROWS*MAX_COLS - 1] = RED_ON_WHITE;

        return get_offset(row,col); //maybe exit with 1?
    }

    int offset;
    if(row >= 0 && col >= 0){
        offset = get_offset(row,col);
    } else {
        offset = get_cursor_offset();
    }

    //special case handling
    if(c == '\n'){
        row = get_offset_row(offset);
        offset = get_offset(row+1,0);
    } else if(c == 0x08){
        vid_mem[offset] = ' ';
        vid_mem[offset+1] = attr;
    }else {
        vid_mem[offset] = c;
        vid_mem[offset+1] = attr;
        offset += 2;
    }
    //offset is incremented before proceeding, so this is the offset for the next operation
    offset = scroll_handling(offset);

    set_cursor_offset(offset);
    return offset;
}

int scroll_handling(int offset){
    //check if offset is greater than screen size
    if(offset >= MAX_COLS * MAX_ROWS * 2){
        int i;
        for (i = 0; i < MAX_ROWS; i++){
            mem_copy((char *)(VIDEO_ADDRESS + get_offset(i,0)), 
                (char *)(VIDEO_ADDRESS + get_offset(i-1,0)), MAX_COLS*2);
        }

        //empty last line
        char *last = (char *)(VIDEO_ADDRESS + get_offset(MAX_ROWS-1,0));
        for(i = 0;i < MAX_COLS;i++){
            last[i] = ' ';
        }
        
        offset -= 2 * MAX_COLS;
    }

    return offset;
}

int get_cursor_offset(){
    port_byte_out(SCREEN_REG_CTRL,14);
    int offset = port_byte_in(SCREEN_REG_DATA) << 8; //high byte
    port_byte_out(SCREEN_REG_CTRL,15);
    offset += port_byte_in(SCREEN_REG_DATA); //add low byte
    return offset * 2; //each char is 2 bytes in memory
}

void set_cursor_offset(int offset){
    offset /= 2;
    port_byte_out(SCREEN_REG_CTRL,14);
    port_byte_out(SCREEN_REG_DATA,(unsigned char)(offset >> 8)); //write high byte
    port_byte_out(SCREEN_REG_CTRL,15);
    port_byte_out(SCREEN_REG_DATA,(unsigned char)(offset & 0xff)); //00000000 11111111 -> 0xff
}

int get_offset(int row, int col){
    return(2 * ((row * MAX_COLS) + col));
}
int get_offset_row(int offset){
    return(offset/(2 * MAX_COLS));
}
int get_offset_col(int offset){
    return(offset - (2 * get_offset_row(offset) * MAX_COLS))/2;
}