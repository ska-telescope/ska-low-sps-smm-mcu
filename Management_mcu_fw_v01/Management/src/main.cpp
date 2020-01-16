/*
 * Sanitas EG - SKA Management Board
 * 
 * V1.0 - 20/03/18 ~ Luca Schettini
 * 
 * Copyright (c) 2017-2018 Sanitas EG srl.  All right reserved.
 * 
 */

#include <asf.h>
#include <string.h>
#include "conf_board.h"
#include <math.h>

#include "spi_master.h"
#include <SpiRouter.h>
#include "build_def.h"
#include <TwiFpga.h>
//#include "i2c.h"
#include <onewire.h>

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
uint8_t twi_block = 0x1;

const uint32_t _build_version = 0xdeb00020;
const uint32_t _build_date = ((((BUILD_YEAR_CH0 & 0xFF - 0x30) * 0x10 ) + ((BUILD_YEAR_CH1 & 0xFF - 0x30)) << 24) | (((BUILD_YEAR_CH2 & 0xFF - 0x30) * 0x10 ) + ((BUILD_YEAR_CH3 & 0xFF - 0x30)) << 16) | (((BUILD_MONTH_CH0 & 0xFF - 0x30) * 0x10 ) + ((BUILD_MONTH_CH1 & 0xFF - 0x30)) << 8) | (((BUILD_DAY_CH0 & 0xFF - 0x30) * 0x10 ) + ((BUILD_DAY_CH1 & 0xFF - 0x30))));
const uint32_t _build_time = (0x00 << 24 | (((__TIME__[0] & 0xFF - 0x30) * 0x10 ) + ((__TIME__[1] & 0xFF - 0x30)) << 16) | (((__TIME__[3] & 0xFF - 0x30) * 0x10 ) + ((__TIME__[4] & 0xFF - 0x30)) << 8) | (((__TIME__[6] & 0xFF - 0x30) * 0x10 ) + ((__TIME__[7] & 0xFF - 0x30))));

// ----- SPI -------
#define SPI_CLOCK_SPEED		8000000UL
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
uint32_t duty;

pwm_channel_t pwm_opts;

uint16_t TPMisOn[8];

volatile uint32_t MS_Timer = 0;
void SysTick_Handler(void) {
	MS_Timer++;                // Increment global millisecond timer
}

void fan_setup(void){
	uint32_t retvalue;
	uint16_t address;
	uint32_t fan_speed = 0x33;
	
	twiFpgaWrite(0x58, 2, 1, 0x6800, &retvalue, i2c2);
	twiFpgaWrite(0x58, 2, 1, 0x6900, &retvalue, i2c2);
	twiFpgaWrite(0x58, 2, 1, 0x4355, &retvalue, i2c2);
	
	twiFpgaWrite(0x5E, 2, 1, 0x6800, &retvalue, i2c2);
	twiFpgaWrite(0x5E, 2, 1, 0x6900, &retvalue, i2c2);

	for (uint16_t i = 0x32; i < 0x36; i++){
		address = (i << 8) + (uint8_t)fan_speed;
		
		twiFpgaWrite(0x58, 2, 1, address, &retvalue, i2c2);
		twiFpgaWrite(0x5E, 2, 1, address, &retvalue, i2c2);
	}
	
	fan_speed = 0x03ff0000 + ((uint8_t)fan_speed << 8) + (uint8_t)fan_speed;
	
	XO3_Write(fram_FAN_PWM + fram_offset, fan_speed);	
	
}

void fan_PWM(void){
	uint32_t retvalue, fan_speed;
	uint16_t cmd0, cmd1;
	int oneTPMisON0 = 0;
	int oneTPMisON1 = 0;
	uint32_t tachl, tachm;
	bool automode = false;
	
	XO3_Read(fram_FAN_PWM + fram_offset, &fan_speed);
	
	for (int i = 0; i< 4; i++) if(TPMisOn[i] & 0x800) oneTPMisON0++;
	for (int i = 4; i< 8; i++) if(TPMisOn[i] & 0x800) oneTPMisON1++;
	
	if ((fan_speed & 0x2000000)){
		fan_speed = (fan_speed & ~0x00ff) + (0x33 * oneTPMisON0) + 0x33;
		automode = true;
	}
	
	if ((fan_speed & 0x2000000)){
		fan_speed = (fan_speed & ~0xff00) + ((0x33 * oneTPMisON1) << 8) + 0x3300;
		automode = true;
	} 
	
	if (automode) XO3_Write(fram_FAN_PWM + fram_offset, fan_speed);
	
	for (uint16_t i = 0x32; i < 0x36; i++){
		cmd0 = (i << 8) + (uint8_t)fan_speed;
		cmd1 = (i << 8) + (uint8_t)(fan_speed >> 8);
		
		twiFpgaWrite(0x58, 2, 1, cmd0, &retvalue, i2c2);
		twiFpgaWrite(0x5E, 2, 1, cmd1, &retvalue, i2c2);
	}
	
	tachl = twiFpgaRead8(0x58, 0x2A, i2c2);
	tachm = twiFpgaRead8(0x58, 0x2B, i2c2);
	tachl = tachl + (tachm << 8);
	//tachl = 5400000 / tachl;	
	XO3_Write(fram_FAN1_TACH + fram_offset, tachl);
	
	tachl = twiFpgaRead8(0x58, 0x2C, i2c2);
	tachm = twiFpgaRead8(0x58, 0x2D, i2c2);
	tachl = tachl + (tachm << 8);
	//tachl = 5400000 / tachl;	
	XO3_Write(fram_FAN2_TACH + fram_offset, tachl);
	
	tachl = twiFpgaRead8(0x5E, 0x2A, i2c2);
	tachm = twiFpgaRead8(0x5E, 0x2B, i2c2);
	tachl = tachl + (tachm << 8);
	//tachl = 5400000 / tachl;
	XO3_Write(fram_FAN3_TACH + fram_offset, tachl);
	
	tachl = twiFpgaRead8(0x5E, 0x2C, i2c2);
	tachm = twiFpgaRead8(0x5E, 0x2D, i2c2);
	tachl = tachl + (tachm << 8);
	//tachl = 5400000 / tachl;
	XO3_Write(fram_FAN4_TACH + fram_offset, tachl);
	
}

void TPM_present(void){
	uint32_t tpmpresent, retvalue;
	uint8_t tpmled0 = 0;
	uint8_t tpmled1 = 0;
	int status;
	XO3_Read(regfile_present_tpm + regfile_offset, &tpmpresent);
	
	if (tpmpresent & 0x1) tpmled0 += 0x1;
	if (tpmpresent & 0x2) tpmled0 += 0x2;
	if (tpmpresent & 0x4) tpmled0 += 0x4;
	if (tpmpresent & 0x8) tpmled0 += 0x8;
	
	if (tpmpresent & 0x10) tpmled1 += 0x1;
	if (tpmpresent & 0x20) tpmled1 += 0x2;
	if (tpmpresent & 0x40) tpmled1 += 0x4;
	if (tpmpresent & 0x80) tpmled1 += 0x8;
	
	if (TPMisOn[0] & 0x800) tpmled0 = (tpmled0 & ~0x1) + 0x10;
	if (TPMisOn[1] & 0x800) tpmled0 = (tpmled0 & ~0x2) + 0x20;
	if (TPMisOn[2] & 0x800) tpmled0 = (tpmled0 & ~0x4) + 0x40;
	if (TPMisOn[3] & 0x800) tpmled0 = (tpmled0 & ~0x8) + 0x80;
	
	if (TPMisOn[4] & 0x800) tpmled1 = (tpmled1 & ~0x1) + 0x10;
	if (TPMisOn[5] & 0x800) tpmled1 = (tpmled1 & ~0x2) + 0x20;
	if (TPMisOn[6] & 0x800) tpmled1 = (tpmled1 & ~0x4) + 0x40;
	if (TPMisOn[7] & 0x800) tpmled1 = (tpmled1 & ~0x8) + 0x80;
	
	status = twiFpgaWrite(0x42, 1, 2, tpmled0, &retvalue, i2c4);
	status = twiFpgaWrite(0x40, 1, 2, tpmled1, &retvalue, i2c4);	
	
	asm("nop");
	
	
}

void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOA) && (index == PIO_PA27)){
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

	pio_set_input(PIOA, PIO_PA27, PIO_PULLUP);
	pio_set_debounce_filter(PIOA,  PIO_PA27, 20);
	pio_handler_set(PIOA, ID_PIOA, PIO_PA27, PIO_IT_EDGE, pin_edge_handler);
	pio_enable_interrupt(PIOA, PIO_PA27);
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
	XO3_Write(sam_voltage_soc + sam_offset, uint32_t(voltagesnorm[0]));
	XO3_Write(sam_voltage_arm + sam_offset, uint32_t(voltagesnorm[1]));
	XO3_Write(sam_voltage_ddr + sam_offset, uint32_t(voltagesnorm[2]));
	XO3_Write(sam_voltage_v25 + sam_offset, uint32_t(voltagesnorm[3]));
	XO3_Write(sam_voltage_v1 + sam_offset, uint32_t(voltagesnorm[4]));
	XO3_Write(sam_voltage_v11 + sam_offset, uint32_t(voltagesnorm[5]));
	XO3_Write(sam_voltage_vcore + sam_offset, uint32_t(voltagesnorm[6]));
	XO3_Write(sam_voltage_v15 + sam_offset, uint32_t(voltagesnorm[7]));
	XO3_Write(sam_voltage_v33 + sam_offset, uint32_t(voltagesnorm[8]));
	XO3_Write(sam_voltage_v5 + sam_offset, uint32_t(voltagesnorm[9]));
	XO3_Write(sam_voltage_v3 + sam_offset, uint32_t(voltagesnorm[10]));
	XO3_Write(sam_voltage_v28 + sam_offset, uint32_t(voltagesnorm[11]));

	// Temperatures
	XO3_Write(sam_temp_Buck + sam_offset, uint32_t(buck2tempnorm));
	XO3_Write(sam_temp_MCU + sam_offset, internalTemp);
	//XO3_WriteByte(sam_temp_MCU, xxx);
	
	XO3_Read(sam_user_gp2 + sam_offset, &duty); // 0 max - 90 slow/stop
	if (duty > 99) duty = 99;
	
}

bool checkInterruptIMX6(void){
	if (ioport_get_pin_level(IMX_TWIBUSY_N)){
		if (iMX_use_TWI) XO3_Write(sam_user_gp3 + sam_offset, 0x12CFFFFF);
		iMX_use_TWI = false;
		ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_HIGH); // All right, TWI free
		return false;
	}
	else {
		iMX_use_TWI = true;
		XO3_Write(sam_user_gp3 + sam_offset, 0x12C0DEAD);
		ioport_set_pin_level(PIN_LEDK7, IOPORT_PIN_LEVEL_LOW); // Stop TWI, iMX6 request the bus
		return true;
	}
}

void TWIdataBlock(void){
	int status;
	uint32_t retvalue = 0xffffffff;
	float voltage, amperage, power, powerc;
	
	if ((checkInterruptIMX6() == false) && (twi_block == 0x1)) { // All right, TWI free. Read TWI regs and call XO3_WriteByte to write regs on FPGA
		XO3_Write(sam_user_gp3 + sam_offset, 0x12C10000);

		// i2c1
		status = twiFpgaWrite(0x30, 1, 2, 0x05, &retvalue, i2c1); //temp_value 0x30
		XO3_Write(fram_ADT7408_M_1_temp_val + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x32, 1, 2, 0x05, &retvalue, i2c1); //temp_value 0x32
		XO3_Write(fram_ADT7408_M_2_temp_val + fram_offset, retvalue);	
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x88, 1, 1, 0x04, &retvalue, i2c1); //fault_log 0x88
		XO3_Write(fram_LTC4281_M_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x12, &retvalue, i2c1); //energy0 0x88
		XO3_Write(fram_LTC4281_M_energy_0 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x13, &retvalue, i2c1); //energy1 0x88
		XO3_Write(fram_LTC4281_M_energy_1 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x14, &retvalue, i2c1); //energy2 0x88
		XO3_Write(fram_LTC4281_M_energy_2 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x15, &retvalue, i2c1); //energy3 0x88
		XO3_Write(fram_LTC4281_M_energy_3 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x16, &retvalue, i2c1); //energy4 0x88
		XO3_Write(fram_LTC4281_M_energy_4 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x17, &retvalue, i2c1); //energy5 0x88
		XO3_Write(fram_LTC4281_M_energy_5 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x18, &retvalue, i2c1); //time_count0 0x88
		XO3_Write(fram_LTC4281_M_TIME_counter_0 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x19, &retvalue, i2c1); //time_count1 0x88
		XO3_Write(fram_LTC4281_M_TIME_counter_1 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x1A, &retvalue, i2c1); //time_count2 0x88
		XO3_Write(fram_LTC4281_M_TIME_counter_2 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x1B, &retvalue, i2c1); //time_count3 0x88
		XO3_Write(fram_LTC4281_M_TIME_counter_3 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x1E, &retvalue, i2c1); //status0 0x88
		XO3_Write(fram_LTC4281_M_status_0 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x1F, &retvalue, i2c1); //status1 0x88
		XO3_Write(fram_LTC4281_M_status_1 + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x34, &retvalue, i2c1); //vgpio_msb 0x88
		XO3_Write(fram_LTC4281_M_VGPIO_msb + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x35, &retvalue, i2c1); //vgpio_lsb 0x88
		XO3_Write(fram_LTC4281_M_VGPIO_lsb + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x3A, &retvalue, i2c1); //VSOURCE_msb 0x88
		XO3_Write(fram_LTC4281_M_VSOURCE_msb + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x3B, &retvalue, i2c1); //VSOURCE_lsb 0x88
		XO3_Write(fram_LTC4281_M_VSOURCE_lsb + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x40, &retvalue, i2c1); //VSENSE_msb 0x88
		XO3_Write(fram_LTC4281_M_VSENSE_msb + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x41, &retvalue, i2c1); //VSENSE_lsb 0x88
		XO3_Write(fram_LTC4281_M_VSENSE_lsb + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x46, &retvalue, i2c1); //POWER_msb 0x88
		XO3_Write(fram_LTC4281_M_POWER_msb + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x47, &retvalue, i2c1); //POWER_msb 0x88
		XO3_Write(fram_LTC4281_M_POWER_lsb + fram_offset, retvalue);
		
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x78, 1, 1, 0x13, &retvalue, i2c1); //MSKPG 0x78
		XO3_Write(fram_LTC3676_M_MSKPG + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x78, 1, 1, 0x15, &retvalue, i2c1); //IRQSTAT 0x78
		XO3_Write(fram_LTC3676_M_IRQSTAT + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x78, 1, 1, 0x17, &retvalue, i2c1); //PGSTATRT 0x78
		XO3_Write(fram_LTC3676_M_PGSTATRT + fram_offset, retvalue);
		
		twi_block = 0x2;
	}
	if ((checkInterruptIMX6() == false) && (twi_block == 0x2)) { // All right, TWI free. Read TWI regs and call XO3_WriteByte to write regs on FPGA
		XO3_Write(sam_user_gp3 + sam_offset, 0x12C20000);
				
		// TWI2 - Backplane
		fan_PWM();
		
		status = twiFpgaWrite(0x80, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_1_control + fram_offset, retvalue);
		TPMisOn[0] = retvalue;
		retvalue = 0xffffffff;		
		status = twiFpgaWrite(0x80, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_1_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;		
		status = twiFpgaWrite(0x80, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_1_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;		
		status = twiFpgaWrite(0x80, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_1_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;		
		status = twiFpgaWrite(0x80, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_1_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;		
		status = twiFpgaWrite(0x80, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_1_power + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x82, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_2_control + fram_offset, retvalue);
		TPMisOn[1] = retvalue;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x82, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_2_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x82, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_2_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x82, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_2_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x82, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_2_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x82, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_2_power + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x84, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_3_control + fram_offset, retvalue);
		TPMisOn[2] = retvalue;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x84, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_3_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x84, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_3_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x84, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_3_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x84, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_3_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x84, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_3_power + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x86, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_4_control + fram_offset, retvalue);
		TPMisOn[3] = retvalue;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x86, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_4_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x86, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_4_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x86, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_4_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x86, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_4_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x86, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_4_power + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x88, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_5_control + fram_offset, retvalue);
		TPMisOn[4] = retvalue;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_5_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_5_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_5_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_5_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x88, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_5_power + fram_offset, retvalue);
		retvalue = 0xffffffff;

		status = twiFpgaWrite(0x8A, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_6_control + fram_offset, retvalue);
		TPMisOn[5] = retvalue;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8A, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_6_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8A, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_6_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8A, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_6_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8A, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_6_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8A, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_6_power + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x8C, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_7_control + fram_offset, retvalue);
		TPMisOn[6] = retvalue;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8C, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_7_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8C, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_7_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8C, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_7_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8C, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_7_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8C, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_7_power + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x8E, 1, 2, 0x00, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_8_control + fram_offset, retvalue);
		TPMisOn[7] = retvalue;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8E, 1, 2, 0x02, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_8_alert + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8E, 1, 1, 0x04, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_8_fault_log + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8E, 1, 1, 0x11, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_8_ilim_adj + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8E, 1, 2, 0x3A, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_8_Vsource + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x8E, 1, 2, 0x46, &retvalue, i2c2);
		XO3_Write(fram_LTC4281_B_8_power + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		status = twiFpgaWrite(0x30, 1, 2, 0x05, &retvalue, i2c2); //temp_value 0x30
		XO3_Write(fram_ADT7408_B_1_temp_val + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0x32, 1, 2, 0x05, &retvalue, i2c2); //temp_value 0x32
		XO3_Write(fram_ADT7408_B_2_temp_val + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		twi_block = 0x3;
	}
		
	if ((checkInterruptIMX6() == false) && (twi_block == 0x3)) { // All right, TWI free. Read TWI regs and call XO3_WriteByte to write regs on FPGA	
		XO3_Write(sam_user_gp3 + sam_offset, 0x12C30000);
		
		// TWI3 - Power Supply		
		status = twiFpgaWrite(0xB0, 1, 2, 0x8b, &retvalue, i2c3);
		//voltage = uint16_t(retvalue) * pow(2,-9);
		XO3_Write(fram_PSU_0_vout + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB0, 1, 2, 0x8c, &retvalue, i2c3);
		XO3_Write(fram_PSU_0_iout + fram_offset, retvalue);
		//amperage = (uint16_t(retvalue) & 0x7ff) * pow(2,-3);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB0, 1, 2, 0x96, &retvalue, i2c3);
		//XO3_Write(fram_PSU_0_vout + fram_offset, retvalue);
		//power = (uint16_t(retvalue) & 0x7ff) * 2;
		//powerc = amperage * voltage;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB0, 1, 1, 0x7A, &retvalue, i2c3);
		XO3_Write(fram_PSU_0_status_vout + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB0, 1, 1, 0x7B, &retvalue, i2c3);
		XO3_Write(fram_PSU_0_status_iout + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB0, 1, 2, 0x90, &retvalue, i2c3);
		XO3_Write(fram_PSU_0_fan_speed + fram_offset, retvalue);
		retvalue = 0xffffffff;	
			
		status = twiFpgaWrite(0xB2, 1, 2, 0x8b, &retvalue, i2c3);
		//voltage = uint16_t(retvalue) * pow(2,-9);
		XO3_Write(fram_PSU_1_vout + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB2, 1, 2, 0x8c, &retvalue, i2c3);
		XO3_Write(fram_PSU_1_iout + fram_offset, retvalue);
		//amperage = (uint16_t(retvalue) & 0x7ff) * pow(2,-3);
		status = twiFpgaWrite(0xB2, 1, 2, 0x96, &retvalue, i2c3);
		retvalue = 0xffffffff;
		//XO3_Write(fram_PSU_1_vout + fram_offset, retvalue);
		//power = (uint16_t(retvalue) & 0x7ff) * 2;
		//powerc = amperage * voltage;
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB2, 1, 1, 0x7A, &retvalue, i2c3);
		XO3_Write(fram_PSU_1_status_vout + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB2, 1, 1, 0x7B, &retvalue, i2c3);
		XO3_Write(fram_PSU_1_status_iout + fram_offset, retvalue);
		retvalue = 0xffffffff;
		status = twiFpgaWrite(0xB2, 1, 2, 0x90, &retvalue, i2c3);
		XO3_Write(fram_PSU_1_fan_speed + fram_offset, retvalue);
		retvalue = 0xffffffff;
		
		
		twi_block = 0x4; // return
		
	}
	if ((checkInterruptIMX6() == false) && (twi_block == 0x4)) {
// 		static int io = 0;
// 				
// 		int num = pow(2,io);
// 		twiFpgaWrite(0x40, 1, 2, num, &retvalue, i2c4);
// 		twiFpgaWrite(0x42, 1, 2, num, &retvalue, i2c4);
// 		io++;
// 		if (io == 8) io = 0;
		
		TPM_present();
		
		twi_block = 0x1; // return
	}
	
	
}

int main (void)
{
	/* Insert system clock initialization code here*/
	sysclk_init();
	board_init();

	SysTick_Config(F_CPU/1000);
	uint32_t  Timeout = MS_Timer + 1000;
	uint32_t pooling_time = 0;
	
#ifdef ENABLE_IMX_TWI_INTERRUPT
	setup_interupts();
#endif
#ifdef DEBUG	
	XO3_refresh(2);
 	for (uint32_t i = 0; i < 0xfffff; i++){
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
	twiFpgaWrite(0x40, 1, 2, 0xf, &vers, i2c4);
	twiFpgaWrite(0x42, 1, 2, 0xf, &vers, i2c4);
	XO3_Read(regfile_fw_version + regfile_offset, &vers);
	XO3_Write(sam_mcufw_build_version + sam_offset, _build_version);
	XO3_Write(sam_mcufw_build_time + sam_offset, _build_time);
	XO3_Write(sam_mcufw_build_date + sam_offset, _build_date);
	XO3_Write(sam_user_gp2 + sam_offset, 0x0); // Initialize fan speed to max
	XO3_Read(regfile_sam_pooltime + regfile_offset, &pooling_time); // ms
	Timeout = MS_Timer + pooling_time;
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
	fan_setup();
//  	OneWireSetupClock(0xF, true);
  	OneWireSelectCS(TPM1OW);
	twiFpgaWrite(0x40, 1, 2, 0xf0, &vers, i2c4);
	twiFpgaWrite(0x42, 1, 2, 0xf0, &vers, i2c4);
	
//  	twiFpgaWrite(0x80, 3, 2, 0x00bb00, &vers, i2c2);
//  	twiFpgaWrite(0x82, 3, 2, 0x00bb00, &vers, i2c2);

	//XO3_Write(fram_FAN_PWM + fram_offset, 0x00FFFFFF);	
	// ---
	while (1) {
		checkInterruptIMX6();
		
		SPIdataBlock();
		TWIdataBlock();
		
		if ((int32_t)((int32_t)MS_Timer - (int32_t)Timeout) >= 0) { //Timed execution
			Timeout += pooling_time;  // Repeat this as pooling_time
			readADCnormalized();

			ioport_toggle_pin_level(PIN_LEDK8);
// 			duty += 5;
// 			if (duty > 70) duty = 0;
			pwm_channel_update_duty( PWM, &pwm_opts, duty );
// 			ioport_toggle_pin_level(I2C1_SDA);
// 			ioport_toggle_pin_level(I2C1_SCL);


			//MS_Timer
// 			XO3_WriteByte(sam_user_gp0 + sam_offset, MS_Timer);
// 			XO3_WriteByte(sam_user_gp1 + sam_offset, 0x1);
// 			XO3_Read(regfile_sam_pooltime + regfile_offset, &pooling_time);			
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
		//XO3_WriteByte(regfile_fw_version + regfile_offset, _build_low);
		//XO3_WriteByte(fram_LTC4281_TIME_counter_0 + fram_offset, _build_high);
		//XO3_WriteByte(regfile_pll_reset + regfile_offset, 0x00000000);
		uint32_t dato;
		//XO3_Read(fram_LTC4281_TIME_counter_0 + fram_offset, &dato);
		XO3_Read(regfile_fw_version, &dato);	
		//XO3_Read(regfile_user_reg0, &dato);
		ioport_toggle_pin_level(PIO_PB10_IDX);
		XO3_Read(fram_PSU_0_vout + fram_offset, &dato);
		
// 		static int CS1WAct = 0x0;
// 		if (CS1WAct > 0x70) CS1WAct = 0x0;
		
		char onedata[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		int status[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		
		//OneWireSearch();

/*		if(!OneWireReset()){
			status[0] = OneWireWriteByte(0xF0);
// 			status[0] = OneWireWriteByte(0xCC);
// 			status[0] = OneWireWriteByte(0x44);
// 			status[0] = OneWireWriteByte(0xCC);
// 			status[0] = OneWireWriteByte(0xBE);
			//status = OneWireWriteByte(0xBE);
			//status = OneWireWriteByte(0x28);
			//OneWireReadByte(&onedata[0]);
 			//OneWireWriteByte(0x44);
 			for (int i = 0; i < 16; i++){
				 status[i] = OneWireReadByte(&onedata[i]);
				 if (status[i]) break;
			 }
		}

		asm("nop");*/
		
// 		CS1WAct = CS1WAct + 0x10;
// 		OneWireSelectCS(CS1W(CS1WAct));
	}

}
