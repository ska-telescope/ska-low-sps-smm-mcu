/*
 * Sanitas EG Register File - XO3 Demo
 * 
 * V0.1 - 20/12/17 ~ Luca Schettini
 * 
 * Copyright (c) 2017 Sanitas EG srl.  All right reserved.
 * 
 */

#ifndef REGFILE_H_
#define REGFILE_H_

#define regfile_fw_build_l    0x00000000  //R
#define regfile_fw_build_l_M  0xffff
#define regfile_fw_build_l_R  0x0
#define regfile_fw_build_l_D  "Build Timestamp Low Part"

#define regfile_fw_build_m    0x00000004  //R
#define regfile_fw_build_m_M  0xffff
#define regfile_fw_build_m_R  0x0
#define regfile_fw_build_m_D  "Build Timestamp Middle Part"

#define regfile_fw_build_h    0x00000008  //R
#define regfile_fw_build_h_M  0xffff
#define regfile_fw_build_h_R  0x0
#define regfile_fw_build_h_D  "Build Timestamp High Part"

#define regfile_fw_version_l    0x0000000C  //R
#define regfile_fw_version_l_M  0xffff
#define regfile_fw_version_l_R  0x0
#define regfile_fw_version_l_D  "Firmware Version Low Part"

#define regfile_fw_version_h    0x00000010  //R
#define regfile_fw_version_h_M  0xffff
#define regfile_fw_version_h_R  0x0
#define regfile_fw_version_h_D  "Firmware Version High Part"

#define regfile_sam_rstn    0x00000100  //RW
#define regfile_sam_rstn_M  0x0001
#define regfile_sam_rstn_R  0x0001
#define regfile_sam_rstn_D  "SAM Reset N"

#define regfile_tempalarm   0x00000200  //R
#define regfile_tempalarm_M 0x0003
#define regfile_tempalarm_R 0x0
#define regfile_tempalarm_D "Temperature alarm status"

#define regfile_actuator    0x00000300  //RW
#define regfile_actuator_M  0x0007
#define regfile_actuator_R  0x0000
#define regfile_actuator_D  "Actuator - Relay"

#define regfile_mode    0x00000400  //R
#define regfile_mode_M  0x000f
#define regfile_mode_R  0x0
#define regfile_mode_D  "Mode"

#define regfile_cooler    0x00000500  //RW
#define regfile_cooler_M  0x000f
#define regfile_cooler_R  0x0000
#define regfile_cooler_D  "Coolers"

#define regfile_adc_rstn    0x00000600  //RW
#define regfile_adc_rstn_M  0x0001
#define regfile_adc_rstn_R  0x0001
#define regfile_adc_rstn_D  "ADC Reset N"

#define regfile_adc_convertn    0x00000604  //RW
#define regfile_adc_convertn_M  0x0001
#define regfile_adc_convertn_R  0x0001
#define regfile_adc_convertn_D  "ADC Convert N"

#define regfile_adc_alert   0x00000608  //R
#define regfile_adc_alert_M 0x0001
#define regfile_adc_alert_R 0x0
#define regfile_adc_alert_D "ADC Alert status"

#define regfile_adc_gpo   0x0000060C  //R
#define regfile_adc_gpo_M 0x0001
#define regfile_adc_gpo_R 0x0
#define regfile_adc_gpo_D "ADC GPO status"

#define regfile_led_enable    0x00000700  //RW
#define regfile_led_enable_M  0x000f
#define regfile_led_enable_R  0x0000
#define regfile_led_enable_D  "LEDs driver enable"

#define regfile_led_fault   0x00000704  //R
#define regfile_led_fault_M 0x000f
#define regfile_led_fault_R 0x0
#define regfile_led_fault_D "LEDs driver fault"

#define regfile_power   0x00000800  //RW
#define regfile_power_M 0xFFFFFFFF
#define regfile_power_R 0x0
#define regfile_power_D "Missing description"

#define regfile_power_fault   0x00000800  //R
#define regfile_power_fault_M 0x0002
#define regfile_power_fault_R 0x0
#define regfile_power_fault_D "Main Power Fault Status"

#define regfile_power_pgood_5v    0x00000800  //R
#define regfile_power_pgood_5v_M  0x0004
#define regfile_power_pgood_5v_R  0x0
#define regfile_power_pgood_5v_D  "Power good 5V"

#define regfile_power_pgood_3v3   0x00000800  //R
#define regfile_power_pgood_3v3_M 0x0008
#define regfile_power_pgood_3v3_R 0x0
#define regfile_power_pgood_3v3_D "Power good 3V3"

#define regfile_power_pgood_xo3   0x00000800  //R
#define regfile_power_pgood_xo3_M 0x0010
#define regfile_power_pgood_xo3_R 0x0
#define regfile_power_pgood_xo3_D "Power good XO3"

#define regfile_power_enable    0x00000800  //R
#define regfile_power_enable_M  0x0001
#define regfile_power_enable_R  0x0
#define regfile_power_enable_D  "Main Power Enable Status"

#define regfile_exp   0x00000900  //RW
#define regfile_exp_M 0x3fff
#define regfile_exp_R 0x0000
#define regfile_exp_D "Expansion"


#endif // REGFILE_H_

