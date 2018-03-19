/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	
	WDT->WDT_MR = WDT_MR_WDDIS;         // disable watchdog
	
	ioport_init();
	ioport_set_pin_dir(PIN_LEDTB, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_LEDTB, IOPORT_PIN_LEVEL_HIGH);
	
	// configure UART pins
	ioport_set_port_mode(IOPORT_PIOA, PIO_PA9A_URXD0 | PIO_PA10A_UTXD0, IOPORT_MODE_MUX_A);
	ioport_disable_port(IOPORT_PIOA, PIO_PA9A_URXD0 | PIO_PA10A_UTXD0);
	
	/*void ADC_IrqHandler(void)
	{
		//Check the ADC conversion status
		if ((adc_get_status(ADC) & ADC_ISR_DRDY) == ADC_ISR_DRDY)
		{
			//Get latest digital data value from ADC and can be used by application
			uint32_t result = adc_get_latest_value(ADC);
		}
	}
	adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 8);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_0);
	adc_enable_interrupt(ADC, ADC_IER_DRDY);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);*/
	
}
