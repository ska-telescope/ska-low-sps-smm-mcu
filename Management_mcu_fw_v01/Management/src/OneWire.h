/*
 * OneWire.h
 *
 * Created: 30/10/2019 11:39:32
 *  Author: luca
 */ 


#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <stdbool.h>

int OneWireSetupClock(uint8_t ClkDiv, bool ClkEN);
int OneWireReset(void);
int OneWireWriteByte(char Data);
int OneWireReadByte(char *Data);



#endif /* ONEWIRE_H_ */