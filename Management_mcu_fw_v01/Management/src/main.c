/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

float voltages[12] = { 0 };	
const float voltagesMot[] = { 0.4395, 0.4395, 0.4395, 0.7396, 0.4395,  0.4395, 0.9763, 0.4395, 0.9763, 1.4793, 0.8766, 0.8284 };

static void configure_adc(void)
{
	/* List ADC Channel*/
	enum adc_channel_num_t ch_list[12] = {
		ADC_SOC,
		ADC_ARM,
		ADC_DDR,
		ADC_2V5,
		ADC_1V0,
		ADC_1V1,
		ADC_VCORE, 
		ADC_1V5, 
		ADC_3V3, 
		ADC_5V,
		ADC_3V,
		ADC_2V8
		};
	/* Configure ADC pin */
	gpio_configure_pin(PIO_PB0_IDX, PIO_INPUT);
	
	/* Enable ADC clock. */
	pmc_enable_periph_clk(ID_ADC);
	
	/* Configure ADC. */
	adc_init(ADC, sysclk_get_cpu_hz(), 1000000, ADC_MR_STARTUP_SUT0);
	for (int i = 0; i < 13; i++) {
		adc_enable_channel(ADC, (enum adc_channel_num_t)i);
		if (i == 9) i++;
	}
	adc_configure_trigger(ADC, ADC_TRIG_SW, 1);
}

void readADC(void)
{
	uint32_t adc_value;
	uint32_t normalized_adc_value;
	// Test ADC
	//adc_val = adc_get_channel_value(ADC, ADC_CHANNEL_0);
	
	
	for(int y=0; y < 13; y++)
	{	
		volatile int x = 0;
		adc_value = 0;
		for(int i=0; i < 10; i++)
		adc_value += adc_get_channel_value(ADC,  (enum adc_channel_num_t)y);
		adc_value /= 10;
		//normalize
		//normalized_adc_value = (adc_value * 1000) / 4096; // Da sistemare in base al partitore
		voltages[x] = (adc_value * voltagesMot[y]);
		if (y == 9) y++;
		x++;
	}
	int b = 0;
	return;
}

int main (void)
{
	/* Insert system clock initialization code here*/
	sysclk_init();
	board_init();
	
	//uint32_t adc_val;
	
	//Configure ADC
	configure_adc();
	//start ADC
	adc_start(ADC);
	
	/* Insert application code here, after the board has been initialized. */
	while (1) {
		//ioport_toggle_pin_level(PIN_LEDTB);		
		readADC();
		
		//delay_ms(1000);
		
	}
}