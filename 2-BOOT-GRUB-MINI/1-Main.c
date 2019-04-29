
#include "Outils.h"
#include "Clavier.h"
#include "Ecran.h"

//=================================================================
// -Ttext=0x100000 --entry=_start --oformat i586-pc-elf

#define NB_COL      80
#define NB_LN       25
#define STD_CLR     0x07

//unsigned int* Video;
//unsigned short* carac;


/*
void write(char* string, int offset){
    unsigned char* charWrite = (unsigned char*)0xB8000;
    charWrite += (offset * 2);
    int i = 0;
    while(string[i] != '\0'){
        
        *charWrite = string[i];
        charWrite++;
        *charWrite = 0x07;
        charWrite++;
        i++;
    }
    
}
*/

/*
void print(char* string, int line, int col)
{
    carac = (unsigned short*)0xB8000;
    carac += (NB_COL * line + col);
    int i = 0;
    while(string[i] != '\0'){
        *carac = (STD_CLR << 8) | string[i];
        carac++;
        i++;
    }
    
}

void Affi(char c, int pX, int pY)
{
    carac = (unsigned short*)0xB8000 + (NB_COL * pY + pX);
    *carac = (STD_CLR << 8) | c;
    carac++;

}
*/

/*
inline void show_cursor(int pX, int pY)
{
    
#define outb(P_port, P_val) asm volatile ("outb %%al, %%dx" ::"d" (P_port), "a" (P_val));
    unsigned short L_Offset;
    L_Offset = (pY* NB_COL) + pX;
    outb(0x3d4, 0x0f);
    outb(0x3d5, (unsigned char) L_Offset);
    outb(0x3d4, 0x0e);
    outb(0x3d5, (unsigned char) (L_Offset >> 8));
}

void clear_Screen()
{
    Video = (unsigned int*)0xB8000;
    char filler = ' ';
    while(Video < (unsigned int*)(0xB8000 + NB_COL*NB_LN*2)) {
        *Video = 0x07200720;
        *Video = (STD_CLR<<24) | (filler<<16) | (STD_CLR<<8) | filler;
        Video++;
    }
    show_cursor(0,0);
}
*/

void OS_Start()
{
    Efface_Ecran();
    Repositionne_Curseur();
    
}

