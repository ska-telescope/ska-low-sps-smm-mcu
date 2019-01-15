/*
 * fram.h
 *
 * Sanitas EG - SKA Management Board
 *
 * Created: 09/01/2019 13:37:19 ~ Luca Schettini
 *
 * Copyright (c) 2017-2018 Sanitas EG srl.  All right reserved.
 *
 */ 


#ifndef FRAM_H_
#define FRAM_H_

// All registers are 32bit spaced. The size in comment refers to the shadow TWI register

#define fram_ADT7408_1_capability					0x000000000 //R  - 16 bit
#define fram_ADT7408_1_configuration				0x000000004 //RW - 16 bit
#define fram_ADT7408_1_alarm_temp_up_bound_trip		0x000000008 //RW - 16 bit
#define fram_ADT7408_1_alarm_temp_low_bound_trip	0x00000000C //RW - 16 bit
#define fram_ADT7408_1_critical_temp_trip			0x000000010 //RW - 16 bit
#define fram_ADT7408_1_temp_val						0x000000014 //RW - 16 bit

#define fram_ADT7408_2_capability					0x000000018 //R  - 16 bit
#define fram_ADT7408_2_configuration				0x00000001C //RW - 16 bit
#define fram_ADT7408_2_alarm_temp_up_bound_trip		0x000000020 //RW - 16 bit
#define fram_ADT7408_2_alarm_temp_low_bound_trip	0x000000024 //RW - 16 bit
#define fram_ADT7408_2_critical_temp_trip			0x000000028 //RW - 16 bit
#define fram_ADT7408_2_temp_val						0x00000002C //RW - 16 bit

#define fram_LTC4281_control_1						0x000000030 //RW - 8 bit
#define fram_LTC4281_control_2						0x000000034 //RW - 8 bit
#define fram_LTC4281_alert_1						0x000000038 //RW - 8 bit
#define fram_LTC4281_alert_2						0x00000003C //RW - 8 bit
#define fram_LTC4281_fault_log						0x000000040 //RW - 8 bit
#define fram_LTC4281_ADC_alert_log					0x000000044 //RW - 8 bit
#define fram_LTC4281_FET_bad_fault_time				0x000000048 //RW - 8 bit
#define fram_LTC4281_GPIO_config					0x00000004C //RW - 8 bit
#define fram_LTC4281_VGPIO_Alarm_MIN				0x000000050 //RW - 8 bit
#define fram_LTC4281_VGPIO_Alarm_MAX				0x000000054 //RW - 8 bit
#define fram_LTC4281_VSOURCE_Alarm_MIN				0x000000058 //RW - 8 bit
#define fram_LTC4281_VSOURCE_Alarm_MAX				0x00000005C //RW - 8 bit
#define fram_LTC4281_VSENSE_Alarm_MIN				0x000000060 //RW - 8 bit
#define fram_LTC4281_VSENSE_Alarm_MAX				0x000000064 //RW - 8 bit
#define fram_LTC4281_POWER_Alarm_MIN				0x000000068 //RW - 8 bit
#define fram_LTC4281_POWER_Alarm_MAX				0x00000006C //RW - 8 bit
#define fram_LTC4281_clock_divider					0x000000070 //RW - 8 bit
#define fram_LTC4281_ILIM_Adjust					0x000000074 //RW - 8 bit
#define fram_LTC4281_energy_0						0x000000078 //RW - 8 bit
#define fram_LTC4281_energy_1						0x00000007C //RW - 8 bit
#define fram_LTC4281_energy_2						0x000000080 //RW - 8 bit
#define fram_LTC4281_energy_3						0x000000084 //RW - 8 bit
#define fram_LTC4281_energy_4						0x000000088 //RW - 8 bit
#define fram_LTC4281_energy_5						0x00000008C //RW - 8 bit
#define fram_LTC4281_TIME_counter_0					0x000000090 //RW - 8 bit
#define fram_LTC4281_TIME_counter_1					0x000000094 //RW - 8 bit
#define fram_LTC4281_TIME_counter_2					0x000000098 //RW - 8 bit
#define fram_LTC4281_TIME_counter_3					0x00000009C //RW - 8 bit
#define fram_LTC4281_Alert_control					0x0000000A0 //RW - 8 bit
#define fram_LTC4281_ADC_control					0x0000000A4 //RW - 8 bit
#define fram_LTC4281_status_0						0x0000000A8 //R  - 8 bit
#define fram_LTC4281_status_1						0x0000000AC //R  - 8 bit
#define fram_LTC4281_VGPIO_msb						0x0000000B0 //RW - 8 bit
#define fram_LTC4281_VGPIO_lsb						0x0000000B4 //RW - 8 bit
#define fram_LTC4281_VGPIO_MIN_msb					0x0000000B8 //RW - 8 bit
#define fram_LTC4281_VGPIO_MIN_lsb 					0x0000000BC //RW - 8 bit
#define fram_LTC4281_VGPIO_MAX_msb					0x0000000C0 //RW - 8 bit
#define fram_LTC4281_VGPIO_MAX_lsb					0x0000000C4 //RW - 8 bit
#define fram_LTC4281_VSOURCE_msb					0x0000000C8 //RW - 8 bit
#define fram_LTC4281_VSOURCE_lsb					0x0000000CC //RW - 8 bit
#define fram_LTC4281_VSOURCE_MIN_msb				0x0000000D0 //RW - 8 bit
#define fram_LTC4281_VSOURCE_MIN_lsb				0x0000000D4 //RW - 8 bit
#define fram_LTC4281_VSOURCE_MAX_msb				0x0000000D8 //RW - 8 bit
#define fram_LTC4281_VSOURCE_MAX_lsb				0x0000000DC //RW - 8 bit
#define fram_LTC4281_VSENSE_msb						0x0000000E0 //RW - 8 bit
#define fram_LTC4281_VSENSE_lsb						0x0000000E4 //RW - 8 bit
#define fram_LTC4281_VSENSE_MIN_msb					0x0000000E8 //RW - 8 bit
#define fram_LTC4281_VSENSE_MIN_lsb					0x0000000EC //RW - 8 bit
#define fram_LTC4281_VSENSE_MAX_msb					0x0000000F0 //RW - 8 bit
#define fram_LTC4281_VSENSE_MAX_lsb					0x0000000F4 //RW - 8 bit
#define fram_LTC4281_POWER_msb						0x0000000F8 //RW - 8 bit
#define fram_LTC4281_POWER_lsb						0x0000000FC //RW - 8 bit
#define fram_LTC4281_POWER_MIN_msb					0x000000100 //RW - 8 bit
#define fram_LTC4281_POWER_MIN_lsb					0x000000104 //RW - 8 bit
#define fram_LTC4281_POWER_MAX_msb					0x000000108 //RW - 8 bit
#define fram_LTC4281_POWER_MAX_lsb					0x00000010C //RW - 8 bit

#define fram_LTC3676_BUCK1							0x000000110 //RW - 8 bit
#define fram_LTC3676_BUCK2							0x000000114 //RW - 8 bit
#define fram_LTC3676_BUCK3							0x000000118 //RW - 8 bit
#define fram_LTC3676_BUCK4							0x00000011C //RW - 8 bit
#define fram_LTC3676_LDOA							0x000000120 //RW - 8 bit
#define fram_LTC3676_LDOB							0x000000124 //RW - 8 bit
#define fram_LTC3676_SQD1							0x000000128 //RW - 8 bit
#define fram_LTC3676_SQD2							0x00000012C //RW - 8 bit
#define fram_LTC3676_CNTRL							0x000000130 //RW - 8 bit
#define fram_LTC3676_DVB1A							0x000000134 //RW - 8 bit
#define fram_LTC3676_DVB1B							0x000000138 //RW - 8 bit
#define fram_LTC3676_DVB2A							0x00000013C //RW - 8 bit
#define fram_LTC3676_DVB2B							0x000000140 //RW - 8 bit
#define fram_LTC3676_DVB3A							0x000000144 //RW - 8 bit
#define fram_LTC3676_DVB3B							0x000000148 //RW - 8 bit
#define fram_LTC3676_DVB4A							0x00000014C //RW - 8 bit
#define fram_LTC3676_DVB4B							0x000000150 //RW - 8 bit
#define fram_LTC3676_MSKIRQ							0x000000154 //RW - 8 bit
#define fram_LTC3676_MSKPG							0x000000158 //RW - 8 bit
#define fram_LTC3676_USER							0x00000015C //RW - 8 bit
#define fram_LTC3676_HRESET							0x000000160 //R  - 8 bit
#define fram_LTC3676_CLIARIRQ						0x000000164 //R  - 8 bit
#define fram_LTC3676_IRQSTAT						0x000000168 //R  - 8 bit
#define fram_LTC3676_PGSTATL						0x00000016C //R  - 8 bit
#define fram_LTC3676_PGSTATRT						0x000000170 //R  - 8 bit

#endif /* FRAM_H_ */