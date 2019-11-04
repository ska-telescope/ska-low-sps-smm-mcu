/*
 * OneWire.h
 *
 * Created: 30/10/2019 11:39:32
 *  Author: luca
 */ 


#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum CS1W_t {
	TPM1OW		    = 0x00,
	TPM2OW			= 0x01,
	TPM3OW			= 0x02,
	TPM4OW			= 0x03,
	TPM5OW			= 0x04,
	TPM6OW			= 0x05,
	TPM7OW			= 0x06,
	TPM8OW			= 0x07,
	TPMALLOW		= 0xFF			
} CS1W;

int OneWireSetupClock (uint8_t ClkDiv, bool ClkEN);
int OneWireReset (void);
int OneWireWriteByte (char Data);
int OneWireReadByte (char *Data);
int OneWireSelectCS (CS1W CS);

#endif /* ONEWIRE_H_ */