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

int twiFpgaWrite (uint8_t ICaddress, uint8_t byte2write, uint8_t byte2read, uint32_t datatx, uint32_t* datarx)
{
	uint32_t twi_ctrl_data = 0;
	uint32_t dataIN;
	uint32_t statusIN;
	
	ICaddress = ICaddress >> 1;
	twi_ctrl_data += (byte2read << 24); // [31:24] byte number to read
	twi_ctrl_data += (byte2read << 16); // [23:16] byte number to write
	twi_ctrl_data += (ICaddress); // [9:0] command - [6:0] IC address
	//twi_ctrl_data += 0x100;
	
	XO3_WriteByte(twi_offset + twi_wrdata, datatx);
	XO3_WriteByte(twi_offset + twi_command, twi_ctrl_data);
	for (int i = 0; i < 2000; i++){
		asm("nop");
	}
	XO3_Read(twi_offset + tiw_rdata, &dataIN);
	XO3_Read(twi_offset + tiw_rdata, &statusIN);
	
	*datarx = dataIN;
	return int(statusIN);
}