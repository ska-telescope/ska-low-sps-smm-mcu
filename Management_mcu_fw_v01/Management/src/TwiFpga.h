/*
 * TwiFpga.h
 *
 * Created: 18/12/2018 14:19:59
 *  Author: Luca Schettini
 */ 

#include <stdint.h>

#ifndef TWIFPGA_H_
#define TWIFPGA_H_

#define TWISTATUS_OK		0x00
#define TWISTATUS_ACK_ERR	0x02

int twiFpgaWrite (uint8_t ICaddress,
				   uint8_t byte2write,
				   uint8_t byte2read,
				   uint32_t datatx,
				   uint32_t* datarx
				   );


#endif /* TWIFPGA_H_ */