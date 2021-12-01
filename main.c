#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "atmega328P_LCD.h"
#include "atmega328P_HC_SR04.h"

#define reg1    PORTC
#define RS      PORTC0
#define EN      PORTC1
#define D4      PORTC2
#define D5      PORTC3
#define D6      PORTC4
#define D7      PORTC5 

#define set_bit(reg,bit) (reg |=(1<<bit))
#define clr_bit(reg,bit) (reg &= ~(1<<bit))

int main(void)
{
    disp_init();
    disp_cmd(0x0C);
    sensor_init();

    disp_text("Distance:",0,1);

    while(1)
    {
        disp_number(sensor_read(),1,1);
        disp_write('c');
        disp_write('m');
        _delay_ms(500);
    }

    return 0;
}