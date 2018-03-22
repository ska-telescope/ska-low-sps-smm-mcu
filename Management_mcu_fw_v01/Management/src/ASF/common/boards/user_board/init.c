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
	
	// COnfigure ADC
	/* List ADC Channel*/
	enum adc_channel_num_t ch_list[12] = {
		ADC_SOC,	// 1360
		ADC_ARM,	// 1360
		ADC_DDR,	// 1350
		ADC_2V5,	// 2500
		ADC_1V0,	// 1000
		ADC_1V1,	// 1100
		ADC_VCORE,  // 1200
		ADC_1V5,    // 1500
		ADC_3V3,	// 3300
		ADC_5V,		// 5000
		ADC_3V,		// 3000
		ADC_2V8		// 2800
	};
	/* Configure ADC pin */
	gpio_configure_pin(PIO_PB0_IDX, PIO_INPUT);
	
	/* Enable ADC clock. */
	pmc_enable_periph_clk(ID_ADC);
	
	/* Configure ADC. */
	adc_init(ADC, sysclk_get_cpu_hz(), 1000000, ADC_MR_STARTUP_SUT0);
	for (int i = 0; i < 13; i++) { // Voltages
		adc_enable_channel(ADC, (enum adc_channel_num_t)i);
		if (i == 9) i++;
	}
	adc_enable_channel(ADC, ADC_BUCK2TEMP); // Temp Buck 2
	adc_configure_trigger(ADC, ADC_TRIG_SW, 1);
	
	// Configure LED
	ioport_set_pin_dir(PIN_LEDK7, IOPORT_DIR_OUTPUT); // Led Amber
	ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_dir(PIN_LEDK8, IOPORT_DIR_OUTPUT); // Led Blue
	ioport_set_pin_level(PIN_LEDK8, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_dir(PIN_LEDTB, IOPORT_DIR_OUTPUT); // Led DemoBoard
	ioport_set_pin_level(PIN_LEDTB, IOPORT_PIN_LEVEL_HIGH);
	
	// Configure GPIO
	//ioport_set_pin_dir(XO3_REFRESH, IOPORT_DIR_OUTPUT); // Pin XO3_REFRESH - Temp Disabled
	//ioport_set_pin_level(XO3_REFRESH, IOPORT_PIN_LEVEL_LOW);
	
	// configure UART pins
	ioport_set_port_mode(IOPORT_PIOA, PIO_PA9A_URXD0 | PIO_PA10A_UTXD0, IOPORT_MODE_MUX_A);
	ioport_disable_port(IOPORT_PIOA, PIO_PA9A_URXD0 | PIO_PA10A_UTXD0);
	
	
	
}
