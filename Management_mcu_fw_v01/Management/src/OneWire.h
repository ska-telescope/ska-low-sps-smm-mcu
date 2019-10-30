/*
 * OneWire.h
 *
 * Created: 30/10/2019 11:39:32
 *  Author: luca
 */ 


#ifndef ONEWIRE_H_
#define ONEWIRE_H_

int OneWireReset(void);
int OneWireWriteByte(char Data);
int OneWireReadByte(char *Data);



#endif /* ONEWIRE_H_ */