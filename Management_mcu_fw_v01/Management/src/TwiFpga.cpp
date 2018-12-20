/*
 * TwiFpga.cpp
 *
 * Created: 18/12/2018 14:19:42
 *  Author: luca
 */ 

#include <TwiFpga.h>
#include <SpiRouter.h>
#include <asf.h>
#include "FPGA_RegFiles.h"

int twiFpgaWrite (uint8_t ICaddress, uint8_t byte2write, uint8_t byte2read, uint32_t datatx, uint32_t* datarx, twiFPGAadd address)
{
	uint32_t twi_ctrl_data = 0;
	uint32_t dataIN;
	uint32_t statusIN;
	uint8_t busyRetry = 0;
	
	ICaddress = ICaddress >> 1;
	twi_ctrl_data += (byte2read << 24); // [31:24] byte number to read
	twi_ctrl_data += (byte2read << 16); // [23:16] byte number to write
	twi_ctrl_data += (ICaddress); // [9:0] command - [6:0] IC address
	twi_ctrl_data += address; // [9:0] command - [9:8] FPGA router TWI address
	
	XO3_WriteByte(twi_offset + twi_wrdata, datatx);
	XO3_WriteByte(twi_offset + twi_command, twi_ctrl_data);
    XO3_Read(twi_offset + twi_status, &statusIN);
	while (statusIN == 0x1) {
		busyRetry++;
		if (busyRetry >= MAX_BUSY_RETRY) return int(statusIN);
		XO3_Read(twi_offset + twi_status, &statusIN);
	}
	XO3_Read(twi_offset + tiw_rdata, &dataIN);
	
	
	*datarx = dataIN;
	return int(statusIN);
}

int twiFpgaRead8 (uint8_t ICaddress, uint32_t TwiRegister, uint8_t* datarx, twiFPGAadd address)
{
	int status;
	uint32_t data;
		
	status = twiFpgaWrite(ICaddress, RW8BIT, RW8BIT, TwiRegister, &data, address);
	
	*datarx = data;
	return status;
}

int twiFpgaRead16 (uint8_t ICaddress, uint32_t TwiRegister, uint16_t* datarx, twiFPGAadd address)
{
	int status;
	uint32_t data;
	
	status = twiFpgaWrite(ICaddress, RW16BIT, RW16BIT, TwiRegister, &data, address);
	
	*datarx = data;
	return status;
}