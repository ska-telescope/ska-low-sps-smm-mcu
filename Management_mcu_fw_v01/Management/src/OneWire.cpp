/*
 * OneWire.cpp
 *
 * Created: 29/10/2019 16:35:32
 *  Author: luca
 *
 * Adapted from https://www.maximintegrated.com/en/design/technical-documents/app-notes/1/145.html
 */ 

#include <SpiRouter.h>
#include "FPGA_RegFiles.h"


static const uint32_t Command1WM	= onewire_offset + onewire_Command1WM;	/* Address of Command Register */
static const uint32_t Data1WM		= onewire_offset + onewire_Data1WM;		/* Address of Data Register */
static const uint32_t Int1WM		= onewire_offset + onewire_Int1WM;		/* Address of Interrupt Register */
static const uint32_t Clock1WM		= onewire_offset + onewire_Clock1WM;	/* Address DS1WM Clock Divider */

/* The clock divider must be programmed before 1-Wire communication can take place */
/* Refer to the DS1WM datasheet page 4 for the proper programming value for you system clock */
//*Clock1WM = (unsigned char)0x12; /* Setup for 32MHz Clock */

/* Reset will generate a reset on the 1-Wire bus. If no presence detect was seen, it will return a 1, */
/* otherwise it returns 0. */
int OneWireReset(void)
{
	unsigned char result;
	uint32_t readback;
	int loop;
	int DELAY = 30000; /* Time to Poll for Completion */
	/* Choose a length to Poll that is slightly greater than */
	/* the maximum possible time to complete the operation */
	XO3_Write(Command1WM, 0x01); /* Send 1WR Reset */
	for( loop=0; loop < DELAY; loop++ ) /* Poll INT Register for command completion */
	{
		XO3_Read(Int1WM, &readback);	
		result=(unsigned char)readback;
		if(result&0x01) break;
	}
	if((result&0x02) != 0x00) return 1; /* No Presence Detect Found, Return Error */
	return 0;
}

/* Send a byte on the 1-Wire Bus. Poll for completion afterwards */
/* Return 1 if operation timed out, 0 if successful */
int OneWireWriteByte(char Data)
{
	unsigned char result;
	uint32_t readback;
	int loop;
	int DELAY = 30000; /* Time to Poll for Completion */
	/* Choose a length to Poll that is slightly greater than */
	/* the maximum possible time to complete the operation */
	
	XO3_Write(Data1WM, (uint8_t)Data); /* Transmit Data Byte on the Bus */
	for( loop=0; loop < DELAY; loop++ ) /* Poll INT Register for command completion */
	{
		XO3_Read(Int1WM, &readback);
		result=(unsigned char)readback;
		if((result&0x0C) == 0x0C ) break; /* Poll TBE & TEMT until both are empty */
	}
	if(loop == DELAY) return 1; /* Operation Timed Out */
	return 0;
}

/* Read a byte from the 1-Wire Bus. Write a 0xFF to create read time slots and poll for receive */
/* buffer full before moving the result to the location pointed to by *Data. Returns a 1 if either */
/* the write 0xFF or read times out, 0 otherwise. */
int OneWireReadByte(char *Data)
{
	unsigned char result;
	uint32_t readback;
	int loop;
	int DELAY = 30000; /* Time to Poll for Completion */
	/* Choose a length to Poll that is slightly greater than */
	/* the maximum possible time to complete the operation */

	if(OneWireWriteByte((char)0xFF)) return 1; /* Generate 1-Wire read timeslots */
	for( loop=0; loop < DELAY; loop++ ) /* Poll INT Register for command completion */
	{
		XO3_Read(Int1WM, &readback);
		result=(unsigned char)readback;
		if((result&0x10) == 0x10 ) break; /* Poll RBF until set */
	}
	if(loop == DELAY) return 1; /* Operation Timed Out */
	XO3_Read(Data1WM, &readback);
	*Data = readback; /* Retrieve data that was returned */
	return 0;
}