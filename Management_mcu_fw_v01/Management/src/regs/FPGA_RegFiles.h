/*
 * FPGA_RegFiles.h
 *
 * Created: 18/12/2018 16:15:59
 *  Author: luca
 */ 


#ifndef FPGA_REGFILES_H_
#define FPGA_REGFILES_H_

#include "intctrl.h"
#include "mdio.h"
#include "onewire.h"
#include "regfile.h"
#include "sam.h"
#include "uart.h"
#include "twi_fpga.h"
#include "fram.h"

// Register Base Address
#define regfile_offset	0x00000000
//#define twi_offset		0x00010000
#define intctr_offset	0x00020000
#define sam_offset		0x00030000
#define uart_offset		0x00070000
#define fram_offset		0x00090000 //2 KB


#endif /* FPGA_REGFILES_H_ */