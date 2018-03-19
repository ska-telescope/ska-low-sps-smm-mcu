/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

static void configure_adc(void)
{
	/* List ADC Channel*/
	enum adc_channel_num_t ch_list[10] = {
		ADC_SOC,
		ADC_ARM,
		ADC_DDR,
		ADC_2V5,
		ADC_1V0,
		ADC_1V1,
		ADC_1V2, 
		ADC_1V5, 
		ADC_3V3, 
		ADC_5V	
		};
	/* Configure ADC pin for light sensor. */
	gpio_configure_pin(PIO_PB0_IDX, PIO_INPUT);
	
	/* Enable ADC clock. */
	pmc_enable_periph_clk(ID_ADC);
	
	/* Configure ADC. */
	adc_init(ADC, sysclk_get_cpu_hz(), 1000000, ADC_MR_STARTUP_SUT0);
	//adc_enable_channel(ADC, ADC_CHANNEL_0);
	for (int i = 0; i < 10; i++) {
		adc_enable_channel(ADC, (enum adc_channel_num_t)i);
	}
	adc_configure_trigger(ADC, ADC_TRIG_SW, 1);
}

void readADC(void)
{
	uint16_t adc_value;
	uint16_t normalized_adc_value;
	// Test ADC
	//adc_val = adc_get_channel_value(ADC, ADC_CHANNEL_0);
			
	uint16_t adc_value = 0;
	for(int i=0; i<10; i++)
	adc_value += adc_get_channel_value(ADC, ADC_CHANNEL_0);
	adc_value /= 10;
	//normalize
	normalized_adc_value = (adc_value * 1000) / 4096;
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	//uint32_t adc_val;
	
	//Configure ADC
	configure_adc();
	//start ADC
	adc_start(ADC);
	
	/* Insert application code here, after the board has been initialized. */
	while (1) {
		ioport_toggle_pin_level(PIN_LEDTB);
		
		readADC();
		
		//delay_ms(1000);
		
	}
}