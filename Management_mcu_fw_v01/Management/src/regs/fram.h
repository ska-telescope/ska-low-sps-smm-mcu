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

// All registers are 32bit spaced. The size in comment refers to the shadow TWI register - MAX 0x200 - 0x400

// i2c1
#define fram_ADT7408_M_1_capability					0x000000000 //R  - 16 bit
#define fram_ADT7408_M_1_configuration				0x000000004 //RW - 16 bit
#define fram_ADT7408_M_1_alarm_temp_up_bound_trip	0x000000008 //RW - 16 bit
#define fram_ADT7408_M_1_alarm_temp_low_bound_trip	0x00000000C //RW - 16 bit
#define fram_ADT7408_M_1_critical_temp_trip			0x000000010 //RW - 16 bit
#define fram_ADT7408_M_1_temp_val					0x000000014 //RW - 16 bit

#define fram_ADT7408_M_2_capability					0x000000018 //R  - 16 bit
#define fram_ADT7408_M_2_configuration				0x00000001C //RW - 16 bit
#define fram_ADT7408_M_2_alarm_temp_up_bound_trip	0x000000020 //RW - 16 bit
#define fram_ADT7408_M_2_alarm_temp_low_bound_trip	0x000000024 //RW - 16 bit
#define fram_ADT7408_M_2_critical_temp_trip			0x000000028 //RW - 16 bit
#define fram_ADT7408_M_2_temp_val					0x00000002C //RW - 16 bit

#define fram_LTC4281_M_control_1					0x000000030 //RW - 8 bit
#define fram_LTC4281_M_control_2					0x000000034 //RW - 8 bit
#define fram_LTC4281_M_alert_1						0x000000038 //RW - 8 bit
#define fram_LTC4281_M_alert_2						0x00000003C //RW - 8 bit
#define fram_LTC4281_M_fault_log					0x000000040 //RW - 8 bit
#define fram_LTC4281_M_ADC_alert_log				0x000000044 //RW - 8 bit
#define fram_LTC4281_M_FET_bad_fault_time			0x000000048 //RW - 8 bit
#define fram_LTC4281_M_GPIO_config					0x00000004C //RW - 8 bit
#define fram_LTC4281_M_VGPIO_Alarm_MIN				0x000000050 //RW - 8 bit
#define fram_LTC4281_M_VGPIO_Alarm_MAX				0x000000054 //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_Alarm_MIN			0x000000058 //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_Alarm_MAX			0x00000005C //RW - 8 bit
#define fram_LTC4281_M_VSENSE_Alarm_MIN				0x000000060 //RW - 8 bit
#define fram_LTC4281_M_VSENSE_Alarm_MAX				0x000000064 //RW - 8 bit
#define fram_LTC4281_M_POWER_Alarm_MIN				0x000000068 //RW - 8 bit
#define fram_LTC4281_M_POWER_Alarm_MAX				0x00000006C //RW - 8 bit
#define fram_LTC4281_M_clock_divider				0x000000070 //RW - 8 bit
#define fram_LTC4281_M_ILIM_Adjust					0x000000074 //RW - 8 bit
#define fram_LTC4281_M_energy_0						0x000000078 //RW - 8 bit
#define fram_LTC4281_M_energy_1						0x00000007C //RW - 8 bit
#define fram_LTC4281_M_energy_2						0x000000080 //RW - 8 bit
#define fram_LTC4281_M_energy_3						0x000000084 //RW - 8 bit
#define fram_LTC4281_M_energy_4						0x000000088 //RW - 8 bit
#define fram_LTC4281_M_energy_5						0x00000008C //RW - 8 bit
#define fram_LTC4281_M_TIME_counter_0				0x000000090 //RW - 8 bit
#define fram_LTC4281_M_TIME_counter_1				0x000000094 //RW - 8 bit
#define fram_LTC4281_M_TIME_counter_2				0x000000098 //RW - 8 bit
#define fram_LTC4281_M_TIME_counter_3				0x00000009C //RW - 8 bit
#define fram_LTC4281_M_Alert_control				0x0000000A0 //RW - 8 bit
#define fram_LTC4281_M_ADC_control					0x0000000A4 //RW - 8 bit
#define fram_LTC4281_M_status_0						0x0000000A8 //R  - 8 bit
#define fram_LTC4281_M_status_1						0x0000000AC //R  - 8 bit
#define fram_LTC4281_M_VGPIO_msb					0x0000000B0 //RW - 8 bit
#define fram_LTC4281_M_VGPIO_lsb					0x0000000B4 //RW - 8 bit
#define fram_LTC4281_M_VGPIO_MIN_msb				0x0000000B8 //RW - 8 bit
#define fram_LTC4281_M_VGPIO_MIN_lsb 				0x0000000BC //RW - 8 bit
#define fram_LTC4281_M_VGPIO_MAX_msb				0x0000000C0 //RW - 8 bit
#define fram_LTC4281_M_VGPIO_MAX_lsb				0x0000000C4 //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_msb					0x0000000C8 //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_lsb					0x0000000CC //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_MIN_msb				0x0000000D0 //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_MIN_lsb				0x0000000D4 //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_MAX_msb				0x0000000D8 //RW - 8 bit
#define fram_LTC4281_M_VSOURCE_MAX_lsb				0x0000000DC //RW - 8 bit
#define fram_LTC4281_M_VSENSE_msb					0x0000000E0 //RW - 8 bit
#define fram_LTC4281_M_VSENSE_lsb					0x0000000E4 //RW - 8 bit
#define fram_LTC4281_M_VSENSE_MIN_msb				0x0000000E8 //RW - 8 bit
#define fram_LTC4281_M_VSENSE_MIN_lsb				0x0000000EC //RW - 8 bit
#define fram_LTC4281_M_VSENSE_MAX_msb				0x0000000F0 //RW - 8 bit
#define fram_LTC4281_M_VSENSE_MAX_lsb				0x0000000F4 //RW - 8 bit
#define fram_LTC4281_M_POWER_msb					0x0000000F8 //RW - 8 bit
#define fram_LTC4281_M_POWER_lsb					0x0000000FC //RW - 8 bit
#define fram_LTC4281_M_POWER_MIN_msb				0x000000100 //RW - 8 bit
#define fram_LTC4281_M_POWER_MIN_lsb				0x000000104 //RW - 8 bit
#define fram_LTC4281_M_POWER_MAX_msb				0x000000108 //RW - 8 bit
#define fram_LTC4281_M_POWER_MAX_lsb				0x00000010C //RW - 8 bit

#define fram_LTC3676_M_BUCK1						0x000000110 //RW - 8 bit
#define fram_LTC3676_M_BUCK2						0x000000114 //RW - 8 bit
#define fram_LTC3676_M_BUCK3						0x000000118 //RW - 8 bit
#define fram_LTC3676_M_BUCK4						0x00000011C //RW - 8 bit
#define fram_LTC3676_M_LDOA							0x000000120 //RW - 8 bit
#define fram_LTC3676_M_LDOB							0x000000124 //RW - 8 bit
#define fram_LTC3676_M_SQD1							0x000000128 //RW - 8 bit
#define fram_LTC3676_M_SQD2							0x00000012C //RW - 8 bit
#define fram_LTC3676_M_CNTRL						0x000000130 //RW - 8 bit
#define fram_LTC3676_M_DVB1A						0x000000134 //RW - 8 bit
#define fram_LTC3676_M_DVB1B						0x000000138 //RW - 8 bit
#define fram_LTC3676_M_DVB2A						0x00000013C //RW - 8 bit
#define fram_LTC3676_M_DVB2B						0x000000140 //RW - 8 bit
#define fram_LTC3676_M_DVB3A						0x000000144 //RW - 8 bit
#define fram_LTC3676_M_DVB3B						0x000000148 //RW - 8 bit
#define fram_LTC3676_M_DVB4A						0x00000014C //RW - 8 bit
#define fram_LTC3676_M_DVB4B						0x000000150 //RW - 8 bit
#define fram_LTC3676_M_MSKIRQ						0x000000154 //RW - 8 bit
#define fram_LTC3676_M_MSKPG						0x000000158 //RW - 8 bit
#define fram_LTC3676_M_USER							0x00000015C //RW - 8 bit
#define fram_LTC3676_M_HRESET						0x000000160 //R  - 8 bit
#define fram_LTC3676_M_CLIARIRQ						0x000000164 //R  - 8 bit
#define fram_LTC3676_M_IRQSTAT						0x000000168 //R  - 8 bit
#define fram_LTC3676_M_PGSTATL						0x00000016C //R  - 8 bit
#define fram_LTC3676_M_PGSTATRT						0x000000170 //R  - 8 bit

// i2c2
#define fram_ADT7408_B_1_capability					0x000000174 //R  - 16 bit
#define fram_ADT7408_B_1_configuration				0x000000178 //RW - 16 bit
#define fram_ADT7408_B_1_alarm_temp_up_bound_trip	0x00000017C //RW - 16 bit
#define fram_ADT7408_B_1_alarm_temp_low_bound_trip	0x000000180 //RW - 16 bit
#define fram_ADT7408_B_1_critical_temp_trip			0x000000184 //RW - 16 bit
#define fram_ADT7408_B_1_temp_val					0x000000188 //RW - 16 bit

#define fram_ADT7408_B_2_capability					0x00000018C //R  - 16 bit
#define fram_ADT7408_B_2_configuration				0x000000190 //RW - 16 bit
#define fram_ADT7408_B_2_alarm_temp_up_bound_trip	0x000000194 //RW - 16 bit
#define fram_ADT7408_B_2_alarm_temp_low_bound_trip	0x000000198 //RW - 16 bit
#define fram_ADT7408_B_2_critical_temp_trip			0x00000019C //RW - 16 bit
#define fram_ADT7408_B_2_temp_val					0x000000200 //RW - 16 bit

#define fram_LTC4281_M_control_1					0x000000030 //RW - 8 bit
#define fram_LTC4281_M_control_2					0x000000034 //RW - 8 bit
#define fram_LTC4281_M_alert_1						0x000000038 //RW - 8 bit
#define fram_LTC4281_M_alert_2						0x00000003C //RW - 8 bit
#define fram_LTC4281_M_status_0						0x0000000A8 //R  - 8 bit
#define fram_LTC4281_M_status_1						0x0000000AC //R  - 8 bit



#endif /* FRAM_H_ */