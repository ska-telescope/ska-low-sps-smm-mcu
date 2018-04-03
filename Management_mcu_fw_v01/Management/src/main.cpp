/*
 * Sanitas EG - SKA Management Board
 * 
 * V1.0 - 20/03/18 ~ Luca Schettini
 * 
 * Copyright (c) 2017 Sanitas EG srl.  All right reserved.
 * 
 */

#include <asf.h>
#include <SpiRouter.h>
#include <regfile.h>

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

/* ----------------------------------------- SPI SP Start --- */

/*void spi_master_init(Spi *p_spi)
{
	spi_enable_clock(p_spi);
	spi_reset(p_spi);
	spi_set_master_mode(p_spi);
	spi_disable_mode_fault_detect(p_spi);
	spi_disable_loopback(p_spi);
	spi_set_peripheral_chip_select_value(p_spi,
	spi_get_pcs(DEFAULT_CHIP_ID));
	spi_set_fixed_peripheral_select(p_spi);
	spi_disable_peripheral_select_decode(p_spi);
	spi_set_delay_between_chip_select(p_spi, CONFIG_SPI_MASTER_DELAY_BCS);
}
void spi_master_setup_device(Spi *p_spi, struct spi_device *device,
spi_flags_t flags, uint32_t baud_rate, board_spi_select_id_t sel_id)
{
	spi_set_transfer_delay(p_spi, device->id, CONFIG_SPI_MASTER_DELAY_BS,
	CONFIG_SPI_MASTER_DELAY_BCT);
	spi_set_bits_per_transfer(p_spi, device->id, CONFIG_SPI_MASTER_BITS_PER_TRANSFER);
	spi_set_baudrate_div(p_spi, device->id,
	spi_calc_baudrate_div(baud_rate, sysclk_get_peripheral_hz()));
	spi_configure_cs_behavior(p_spi, device->id, SPI_CS_KEEP_LOW);
	spi_set_clock_polarity(p_spi, device->id, flags >> 1);
	spi_set_clock_phase(p_spi, device->id, ((flags & 0x1) ^ 0x1));
}*/

/* ----------------------------------------- ADC SP End --- */

int main (void)
{
	/* Insert system clock initialization code here*/
	sysclk_init();
	board_init();

	adc_start(ADC);
	/* Insert application code here, after the board has been initialized. */

	while (1) {
		//ioport_toggle_pin_level(PIN_LEDTB);		
		readADC();
		XO3_WriteByte(0x00000800, 0xF);
		delay_ms(100);
		XO3_WriteByte(0x00000800, 0x0);
		
		//delay_ms(1000);
		
	}
}