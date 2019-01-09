/*
 * fram.h
 *
 * Created: 09/01/2019 13:37:19
 *  Author: luca
 */ 


#ifndef FRAM_H_
#define FRAM_H_

#define fram_ADT7408_1_capability					0x00000000 //R  - 16 bit
#define fram_ADT7408_1_configuration				0x00000010 //RW - 16 bit
#define fram_ADT7408_1_alarm_temp_up_bound_trip		0x00000020 //RW - 16 bit
#define fram_ADT7408_1_alarm_temp_low_bound_trip	0x00000030 //RW - 16 bit
#define fram_ADT7408_1_critical_temp_trip			0x00000040 //RW - 16 bit
#define fram_ADT7408_1_temp_val						0x00000050 //RW - 16 bit

#define fram_ADT7408_2_capability					0x00000060 //R  - 16 bit
#define fram_ADT7408_2_configuration				0x00000070 //RW - 16 bit
#define fram_ADT7408_2_alarm_temp_up_bound_trip		0x00000080 //RW - 16 bit
#define fram_ADT7408_2_alarm_temp_low_bound_trip	0x00000090 //RW - 16 bit
#define fram_ADT7408_2_critical_temp_trip			0x00000100 //RW - 16 bit
#define fram_ADT7408_2_temp_val						0x00000110 //RW - 16 bit

#define fram_LTC4281_control_1						0x00000120 //RW - 8 bit
#define fram_LTC4281_control_2						0x00000128 //RW - 8 bit
#define fram_LTC4281_alert_1						0x00000136 //RW - 8 bit
#define fram_LTC4281_alert_2						0x00000144 //RW - 8 bit
#define fram_LTC4281_fault_log						0x00000152 //RW - 8 bit
#define fram_LTC4281_ADC_alert_log					0x00000160 //RW - 8 bit
#define fram_LTC4281_FET_bad_fault_time				0x00000168 //RW - 8 bit
#define fram_LTC4281_GPIO_config					0x00000176 //RW - 8 bit
#define fram_LTC4281_VGPIO_Alarm_MIN				0x00000184 //RW - 8 bit
#define fram_LTC4281_VGPIO_Alarm_MAX				0x00000192 //RW - 8 bit
#define fram_LTC4281_VSOURCE_Alarm_MIN				0x00000200 //RW - 8 bit
#define fram_LTC4281_VSOURCE_Alarm_MAX				0x00000208 //RW - 8 bit
#define fram_LTC4281_VSENSE_Alarm_MIN				0x00000216 //RW - 8 bit
#define fram_LTC4281_VSENSE_Alarm_MAX				0x00000224 //RW - 8 bit
#define fram_LTC4281_POWER_Alarm_MIN				0x00000232 //RW - 8 bit
#define fram_LTC4281_POWER_Alarm_MAX				0x00000240 //RW - 8 bit
#define fram_LTC4281_clock_divider					0x00000248 //RW - 8 bit
#define fram_LTC4281_ILIM_Adjust					0x00000256 //RW - 8 bit
#define fram_LTC4281_energy_0						0x00000264 //RW - 8 bit
#define fram_LTC4281_energy_1						0x00000272 //RW - 8 bit
#define fram_LTC4281_energy_2						0x00000280 //RW - 8 bit
#define fram_LTC4281_energy_3						0x00000288 //RW - 8 bit
#define fram_LTC4281_energy_4						0x00000296 //RW - 8 bit
#define fram_LTC4281_energy_5						0x00000304 //RW - 8 bit
#define fram_LTC4281_TIME_counter_0					0x00000312 //RW - 8 bit
#define fram_LTC4281_TIME_counter_1					0x00000320 //RW - 8 bit
#define fram_LTC4281_TIME_counter_2					0x00000328 //RW - 8 bit
#define fram_LTC4281_TIME_counter_3					0x00000336 //RW - 8 bit
#define fram_LTC4281_Alert_control					0x00000344 //RW - 8 bit
#define fram_LTC4281_ADC_control					0x00000352 //RW - 8 bit
#define fram_LTC4281_status_0						0x00000360 //R  - 8 bit
#define fram_LTC4281_status_1						0x00000368 //R  - 8 bit
#define fram_LTC4281_VGPIO_msb						0x00000376 //RW - 8 bit
#define fram_LTC4281_VGPIO_lsb						0x00000384 //RW - 8 bit
#define fram_LTC4281_VGPIO_MIN_msb					0x00000392 //RW - 8 bit
#define fram_LTC4281_VGPIO_MIN_lsb 					0x00000400 //RW - 8 bit
#define fram_LTC4281_VGPIO_MAX_msb					0x00000408 //RW - 8 bit
#define fram_LTC4281_VGPIO_MAX_lsb					0x00000416 //RW - 8 bit
#define fram_LTC4281_VSOURCE_msb					0x00000424 //RW - 8 bit
#define fram_LTC4281_VSOURCE_lsb					0x00000432 //RW - 8 bit
#define fram_LTC4281_VSOURCE_MIN_msb				0x00000440 //RW - 8 bit
#define fram_LTC4281_VSOURCE_MIN_lsb				0x00000448 //RW - 8 bit
#define fram_LTC4281_VSOURCE_MAX_msb				0x00000456 //RW - 8 bit
#define fram_LTC4281_VSOURCE_MAX_lsb				0x00000464 //RW - 8 bit
#define fram_LTC4281_VSENSE_msb						0x00000472 //RW - 8 bit
#define fram_LTC4281_VSENSE_lsb						0x00000480 //RW - 8 bit
#define fram_LTC4281_VSENSE_MIN_msb					0x00000488 //RW - 8 bit
#define fram_LTC4281_VSENSE_MIN_lsb					0x00000496 //RW - 8 bit
#define fram_LTC4281_VSENSE_MAX_msb					0x00000504 //RW - 8 bit
#define fram_LTC4281_VSENSE_MAX_lsb					0x00000512 //RW - 8 bit
#define fram_LTC4281_POWER_msb						0x00000520 //RW - 8 bit
#define fram_LTC4281_POWER_lsb						0x00000528 //RW - 8 bit
#define fram_LTC4281_POWER_MIN_msb					0x00000536 //RW - 8 bit
#define fram_LTC4281_POWER_MIN_lsb					0x00000544 //RW - 8 bit
#define fram_LTC4281_POWER_MAX_msb					0x00000552 //RW - 8 bit
#define fram_LTC4281_POWER_MAX_lsb					0x00000560 //RW - 8 bit

#define fram_LTC3676_BUCK1							0x00000568 //RW - 8 bit
#define fram_LTC3676_BUCK2							0x00000576 //RW - 8 bit
#define fram_LTC3676_BUCK3							0x00000584 //RW - 8 bit
#define fram_LTC3676_BUCK4							0x00000592 //RW - 8 bit
#define fram_LTC3676_LDOA							0x00000600 //RW - 8 bit
#define fram_LTC3676_LDOB							0x00000608 //RW - 8 bit
#define fram_LTC3676_SQD1							0x00000616 //RW - 8 bit
#define fram_LTC3676_SQD2							0x00000624 //RW - 8 bit
#define fram_LTC3676_CNTRL							0x00000632 //RW - 8 bit
#define fram_LTC3676_DVB1A							0x00000640 //RW - 8 bit
#define fram_LTC3676_DVB1B							0x00000648 //RW - 8 bit
#define fram_LTC3676_DVB2A							0x00000656 //RW - 8 bit
#define fram_LTC3676_DVB2B							0x00000664 //RW - 8 bit
#define fram_LTC3676_DVB3A							0x00000672 //RW - 8 bit
#define fram_LTC3676_DVB3B							0x00000680 //RW - 8 bit
#define fram_LTC3676_DVB4A							0x00000688 //RW - 8 bit
#define fram_LTC3676_DVB4B							0x00000696 //RW - 8 bit
#define fram_LTC3676_MSKIRQ							0x00000704 //RW - 8 bit
#define fram_LTC3676_MSKPG							0x00000712 //RW - 8 bit
#define fram_LTC3676_USER							0x00000720 //RW - 8 bit
#define fram_LTC3676_HRESET							0x00000728 //R  - 8 bit
#define fram_LTC3676_CLIARIRQ						0x00000736 //R  - 8 bit
#define fram_LTC3676_IRQSTAT						0x00000744 //R  - 8 bit
#define fram_LTC3676_PGSTATL						0x00000752 //R  - 8 bit
#define fram_LTC3676_PGSTATRT						0x00000760 //R  - 8 bit

#endif /* FRAM_H_ */