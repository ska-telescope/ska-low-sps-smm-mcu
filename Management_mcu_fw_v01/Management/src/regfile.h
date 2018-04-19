// sam.h

#define sam_offset	0x00030000

#define sam_mcufw_build_version  	0x00000000	//RW
#define sam_mcufw_build_version_M	0xffffffff
#define sam_mcufw_build_version_R	0x0
#define sam_mcufw_build_version_D	"MCU Firmware Version"

#define sam_mcufw_build_time  	0x00000004	//RW
#define sam_mcufw_build_time_M	0xffffffff
#define sam_mcufw_build_time_R	0x0
#define sam_mcufw_build_time_D	"MCU Firmware Build time"

#define sam_mcufw_build_date  	0x00000008	//RW
#define sam_mcufw_build_date_M	0xffffffff
#define sam_mcufw_build_date_R	0x0
#define sam_mcufw_build_date_D	"MCU Firmware Build date"

#define sam_user_gp0  	0x00000100	//RW
#define sam_user_gp0_M	0xffffffff
#define sam_user_gp0_R	0x0
#define sam_user_gp0_D	"MCU General Purpouse User Register 0"

#define sam_user_gp1  	0x00000104	//RW
#define sam_user_gp1_M	0xffffffff
#define sam_user_gp1_R	0x0
#define sam_user_gp1_D	"MCU General Purpouse User Register 1"

#define sam_user_gp2  	0x00000108	//RW
#define sam_user_gp2_M	0xffffffff
#define sam_user_gp2_R	0x0
#define sam_user_gp2_D	"MCU General Purpouse User Register 2"

#define sam_user_gp3  	0x0000010C	//RW
#define sam_user_gp3_M	0xffffffff
#define sam_user_gp3_R	0x0
#define sam_user_gp3_D	"MCU General Purpouse User Register 3"

#define sam_voltage_soc  	0x00000200	//RW
#define sam_voltage_soc_M	0xffffffff
#define sam_voltage_soc_R	0x0
#define sam_voltage_soc_D	"SOC Voltage Value"

#define sam_voltage_arm  	0x00000204	//RW
#define sam_voltage_arm_M	0xffffffff
#define sam_voltage_arm_R	0x0
#define sam_voltage_arm_D	"ARM Voltage Value"

#define sam_voltage_ddr  	0x00000208	//RW
#define sam_voltage_ddr_M	0xffffffff
#define sam_voltage_ddr_R	0x0
#define sam_voltage_ddr_D	"DDR Voltage Value"

#define sam_voltage_v25  	0x0000020C	//RW
#define sam_voltage_v25_M	0xffffffff
#define sam_voltage_v25_R	0x0
#define sam_voltage_v25_D	"2V5 Voltage Value"

#define sam_voltage_v1  	0x00000210	//RW
#define sam_voltage_v1_M	0xffffffff
#define sam_voltage_v1_R	0x0
#define sam_voltage_v1_D	"1V0 Voltage Value"

#define sam_voltage_v11  	0x00000214	//RW
#define sam_voltage_v11_M	0xffffffff
#define sam_voltage_v11_R	0x0
#define sam_voltage_v11_D	"1V1 Voltage Value"

#define sam_voltage_vcore  	0x00000218	//RW
#define sam_voltage_vcore_M	0xffffffff
#define sam_voltage_vcore_R	0x0
#define sam_voltage_vcore_D	"VCORE Voltage Value"

#define sam_voltage_v15  	0x0000021C	//RW
#define sam_voltage_v15_M	0xffffffff
#define sam_voltage_v15_R	0x0
#define sam_voltage_v15_D	"1V5 Voltage Value"

#define sam_voltage_v33  	0x00000220	//RW
#define sam_voltage_v33_M	0xffffffff
#define sam_voltage_v33_R	0x0
#define sam_voltage_v33_D	"3V3 Voltage Value"

#define sam_voltage_v5  	0x00000224	//RW
#define sam_voltage_v5_M	0xffffffff
#define sam_voltage_v5_R	0x0
#define sam_voltage_v5_D	"5V Voltage Value"

#define sam_voltage_v3  	0x00000228	//RW
#define sam_voltage_v3_M	0xffffffff
#define sam_voltage_v3_R	0x0
#define sam_voltage_v3_D	"3V Voltage Value"

#define sam_voltage_v28  	0x0000022C	//RW
#define sam_voltage_v28_M	0xffffffff
#define sam_voltage_v28_R	0x0
#define sam_voltage_v28_D	"2V8 Voltage Value"

#define sam_temp_Buck  	0x00000300	//RW
#define sam_temp_Buck_M	0xffffffff
#define sam_temp_Buck_R	0x0
#define sam_temp_Buck_D	"Buck Regulator Temp"

#define sam_temp_MCU  	0x00000304	//RW
#define sam_temp_MCU_M	0xffffffff
#define sam_temp_MCU_R	0x0
#define sam_temp_MCU_D	"MCU Internal Temp"


// Old def
/*
#define regfile_fw_build_low  	0x00000000	//R
#define regfile_fw_build_low_M	0xffffffff
#define regfile_fw_build_low_R	0x0
#define regfile_fw_build_low_D	"Build Timestamp Low Part"

#define regfile_fw_build_high  	0x00000004	//R
#define regfile_fw_build_high_M	0x0000ffff
#define regfile_fw_build_high_R	0x0
#define regfile_fw_build_high_D	"Build Timestamp High Part"

#define regfile_fw_version  	0x00000008	//R
#define regfile_fw_version_M	0xffffffff
#define regfile_fw_version_R	0x0
#define regfile_fw_version_D	"Firmware Version"

#define regfile_ethernet_mac0_low  	0x00000100	//RW
#define regfile_ethernet_mac0_low_M	0xffffffff
#define regfile_ethernet_mac0_low_R	0xbbccdd00
#define regfile_ethernet_mac0_low_D	"MAC 0 Low Part"

#define regfile_ethernet_mac0_high  	0x00000104	//RW
#define regfile_ethernet_mac0_high_M	0x0000ffff
#define regfile_ethernet_mac0_high_R	0x000002aa
#define regfile_ethernet_mac0_high_D	"MAC 0 High Part"

#define regfile_ethernet_mac1_low  	0x00000108	//RW
#define regfile_ethernet_mac1_low_M	0xffffffff
#define regfile_ethernet_mac1_low_R	0x22334400
#define regfile_ethernet_mac1_low_D	"MAC 1 Low Part"

#define regfile_ethernet_mac1_high  	0x0000010C	//RW
#define regfile_ethernet_mac1_high_M	0x0000ffff
#define regfile_ethernet_mac1_high_R	0x00000211
#define regfile_ethernet_mac1_high_D	"MAC 1 High Part"

#define regfile_ethernet_ip  	0x00000110	//RW
#define regfile_ethernet_ip_M	0xffffffff
#define regfile_ethernet_ip_R	0x0a000a02
#define regfile_ethernet_ip_D	"IP"

#define regfile_ethernet_mask  	0x00000114	//RW
#define regfile_ethernet_mask_M	0xffffffff
#define regfile_ethernet_mask_R	0xffffff00
#define regfile_ethernet_mask_D	"Mask"

#define regfile_ethernet_gateway  	0x00000118	//RW
#define regfile_ethernet_gateway_M	0xffffffff
#define regfile_ethernet_gateway_R	0x0a000a01
#define regfile_ethernet_gateway_D	"Gateway"

#define regfile_UCP_ucp_rx_dst_port_l  	0x00000200	//RW
#define regfile_UCP_ucp_rx_dst_port_l_M	0x0000ffff
#define regfile_UCP_ucp_rx_dst_port_l_R	0x00002710
#define regfile_UCP_ucp_rx_dst_port_l_D	"UCP RX destination UDP port Low"

#define regfile_UCP_ucp_rx_dst_port_h  	0x00000204	//RW
#define regfile_UCP_ucp_rx_dst_port_h_M	0x0000ffff
#define regfile_UCP_ucp_rx_dst_port_h_R	0x00002714
#define regfile_UCP_ucp_rx_dst_port_h_D	"UCP RX destination UDP port High "

#define regfile_UCP_ucplastpsn  	0x00000208	//R
#define regfile_UCP_ucplastpsn_M	0xffffffff
#define regfile_UCP_ucplastpsn_R	0x0
#define regfile_UCP_ucplastpsn_D	"UCP Last Psn"

#define regfile_pll_reset  	0x00000300	//RW
#define regfile_pll_reset_M	0x00000001
#define regfile_pll_reset_R	0x00000001
#define regfile_pll_reset_D	"DPLL Reset Status"

#define regfile_pll_m  	0x00000304	//RW
#define regfile_pll_m_M	0x0000001f
#define regfile_pll_m_R	0x00000000
#define regfile_pll_m_D	"DPLL Multifunction Status"

#define regfile_led_tpm_k  	0x00000400	//RW
#define regfile_led_tpm_k_M	0x00000fff
#define regfile_led_tpm_k_R	0x00000000
#define regfile_led_tpm_k_D	"TPM LED K"

#define regfile_led_tpm_a  	0x00000404	//RW
#define regfile_led_tpm_a_M	0x00000fff
#define regfile_led_tpm_a_R	0x00000000
#define regfile_led_tpm_a_D	"TPM LED A"

#define regfile_led_user_k  	0x00000408	//RW
#define regfile_led_user_k_M	0x0000000f
#define regfile_led_user_k_R	0x00000000
#define regfile_led_user_k_D	"USER LED K"

#define regfile_led_user_a  	0x0000040C	//RW
#define regfile_led_user_a_M	0x0000000f
#define regfile_led_user_a_R	0x00000000
#define regfile_led_user_a_D	"USER LED A"

#define regfile_present_backplane  	0x00000500	//R
#define regfile_present_backplane_M	0x00000001
#define regfile_present_backplane_R	0x0
#define regfile_present_backplane_D	"Backplane Present"

#define regfile_present_tpm  	0x00000504	//R
#define regfile_present_tpm_M	0x00000fff
#define regfile_present_tpm_R	0x0
#define regfile_present_tpm_D	"TPMs Present"

#define regfile_hkt  	0x00000600	//R
#define regfile_hkt_M	0xFFFFFFFF
#define regfile_hkt_R	0x0
#define regfile_hkt_D	"House Keeping Temperature"

#define regfile_hkt_temp2  	0x00000600	//R
#define regfile_hkt_temp2_M	0x00000002
#define regfile_hkt_temp2_R	0x0
#define regfile_hkt_temp2_D	"Temperature Alarm 2"

#define regfile_hkt_temp1  	0x00000600	//R
#define regfile_hkt_temp1_M	0x00000001
#define regfile_hkt_temp1_R	0x0
#define regfile_hkt_temp1_D	"Temperature Alarm 1"

#define regfile_hkv  	0x00000700	//R
#define regfile_hkv_M	0xFFFFFFFF
#define regfile_hkv_R	0x0
#define regfile_hkv_D	"House Keeping Voltages"

#define regfile_hkv_buck2_pgood  	0x00000700	//R
#define regfile_hkv_buck2_pgood_M	0x00000020
#define regfile_hkv_buck2_pgood_R	0x0
#define regfile_hkv_buck2_pgood_D	"Buck 2 Power Good"

#define regfile_hkv_vi15_pgood  	0x00000700	//R
#define regfile_hkv_vi15_pgood_M	0x00000040
#define regfile_hkv_vi15_pgood_R	0x0
#define regfile_hkv_vi15_pgood_D	"1V5 Power Good"

#define regfile_hkv_buck1_rsto  	0x00000700	//R
#define regfile_hkv_buck1_rsto_M	0x00000010
#define regfile_hkv_buck1_rsto_R	0x0
#define regfile_hkv_buck1_rsto_D	"Buck 1 Reset Output (Active Low)"

#define regfile_hkv_buck1_pgood  	0x00000700	//R
#define regfile_hkv_buck1_pgood_M	0x00000008
#define regfile_hkv_buck1_pgood_R	0x0
#define regfile_hkv_buck1_pgood_D	"Buck 1 Power Good"

#define regfile_hkv_vin_pgood  	0x00000700	//R
#define regfile_hkv_vin_pgood_M	0x00000004
#define regfile_hkv_vin_pgood_R	0x0
#define regfile_hkv_vin_pgood_D	"Step Down Power Good"

#define regfile_hkv_buck1_irq  	0x00000700	//R
#define regfile_hkv_buck1_irq_M	0x00000002
#define regfile_hkv_buck1_irq_R	0x0
#define regfile_hkv_buck1_irq_D	"Buck 1 IRQ"

#define regfile_hkv_pwrin_alert  	0x00000700	//R
#define regfile_hkv_pwrin_alert_M	0x00000001
#define regfile_hkv_pwrin_alert_R	0x0
#define regfile_hkv_pwrin_alert_D	"Hot Swap Controller Pwrin Alert (Active Low)"

#define regfile_spi_cs_ow  	0x00000800	//RW
#define regfile_spi_cs_ow_M	0x00000001
#define regfile_spi_cs_ow_R	0x00000000
#define regfile_spi_cs_ow_D	"SPI CS OW"

#define regfile_spi_cs0  	0x00000804	//RW
#define regfile_spi_cs0_M	0x00000001
#define regfile_spi_cs0_R	0x00000000
#define regfile_spi_cs0_D	"SPI CS"

#define regfile_spi_tx_byte  	0x00000808	//RW
#define regfile_spi_tx_byte_M	0x000007ff
#define regfile_spi_tx_byte_R	0x00000000
#define regfile_spi_tx_byte_D	"SPI TX Byte"

#define regfile_spi_rx_byte  	0x0000080C	//R
#define regfile_spi_rx_byte_M	0x000007ff
#define regfile_spi_rx_byte_R	0x0
#define regfile_spi_rx_byte_D	"SPI RX Byte"

#define regfile_spi_tx_buf_len  	0x00000810	//R
#define regfile_spi_tx_buf_len_M	0x0000ffff
#define regfile_spi_tx_buf_len_R	0x0
#define regfile_spi_tx_buf_len_D	"SPI TX Buffer length"

#define regfile_spi_rx_buf_len  	0x00000814	//R
#define regfile_spi_rx_buf_len_M	0x0000ffff
#define regfile_spi_rx_buf_len_R	0x0
#define regfile_spi_rx_buf_len_D	"SPI RX Buffer length"

#define regfile_spi_fifo_addr  	0x00000818	//RW
#define regfile_spi_fifo_addr_M	0x000007ff
#define regfile_spi_fifo_addr_R	0x00000000
#define regfile_spi_fifo_addr_D	"SPI Fifo Address"

#define regfile_sam_reset  	0x00000900	//RW
#define regfile_sam_reset_M	0x00000001
#define regfile_sam_reset_R	0x00000001
#define regfile_sam_reset_D	"DPLL Reset Status"

#define regfile_user_reg0  	0x00000A00	//RW
#define regfile_user_reg0_M	0xffffffff
#define regfile_user_reg0_R	0x00000000
#define regfile_user_reg0_D	"User Register 0"

#define regfile_user_reg1  	0x00000A04	//RW
#define regfile_user_reg1_M	0xffffffff
#define regfile_user_reg1_R	0x00000000
#define regfile_user_reg1_D	"User Register 1"

#define regfile_user_reg2  	0x00000A08	//RW
#define regfile_user_reg2_M	0xffffffff
#define regfile_user_reg2_R	0x00000000
#define regfile_user_reg2_D	"User Register 2"

#define regfile_user_reg3  	0x00000A0C	//RW
#define regfile_user_reg3_M	0xffffffff
#define regfile_user_reg3_R	0x00000000
#define regfile_user_reg3_D	"User Register 3"
*/