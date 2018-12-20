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

#define MAX_BUSY_RETRY		5

#define RW8BIT		1
#define RW16BIT		2

typedef enum twiFPGAadd_t {
	i2c1		    = 0x0,
	i2c2			= 0x100,
	i2c3			= 0x200
} twiFPGAadd;

int twiFpgaWrite (uint8_t ICaddress,
				   uint8_t byte2write,
				   uint8_t byte2read,
				   uint32_t datatx,
				   uint32_t* datarx,
				   twiFPGAadd address
				   );

int twiFpgaRead8 (uint8_t ICaddress,
				  uint32_t TwiRegister,
				  uint8_t* datarx,
				  twiFPGAadd address
				  );
				  
int twiFpgaRead16 (uint8_t ICaddress,
				   uint32_t TwiRegister,
				   uint16_t* datarx,
				   twiFPGAadd address
				   );

#endif /* TWIFPGA_H_ */