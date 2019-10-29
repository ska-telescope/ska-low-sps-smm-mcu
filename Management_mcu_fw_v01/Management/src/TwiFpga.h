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

#define MAX_BUSY_RETRY		10

#define R8BIT		1
#define R16BIT		2

#define W8BIT		2
#define W16BIT		4

/*
 * I2C Addresses - 8bit (7bit)
 */

// i2c3
#define IOEXP	0x40 // (0x20)
#define PSU1	0xB0 // (0x58)
#define PSU2	0xB2 // (0x59)

typedef enum twiFPGAadd_t {
	i2c1		    = 0x0,
	i2c2			= 0x1,
	i2c3			= 0x2,
	i2c4			= 0x3
} twiFPGAadd;

int twiFpgaWrite (uint8_t ICaddress,
				   uint8_t byte2write,
				   uint8_t byte2read,
				   uint32_t datatx,
				   uint32_t* datarx,
				   twiFPGAadd address
				   );

uint8_t twiFpgaRead8 (uint8_t ICaddress,
				  uint32_t TwiRegister,
				  twiFPGAadd address
				  );
				  
uint16_t twiFpgaRead16 (uint8_t ICaddress,
				   uint32_t TwiRegister,
				   twiFPGAadd address
				   );

uint8_t twiFpgaWrite8 (uint8_t ICaddress,
					   uint8_t dataOut,
					   uint32_t TwiRegister,
					   twiFPGAadd address
					  );

uint16_t twiFpgaWrite16 (uint8_t ICaddress,
						 uint16_t dataOut,
						 uint32_t TwiRegister,
						 twiFPGAadd address
						);

#endif /* TWIFPGA_H_ */