/*
 * Sanitas EG - SKA Management Board
 * 
 * V1.0 - 20/03/18 ~ Luca Schettini
 * 
 * Copyright (c) 2017 Sanitas EG srl.  All right reserved.
 * 
 */

#include <asf.h>
#include <string.h>
#include "conf_board.h"

#include "spi_master.h"
#include <SpiRouter.h>
#include "build_def.h"
#include <TwiFpga.h>
//#include "i2c.h"

// Registers
// #include "intctrl.h"
// #include "mdio.h"
// #include "onewire.h"
// #include "regfile.h"
// #include "sam.h"
// #include "uart.h"
#include "FPGA_RegFiles.h"

//#define ENABLE_IMX_TWI_INTERRUPT
bool iMX_use_TWI = false;

const uint32_t _build_version = 0xd0000001;
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
uint32_t internalTemp = 0;

pwm_channel_t pwm_opts;

volatile uint32_t MS_Timer = 0;
void SysTick_Handler(void) {
	MS_Timer++;                // Increment global millisecond timer
}

void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOA) && (index == IMX_TWIBUSY_N)){
		if (ioport_get_pin_level(IMX_TWIBUSY_N)){
			iMX_use_TWI = true;
			ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_LOW);
		}
		else {
			iMX_use_TWI = false;
			ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_HIGH);
		}
	}
}

void setup_interupts(void){
	pmc_enable_periph_clk(ID_PIOA);

	pio_set_input(PIOA, IMX_TWIBUSY_N, PIO_PULLUP);
	pio_set_debounce_filter(PIOA,  IMX_TWIBUSY_N, 20);
	pio_handler_set(PIOA, ID_PIOA, IMX_TWIBUSY_N, PIO_IT_EDGE, pin_edge_handler);
	pio_enable_interrupt(PIOA, IMX_TWIBUSY_N);
	NVIC_EnableIRQ(PIOA_IRQn);
}

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
	
	for(int i=0; i < 10; i++)
	adc_value += adc_get_channel_value(ADC,  (enum adc_channel_num_t)15);
	adc_value /= 10;
	internalTemp = uint32_t(adc_value);
	
	
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

int XO3_refresh (int state)
{
	uint32_t  Timeout = MS_Timer + 1000;
	bool lowStepDone = false;
	while (MS_Timer == 0){
		asm("nop");
	}
	if (state == 0){
		while (1){
			if ((int32_t)((int32_t)MS_Timer - (int32_t)Timeout) >= 0) { //Timed execution
				ioport_set_pin_level(XO3_REFRESH, IOPORT_PIN_LEVEL_LOW);
				ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_HIGH);
				return 0;
			}
		}
	}
	if (state == 1){
		while (1){
			if ((int32_t)((int32_t)MS_Timer - (int32_t)Timeout) >= 0) { //Timed execution
				ioport_set_pin_level(XO3_REFRESH, IOPORT_PIN_LEVEL_HIGH);
				ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_LOW);
				return 1;
			}
		}
	}
	if (state == 2){
		while (1){
			if (((int32_t)((int32_t)MS_Timer - (int32_t)Timeout) >= 0) && (lowStepDone == false)) { //Timed execution
				ioport_set_pin_level(XO3_REFRESH, IOPORT_PIN_LEVEL_LOW);
				ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_HIGH);
				Timeout += 1000;
				lowStepDone = true;
			}
			
			if (((int32_t)((int32_t)MS_Timer - (int32_t)Timeout) >= 0) && (lowStepDone == true)) { //Timed execution
				ioport_set_pin_level(XO3_REFRESH, IOPORT_PIN_LEVEL_HIGH);
				ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_LOW);
				return 2;
			}
		}
	}
}

/* ----------------------------------------- ADC SP End --- */

void SPIdataBlock(void){
	// Voltages
// 	XO3_WriteByte(sam_voltage_soc + sam_offset, voltages[0]);
// 	XO3_WriteByte(sam_voltage_arm + sam_offset, voltages[1]);
// 	XO3_WriteByte(sam_voltage_ddr + sam_offset, voltages[2]);
// 	XO3_WriteByte(sam_voltage_v25 + sam_offset, voltages[3]);
// 	XO3_WriteByte(sam_voltage_v1 + sam_offset, voltages[4]);
// 	XO3_WriteByte(sam_voltage_v11 + sam_offset, voltages[5]);
// 	XO3_WriteByte(sam_voltage_vcore + sam_offset, voltages[6]);
// 	XO3_WriteByte(sam_voltage_v15 + sam_offset, voltages[7]);
// 	XO3_WriteByte(sam_voltage_v33 + sam_offset, voltages[8]);
// 	XO3_WriteByte(sam_voltage_v5 + sam_offset, voltages[9]);
// 	XO3_WriteByte(sam_voltage_v3 + sam_offset, voltages[10]);
// 	XO3_WriteByte(sam_voltage_v28 + sam_offset, voltages[11]);
	XO3_WriteByte(sam_voltage_soc + sam_offset, uint32_t(voltagesnorm[0]));
	XO3_WriteByte(sam_voltage_arm + sam_offset, uint32_t(voltagesnorm[1]));
	XO3_WriteByte(sam_voltage_ddr + sam_offset, uint32_t(voltagesnorm[2]));
	XO3_WriteByte(sam_voltage_v25 + sam_offset, uint32_t(voltagesnorm[3]));
	XO3_WriteByte(sam_voltage_v1 + sam_offset, uint32_t(voltagesnorm[4]));
	XO3_WriteByte(sam_voltage_v11 + sam_offset, uint32_t(voltagesnorm[5]));
	XO3_WriteByte(sam_voltage_vcore + sam_offset, uint32_t(voltagesnorm[6]));
	XO3_WriteByte(sam_voltage_v15 + sam_offset, uint32_t(voltagesnorm[7]));
	XO3_WriteByte(sam_voltage_v33 + sam_offset, uint32_t(voltagesnorm[8]));
	XO3_WriteByte(sam_voltage_v5 + sam_offset, uint32_t(voltagesnorm[9]));
	XO3_WriteByte(sam_voltage_v3 + sam_offset, uint32_t(voltagesnorm[10]));
	XO3_WriteByte(sam_voltage_v28 + sam_offset, uint32_t(voltagesnorm[11]));

	// Temperatures
	XO3_WriteByte(sam_temp_Buck + sam_offset, uint32_t(buck2tempnorm));
	XO3_WriteByte(sam_temp_MCU + sam_offset, internalTemp);
	//XO3_WriteByte(sam_temp_MCU, xxx);
}

void TWIdataBlock(void){
	if (iMX_use_TWI){ // Stoooop!
		XO3_WriteByte(sam_user_gp3 + sam_offset, 0x12C1DEAD);
		return;
	}
	else { // All right, TWI free. Read TWI regs and call XO3_WriteByte to write regs on FPGA
		XO3_WriteByte(sam_user_gp3 + sam_offset, 0x00000000);
		int status;
		uint32_t mac1;
		status = twiFpgaWrite(0xA0, 1, 1, 0xFA, &mac1, i2c1); //sam_user_gp3
	}
}

void checkInterruptIMX6(void){
	if (ioport_get_pin_level(IMX_TWIBUSY_N)){
		iMX_use_TWI = false;
		ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_HIGH); // All right, TWI free
	}
	else {
		iMX_use_TWI = true;
		ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_LOW); // Stop TWI, iMX6 request the bus
	}
}

int main (void)
{
	/* Insert system clock initialization code here*/
	sysclk_init();
	board_init();
	
	SysTick_Config(F_CPU/1000);
	uint32_t  Timeout = MS_Timer + 1000;
	
#ifdef ENABLE_IMX_TWI_INTERRUPT
	setup_interupts();
#endif
#ifdef DEBUG	
	XO3_refresh(2);
 	for (uint32_t i = 0; i < 0xffff; i++){
 		asm("nop");
 	}
#endif
	adc_start(ADC);
	adc_enable_ts(ADC);
	/* Insert application code here, after the board has been initialized. */
	
	spi_flags_t spi_flags = SPI_MODE_0;
	board_spi_select_id_t spi_select_id = 0;
	struct spi_device device = {
		.id = 0
	};
	// ------------- Enable SPI
	spi_master_init(MYSPI);
	spi_master_setup_device(MYSPI, &device, spi_flags,	SPI_CLOCK_SPEED, spi_select_id);
	spi_enable(MYSPI);
	spi_enable_clock(MYSPI);
	uint32_t vers;
	XO3_Read(regfile_fw_version + regfile_offset, &vers);
	
	XO3_WriteByte(sam_mcufw_build_version + sam_offset, _build_version);
	XO3_WriteByte(sam_mcufw_build_time + sam_offset, _build_time);
	XO3_WriteByte(sam_mcufw_build_date + sam_offset, _build_date);
	
	XO3_Read(sam_mcufw_build_version + sam_offset, &vers);
	readADCnormalized(); // Drop first read
	
	// PWM
	pwm_clock_t pwm_clock_opts = {
		.ul_clka = 5000000, //10Khz frequency = .1 ms steps
		.ul_clkb = 0,
		.ul_mck =  sysclk_get_main_hz() //main clock speed is 240Mhz!, not 120mhz
	};
	pwm_opts.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_opts.ul_period = 100; //20ms period
	pwm_opts.ul_duty = 0;
	pwm_opts.channel = PWM_CHANNEL_0;
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_disable(PWM, PWM_CHANNEL_0);
	pwm_init( PWM, &pwm_clock_opts );
	pwm_channel_init( PWM, &pwm_opts );
	pwm_channel_enable( PWM, PWM_CHANNEL_0 );
	// ---

	while (1) {
		checkInterruptIMX6();
		if ((int32_t)((int32_t)MS_Timer - (int32_t)Timeout) >= 0) { //Timed execution
			Timeout += 1000;  // Repeat this timeout in 1000 milliseconds
			readADCnormalized();
			SPIdataBlock();
			TWIdataBlock();
			ioport_toggle_pin_level(PIN_LEDK8);
			uint32_t duty;
			duty += 5;
			if (duty > 70) duty = 0;
			pwm_channel_update_duty( PWM, &pwm_opts, duty );
// 			ioport_toggle_pin_level(I2C1_SDA);
// 			ioport_toggle_pin_level(I2C1_SCL);


			//MS_Timer
			XO3_WriteByte(sam_user_gp0 + sam_offset, MS_Timer);
			XO3_WriteByte(sam_user_gp1 + sam_offset, 0x1);
			
		}
		//ioport_set_pin_level(XO3_REFRESH, IOPORT_PIN_LEVEL_HIGH);
		//XO3_WriteByte(0x00000800, 0xF);
		//delay_ms(100);
		//XO3_WriteByte(0x00000800, 0x0);
		//spi_write(SPI_MASTER, 0xf, 0, 1);
		//send_spi(0xF1); // Farlocca
		//delay_ms(1000);
		// 		twiFpgaWrite(0xA2, 1, 1, 0xFB, &mac2, i2c1);
// 		twiFpgaWrite(0xA0, 1, 1, 0xFE, &mac5, i2c1);
// 		twiFpgaWrite(0xA0, 1, 1, 0xFF, &mac6, i2c1);
		
		uint32_t _build_low, _build_high;
		XO3_WriteByte(regfile_fw_version + regfile_offset, _build_low);
		XO3_WriteByte(regfile_fw_build_high + regfile_offset, _build_high);
		XO3_WriteByte(regfile_pll_reset + regfile_offset, 0x00000000);
		uint32_t dato;
		XO3_Read(regfile_pll_reset + regfile_offset, &dato);
		//XO3_Read(0x00000008, &dato8);
		
		//XO3_Read(regfile_user_reg0, &dato);
		ioport_toggle_pin_level(PIO_PB10_IDX);	
	}

}
