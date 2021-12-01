#ifndef ATMEGA328P_LCD_H
#define ATMEGA328P_LCD_H

void disp_number(unsigned num, char row, char col);
void disp_wr_po(unsigned char chr, char row, char col);
void disp_text(char *str, char row, char col);
void disp_write(unsigned char chr);
void disp_cmd(unsigned char cmd);
void disp_init(void);
void disp_clear(void);
void send_nibble(unsigned char nib, char rsel);

#endif