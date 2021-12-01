#define F_CPU 16000000

#define ECHO PORTB0
#define TRIG PORTD7

#include <avr/io.h>
#include <util/delay.h>
#include "atmega328P_HC_SR04.h"
#include <avr/interrupt.h>


ISR(TIMER0_OVF_vect)
{
    static unsigned counter = 0;
    counter ++;

    if (counter == 0x0F)
    {
        counter = 0x00;
    }
    sensor_trig();
}

void sensor_init(void)
{
    cli();
    TCNT0  = 0x00;
    TCCR0B = (1<<2);
    TIMSK0 = (1<<0);
    sei();

    DDRD |= (1 << TRIG);
}

void sensor_trig(void)
{
    PORTD |= (1 << TRIG);
    _delay_us(10);
    PORTD &= ~(1 << TRIG);
}

unsigned sensor_read(void)
{
    unsigned pulse_us = 0;

    while(!(PINB &(1<<ECHO)));

    TCCR1A = 0x00;
    TCCR1B = ((1<<CS11));
    TCNT1 =  0x00;

    for(;;)
    {
        if (PINB &(1 << ECHO))
        {
            if(TCNT1 > 60000) 
                break;
            else 
                continue;
        }
        else
        {
            break;
        }
    }
        pulse_us = TCNT1;
        TCCR1B = 0x00;
        return ((pulse_us >> 1)/58);    
}
