#ifndef ATMEGA328P_HC_SRO4_H
#define ATMEGA328P_HC_SRO4_H

void sensor_init(void);
unsigned sensor_read(void);
void sensor_trig(void);

#endif