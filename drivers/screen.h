#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

//foreground lowest 4 bits 
//background highest 3 bits
//additional bit is interpreted depending on BIOS
// use VGA color table for more colors
#define WHITE_ON_BLACK 0x0f 
#define RED_ON_WHITE 0xf4   
#define GREEN_ON_BLACK 0x02 

#define SCREEN_REG_CTRL 0x3d4
#define SCREEN_REG_DATA 0x3d5


//public functions
void kclear_screen();
void kprint_at(char *text, int row, int col);
void kprint(char *text);