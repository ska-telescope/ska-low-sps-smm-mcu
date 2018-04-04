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

#define SPI_CLOCK_SPEED		4000000UL
#define MYSPI			SPI
#define BUFFERSIZE 1
void send_spi(uint8_t data);
uint8_t data_buffer[BUFFERSIZE];
uint8_t data_rx_buffer[BUFFERSIZE];


float voltages[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };	
const float voltagesMot[] = { 0.4395, 0.4395, 0.4395, 0.7396, 0.4395,  0.4395, 0.9763, 0.4395, 0.9763, 1.4793, 0.8766, 0.8284 };
float buck2temp = 0;



/* ----------------------------------------- ADC SP Start --- */
void readADC(void)
{
	float adc_value;
	uint32_t normalized_adc_value;
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
		voltages[x] = (adc_value * voltagesMot[x]);
		x++;
	}
	buck2temp += adc_get_channel_value(ADC, ADC_BUCK2TEMP); // Temp Buck 2
	buck2temp = ((buck2temp * 0.4395) + 19) / 6.75;
	return;
}

/* ----------------------------------------- ADC SP End --- */

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

	while (1) {
		ioport_toggle_pin_level(PIN_LEDTB);				
		readADC();
		//XO3_WriteByte(0x00000800, 0xF);
		delay_ms(100);
		//XO3_WriteByte(0x00000800, 0x0);
		//spi_write(SPI_MASTER, 0xf, 0, 1);
		send_spi(0xF1);
		//delay_ms(1000);
		
	}
}

void send_spi(uint8_t data){
	
	struct spi_device device = {
		
		device.id = 0
		
	};
	spi_select_device(MYSPI, &device);
	data_buffer[0] = data;
	
	//spi_write_packet(MYSPI, data_buffer, sizeof(data_buffer));
	spi_transceive_packet(MYSPI, data_buffer, data_rx_buffer, sizeof(data_buffer));
	
	spi_deselect_device(MYSPI, &device);
	delay_us(10);
	
	
}
