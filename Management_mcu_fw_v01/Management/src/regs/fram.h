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

#define fram_LTC4281_B_1_control					0x000000204 //RW - 16 bit
#define fram_LTC4281_B_1_alert						0x000000208 //RW - 16 bit
#define fram_LTC4281_B_1_fault_log					0x00000020C //RW - 8 bit
#define fram_LTC4281_B_1_ilim_adj					0x000000210 //RW - 8 bit
#define fram_LTC4281_B_1_Vsource					0x000000214 //R  - 16 bit
#define fram_LTC4281_B_1_power						0x000000218 //R  - 16 bit

#define fram_LTC4281_B_2_control					0x00000021C //RW - 16 bit
#define fram_LTC4281_B_2_alert						0x000000220 //RW - 16 bit
#define fram_LTC4281_B_2_fault_log					0x000000224 //RW - 8 bit
#define fram_LTC4281_B_2_ilim_adj					0x000000228 //RW - 8 bit
#define fram_LTC4281_B_2_Vsource					0x00000022C //R  - 16 bit
#define fram_LTC4281_B_2_power						0x000000230 //R  - 16 bit

#define fram_LTC4281_B_3_control					0x000000234 //RW - 16 bit
#define fram_LTC4281_B_3_alert						0x000000238 //RW - 16 bit
#define fram_LTC4281_B_3_fault_log					0x00000023C //RW - 8 bit
#define fram_LTC4281_B_3_ilim_adj					0x000000240 //RW - 8 bit
#define fram_LTC4281_B_3_Vsource					0x000000244 //R  - 16 bit
#define fram_LTC4281_B_3_power						0x000000248 //R  - 16 bit

#define fram_LTC4281_B_4_control					0x00000024C //RW - 16 bit
#define fram_LTC4281_B_4_alert						0x000000250 //RW - 16 bit
#define fram_LTC4281_B_4_fault_log					0x000000254 //RW - 8 bit
#define fram_LTC4281_B_4_ilim_adj					0x000000258 //RW - 8 bit
#define fram_LTC4281_B_4_Vsource					0x00000025C //R  - 16 bit
#define fram_LTC4281_B_4_power						0x000000260 //R  - 16 bit

#define fram_LTC4281_B_5_control					0x000000264 //RW - 16 bit
#define fram_LTC4281_B_5_alert						0x000000268 //RW - 16 bit
#define fram_LTC4281_B_5_fault_log					0x00000026C //RW - 8 bit
#define fram_LTC4281_B_5_ilim_adj					0x000000270 //RW - 8 bit
#define fram_LTC4281_B_5_Vsource					0x000000274 //R  - 16 bit
#define fram_LTC4281_B_5_power						0x000000278 //R  - 16 bit

#define fram_LTC4281_B_6_control					0x00000027C //RW - 16 bit
#define fram_LTC4281_B_6_alert						0x000000280 //RW - 16 bit
#define fram_LTC4281_B_6_fault_log					0x000000284 //RW - 8 bit
#define fram_LTC4281_B_6_ilim_adj					0x000000288 //RW - 8 bit
#define fram_LTC4281_B_6_Vsource					0x00000028C //R  - 16 bit
#define fram_LTC4281_B_6_power						0x000000290 //R  - 16 bit

#define fram_LTC4281_B_7_control					0x000000294 //RW - 16 bit
#define fram_LTC4281_B_7_alert						0x000000298 //RW - 16 bit
#define fram_LTC4281_B_7_fault_log					0x00000029C //RW - 8 bit
#define fram_LTC4281_B_7_ilim_adj					0x000000300 //RW - 8 bit
#define fram_LTC4281_B_7_Vsource					0x000000304 //R  - 16 bit
#define fram_LTC4281_B_7_power						0x000000308 //R  - 16 bit

#define fram_LTC4281_B_8_control					0x00000030C //RW - 16 bit
#define fram_LTC4281_B_8_alert						0x000000310 //RW - 16 bit
#define fram_LTC4281_B_8_fault_log					0x000000314 //RW - 8 bit
#define fram_LTC4281_B_8_ilim_adj					0x000000318 //RW - 8 bit
#define fram_LTC4281_B_8_Vsource					0x00000031C //R  - 16 bit
#define fram_LTC4281_B_8_power						0x000000320 //R  - 16 bit

// i2c3

#define fram_PSU_0_vout								0x000000324 //R  - 16 bit
#define fram_PSU_0_iout								0x000000328 //R  - 16 bit
#define fram_PSU_0_vin								0x00000032C //R  - 16 bit
#define fram_PSU_0_iin								0x000000330 //R  - 16 bit
#define fram_PSU_0_status_vout						0x000000334 //R  - 8 bit
#define fram_PSU_0_status_iout						0x000000338 //R  - 8 bit
#define fram_PSU_0_fan_speed						0x00000033C //R  - 16 bit

#define fram_PSU_1_vout								0x000000340 //R  - 16 bit
#define fram_PSU_1_iout								0x000000344 //R  - 16 bit
#define fram_PSU_1_vin								0x000000348 //R  - 16 bit
#define fram_PSU_1_iin								0x00000034C //R  - 16 bit
#define fram_PSU_1_status_vout						0x000000350 //R  - 8 bit
#define fram_PSU_1_status_iout						0x000000354 //R  - 8 bit
#define fram_PSU_1_fan_speed						0x000000358 //R  - 16 bit

// i2c2
#define fram_FAN_PWM								0x00000035C //RW - 8 bit
#define fram_FAN1_TACH								0x000000360 //R  - 32 bit
#define fram_FAN2_TACH								0x000000364 //R  - 32 bit
#define fram_FAN3_TACH								0x000000368 //R  - 32 bit
#define fram_FAN4_TACH								0x00000036C //R  - 32 bit


#define fram_TPM_SUPPLY_STATUS						0x000000370 //R  - 32 bit

#define fram_MCU_COUNTER_ALIVE						0x000000374 //R  - 32 bit


#endif /* FRAM_H_ */