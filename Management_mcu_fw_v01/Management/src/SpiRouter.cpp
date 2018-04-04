/*
 * Sanitas EG SPI Router
 * 
 * V1.3 - 17/01/18 ~ Luca Schettini
 * 
 * ~ CHANGELOG ~ 
 * V1.0  - Initial Version.
 * V1.1b - XO3 SPI read with left shifting for mitigation XO3 SPI design error.
 * V1.2  - XO3 SPI ok, remove mitigation from MCU side.
 * V1.3  - Added free to buffer and rxbuffer to free memory. [OoF Issue] 
 * V1.4  - New SPI version
 *
 * Copyright (c) 2017 Sanitas EG srl.  All right reserved.
 * 
 */

#include <memory.h>
#include <string.h>

//#include "MLC150.h"
#include <SpiRouter.h>
#include <asf.h>
#include <regfile.h>

//#include "Arduino.h"
//#include <SPI.h>


int
SPI_sync(
		uint32_t       slaveId,
		const uint8_t* txBuffer,
		uint8_t*       rxBuffer,
		uint16_t    length
)
{
	uint8_t*  tmp           = nullptr;
	uint16_t* txbuf         = nullptr;
 	uint8_t* rxbuf         = nullptr;
	//std::vector<uint16_t> rxbuf;
	uint32_t  offset        = 0;
	bool      last          = true;
	bool      little_endian = true;

	void* buffer = nullptr;
	void* rxbuffer = nullptr;

	uint16_t _length = length;
	uint16_t _count  = length;

	
		
		buffer = malloc(length + 8); // Make sure we have some (4) spare bytes at the end...
		rxbuffer = malloc(length + 8); // Make sure we have some (4) spare bytes at the end...
		tmp    = (uint8_t*)buffer;
		txbuf  = (uint16_t*)buffer;
 		rxbuf  = (uint8_t*)rxbuffer;
		slaveId >>= 8;
		slaveId  &= 0x000000FF;

/*		if (slaveId) */{ 
			if (length < 128) {
				tmp[0] = (uint8_t)(slaveId);
				tmp[1] = length & ~0x80;

//			tmp[length + 3] = 0x00;

				_length = length + 3;
				_count  = length + 3;

				offset = 2;
			} else {
				tmp[0] = (uint8_t)(slaveId);
				tmp[1] = 0x80;

				tmp[2] = (length >> 8) & 0xFF;
				tmp[3] = length & 0xFF;

//			tmp[length + 4] = 0x00;

				_length = length + 5;
				_count  = length + 5;

				offset = 4;
			}

			if (last) {
				tmp[0] &= ~0x80;
			} else {
				tmp[0] |= 0x80;
			}
		}

		if (txBuffer) {
			memcpy(&tmp[offset], txBuffer, length);
		}

		if (_count & 0x00000001) {
			_count++;
		}

		if (!little_endian) {
			uint16_t* ptr = txbuf;

			for (int i = 0; i < _count; i += 2) {
				uint16_t x = *ptr;
				x    = ((x & 0xff00) >> 8) | ((x & 0xff) << 8);
				*ptr = x;
				ptr++;
			}
		}
		
		//SPI1.beginTransaction(SPISettings(12000000, MSBFIRST, SPI_MODE0)); //SPI1 - XO3 Setup
		//digitalWrite(XO3_SS, LOW); //Set Low XO3_SS to select
		for(int i=0;i<_count;i++){
			//spi_write(SPI_MASTER, tmp[i], 0, 0);
			//rxbuf[i]=SPI1.transfer(tmp[i]);
		}
		//digitalWrite(XO3_SS, HIGH); //Set High XO3_SS to deselect
		//SPI1.endTransaction();
		
		memcpy(rxBuffer, &rxbuf[4], length);
		if (!little_endian) {
			uint16_t* ptr = (uint16_t*)rxBuffer;

			for (int i = 0; i < length; i += 2) {
				uint16_t x = *ptr;
				x    = ((x & 0xff00) >> 8) | ((x & 0xff) << 8);
				*ptr = x;
				ptr++;
			}
		}
		free(buffer);
		free(rxbuffer);
		return 0;
} // SPI_sync





/*int
XO3_Write(
    void*    context,
    uint32_t offset,
    uint32_t value,
    void*    privateData
)*/
void
XO3_WriteByte(
    uint32_t offset,
    uint32_t value
)
{
	uint8_t txBuffer[8];
	uint8_t rxBuffer[8];

	memset(txBuffer, 0, 8);

	txBuffer[0] = 0x01;
	//txBuffer[1] = 0xFF & (offset >> 24);
	txBuffer[1] = 0xFF & (offset >> 16);
	txBuffer[2] = 0xFF & (offset >> 8);
	txBuffer[3] = 0xFF & (offset);
	txBuffer[4] = 0xFF & (value >> 8);
	txBuffer[5] = 0xFF & (value);

  int success = SPI_sync(1, txBuffer, rxBuffer, 8);
} // XO3_Write
/*
int
XO3_Read(
    void*     context,
    uint32_t  offset,
    uint32_t* value,
    void*     privateData
)*/
int
XO3_Read(
    uint32_t  offset,
    uint32_t* value
)
{
  uint8_t txBuffer[8];
  uint8_t rxBuffer[8];
  uint32_t dato=0;
  memset(txBuffer, 0, 8);

  txBuffer[0] = 0x03;
  //txBuffer[1] = 0xFF & (offset >> 24);
  txBuffer[1] = 0xFF & (offset >> 16);
  txBuffer[2] = 0xFF & (offset >> 8);
  txBuffer[3] = 0xFF & (offset);

  int success = SPI_sync(1, txBuffer, rxBuffer, 8);

  dato = (((rxBuffer[5] & 0xFF) << 8) | rxBuffer[6]);
  dato=dato&0x0000ffff;
  *value=dato;
  return success;
} // XO3_Read

/*
int
XO3_Address(
    void*     context,
    uint32_t  offset,
    uint32_t* value,
    void*     privateData
)
{
  *value = offset;
  return 0;//success;
} // XO3_Read
*/
