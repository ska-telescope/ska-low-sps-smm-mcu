/*
 * Sanitas EG - SKA Management Board
 * 
 * V1.0 - 20/03/18 ~ Luca Schettini
 * 
 * Copyright (c) 2017 Sanitas EG srl.  All right reserved.
 * 
 */

#include <asf.h>
#include "spi_master.h"
#include <SpiRouter.h>
#include <regfile.h>
#include "build_def.h"
//#include "i2c.h"

const uint32_t _build_version = 0xb0000001;
const uint32_t _build_date ((((BUILD_YEAR_CH0 & 0xFF - 0x30) * 0x10 ) + ((BUILD_YEAR_CH1 & 0xFF - 0x30)) << 24) | (((BUILD_YEAR_CH2 & 0xFF - 0x30) * 0x10 ) + ((BUILD_YEAR_CH3 & 0xFF - 0x30)) << 16) | (((BUILD_MONTH_CH0 & 0xFF - 0x30) * 0x10 ) + ((BUILD_MONTH_CH1 & 0xFF - 0x30)) << 8) | (((BUILD_DAY_CH0 & 0xFF - 0x30) * 0x10 ) + ((BUILD_DAY_CH1 & 0xFF - 0x30))));
const uint32_t _build_time = (0x00 << 24 | (((__TIME__[0] & 0xFF - 0x30) * 0x10 ) + ((__TIME__[1] & 0xFF - 0x30)) << 16) | (((__TIME__[3] & 0xFF - 0x30) * 0x10 ) + ((__TIME__[4] & 0xFF - 0x30)) << 8) | (((__TIME__[6] & 0xFF - 0x30) * 0x10 ) + ((__TIME__[7] & 0xFF - 0x30))));

// ----- SPI -------
#define SPI_CLOCK_SPEED		4000000UL
#define MYSPI			SPI
#define BUFFERSIZE 1
void send_spi(uint8_t data);
uint8_t data_buffer[BUFFERSIZE];
uint8_t data_rx_buffer[BUFFERSIZE];
// ----- SPI -------

float voltagesnorm[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
uint32_t voltages[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };	
const float voltagesMot[] = { 0.4395, 0.4395, 0.4395, 0.7396, 0.4395,  0.4395, 0.9763, 0.4395, 0.9763, 1.4793, 0.8766, 0.8284 };
float buck2tempnorm = 0;
uint32_t buck2temp = 0;

/* ----------------------------------------- ADC SP Start --- */
void readADCnormalized(void) // Normalized with R divider value
{
	float adc_value;
	// Test ADC
	//adc_val = adc_get_channel_value(ADC, ADC_CHANNEL_0);
	
	int x = 0;
	for(int y=0; y < 13; y++) // Voltages
	{	
		if (y == 10) y++;
		adc_value = 0;
		for(int i=0; i < 10; i++)
		adc_value += adc_get_channel_value(ADC,  (enum adc_channel_num_t)y);
		adc_value /= 10;
		//normalize
		//normalized_adc_value = (adc_value * 1000) / 4096; // Da sistemare in base al partitore
		voltagesnorm[x] = (adc_value * voltagesMot[x]);
		x++;
	}
	buck2tempnorm += adc_get_channel_value(ADC, ADC_BUCK2TEMP); // Temp Buck 2 temp
	buck2tempnorm = ((buck2tempnorm * 0.4395) + 19) / 6.75;
	return;
}

void readADC(void) // Pure ADC value
{
	uint32_t adc_value;
	// Test ADC
	//adc_val = adc_get_channel_value(ADC, ADC_CHANNEL_0);
	
	int x = 0;
	for(int y=0; y < 13; y++) // Voltages
	{
		if (y == 10) y++;
		adc_value = 0;
		for(int i=0; i < 10; i++)
		adc_value += adc_get_channel_value(ADC,  (enum adc_channel_num_t)y);
		adc_value /= 10;
		//normalize
		//normalized_adc_value = (adc_value * 1000) / 4096; // Da sistemare in base al partitore
		voltages[x] = (adc_value);
		x++;
	}
	buck2temp += adc_get_channel_value(ADC, ADC_BUCK2TEMP); // Temp Buck 2 temp
	//buck2temp = ((buck2temp * 0.4395) + 19) / 6.75;
	return;
}

/* ----------------------------------------- ADC SP End --- */

void SPIdataBlock(void){
	// Voltages
	XO3_WriteByte(sam_voltage_soc + sam_offset, voltages[0]);
	XO3_WriteByte(sam_voltage_arm + sam_offset, voltages[1]);
	XO3_WriteByte(sam_voltage_ddr + sam_offset, voltages[2]);
	XO3_WriteByte(sam_voltage_v25 + sam_offset, voltages[3]);
	XO3_WriteByte(sam_voltage_v1 + sam_offset, voltages[4]);
	XO3_WriteByte(sam_voltage_v11 + sam_offset, voltages[5]);
	XO3_WriteByte(sam_voltage_vcore + sam_offset, voltages[6]);
	XO3_WriteByte(sam_voltage_v15 + sam_offset, voltages[7]);
	XO3_WriteByte(sam_voltage_v33 + sam_offset, voltages[8]);
	XO3_WriteByte(sam_voltage_v5 + sam_offset, voltages[9]);
	XO3_WriteByte(sam_voltage_v3 + sam_offset, voltages[10]);
	XO3_WriteByte(sam_voltage_v28 + sam_offset, voltages[11]);
	// Temperatures
	XO3_WriteByte(sam_temp_Buck + sam_offset, buck2temp);
	//XO3_WriteByte(sam_temp_MCU, xxx);
}

int main (void)
{
	/* Insert system clock initialization code here*/
	sysclk_init();
	board_init();

	adc_start(ADC);
	/* Insert application code here, after the board has been initialized. */
	
	spi_flags_t spi_flags = SPI_MODE_0;
	board_spi_select_id_t spi_select_id = 0;
	struct spi_device device = {
		.id = 0
	};
	spi_master_init(MYSPI);
	spi_master_setup_device(MYSPI, &device, spi_flags,	SPI_CLOCK_SPEED, spi_select_id);
	spi_enable(MYSPI);
	spi_enable_clock(MYSPI);
	delay_ms(10);
	XO3_WriteByte(sam_mcufw_build_version + sam_offset, _build_version);
	XO3_WriteByte(sam_mcufw_build_time + sam_offset, _build_time);
	XO3_WriteByte(sam_mcufw_build_date + sam_offset, _build_date);
	readADC(); // Drop first read
	//SetupTWI0();

	while (1) {
		delay_ms(1000);
		readADC();
		SPIdataBlock();
		
		//XO3_WriteByte(0x00000800, 0xF);
		//delay_ms(100);
		//XO3_WriteByte(0x00000800, 0x0);
		//spi_write(SPI_MASTER, 0xf, 0, 1);
		//send_spi(0xF1); // Farlocca
		//delay_ms(1000);
		
		//uint32_t dato;
		//uint32_t dato4;
		//uint32_t dato8;
   
		//XO3_WriteByte(regfile_user_reg0, _build_hour);
		//XO3_Read(sam_mcufw_build_date+sam_offset, &dato);
		//XO3_Read(regfile_user_reg0, &dato4);
		//XO3_Read(0x00000008, &dato8);
		
		//XO3_Read(regfile_user_reg0, &dato);

		//ioport_toggle_pin_level(PIN_LEDK8);	
		
	}

}
