#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "atmega328P_LCD.h"

#define reg1    PORTC
#define RS      PORTC0
#define EN      PORTC1
#define D4      PORTC2
#define D5      PORTC3
#define D6      PORTC4
#define D7      PORTC5 
#define LED     PORTB1

#define set_bit(reg,bit) (reg |=(1<<bit))
#define clr_bit(reg,bit) (reg &= ~(1<<bit))

void disp_init(void)
{
    set_bit(DDRC,RS);
    set_bit(DDRC,EN);
    set_bit(DDRC,D4);
    set_bit(DDRC,D5);
    set_bit(DDRC,D6);
    set_bit(DDRC,D7);

    _delay_ms(48);
    send_nibble(0x30,0);
    _delay_ms(5);
    send_nibble(0x30,0);
    _delay_us(150);
    send_nibble(0x30,0);
    send_nibble(0x20,0);
    disp_cmd(0x28);
    disp_cmd(0x0F);
    disp_cmd(0x06);
    disp_clear();
}

void send_nibble(unsigned char nib, char rsel)
{
    ((nib>>4)&0x01) ? set_bit(reg1,D4) : clr_bit(reg1,D4);            

    ((nib>>5)&0x01) ? set_bit(reg1,D5) : clr_bit(reg1,D5);
        
    ((nib>>6)&0x01) ? set_bit(reg1,D6) : clr_bit(reg1,D6);

    ((nib>>7)&0x01) ? set_bit(reg1,D7) : clr_bit(reg1,D7);
        
    (rsel) ?  set_bit(reg1,RS) : clr_bit(reg1,RS);    

    set_bit(reg1,EN);
    _delay_us(1200);
    clr_bit(reg1,EN);
    _delay_us(1200);
}
void disp_clear(void)
{
    disp_cmd(0x02);
    disp_cmd(0x01);
}

void disp_cmd(unsigned char cmd)
{
    send_nibble(cmd, 0);
    cmd <<= 4;
    send_nibble(cmd, 0);
}

void disp_write(unsigned char chr)
{
    send_nibble(chr, 1);
    chr <<= 4;
    send_nibble(chr, 1);
}

void disp_text(char *str, char row, char col)
{
    register int i;

    for(i=0; str[i] != '\0';i++,col++)
        disp_wr_po(str[i],row,col);
}

void disp_wr_po(unsigned char chr, char row, char col)
{
    if(!row)
    {
        disp_cmd(0x80 | col);
        disp_write(chr);
    }
    else
    {
        disp_cmd(0xC0 | col);
        disp_write(chr);
    }
}

void disp_number(unsigned num, char row, char col)
{

    char dem, mil, cen, dez, uni;
    short no_zero = 0;

    dem = (char)(num/10000);
    mil = (char)(num%10000/1000);
    cen = (char)(num%1000/100);
    dez = (char)(num%100/10);
    uni = (char)(num%10);

    if(!dem && !no_zero)
        disp_wr_po(' ', row, col);
    else
    {
        disp_wr_po(dem+0x30,row,col);
        no_zero = 1;
    }

    if (!mil && !no_zero)
        disp_write(' ');
    else
    {
        disp_write(mil+0x30);
    }

    if(!cen && !no_zero)
        disp_write(' ');
    else
    {
        disp_write(cen+0x30);
        no_zero = 1;
    }

    if(!dez && !no_zero)
        disp_write(' ');
    else
    {
        disp_write(dez+0x30);
        no_zero = 1;
    }

    disp_write(uni+0x30);
}
