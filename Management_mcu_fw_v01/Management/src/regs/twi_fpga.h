/*
 * twi_fpga.h
 *
 * Created: 18/12/2018 10:54:41
 *  Author: luca
 */ 


#ifndef TWI_FPGA_H_
#define TWI_FPGA_H_

#define twi_offset				0x00010000
// #define twi_command_byte_len	0x0  // R - Max 16B
// #define twi_command				0x4  // RW [9:0] command
// #define twi_wrbyte				0x4  // RW [23:16] byte number to write
// #define twi_rbyte				0x4	 // RW [31:24] byte number to read
// #define twi_status				0x8  // R
// #define twi_irq					0xc  // RW
// #define twi_irq_en				0x10 // RW

#define twi_wrdata				0x100 // Data W reg 32b (Add + data)
#define tiw_rdata				0x200 // Data R reg 32b

#define i2c_command  	0x00010000	//RW
#define i2c_command_M	0xFFFFFFFF
#define i2c_command_R	0x0
#define i2c_command_D	"Missing description"

#define i2c_command_wrbyte_M	0x00000f00
#define i2c_command_wrbyte_B	8
#define i2c_command_wrbyte_R	0x0
#define i2c_command_wrbyte_D	"Number of byte to write"

#define i2c_command_phyadd_M	0x0000007f
#define i2c_command_phyadd_B	0
#define i2c_command_phyadd_R	0x0
#define i2c_command_phyadd_D	"Physical Address"

#define i2c_command_mux_M	0x00030000
#define i2c_command_mux_B	16
#define i2c_command_mux_R	0x0
#define i2c_command_mux_D	"Output mux control"

#define i2c_command_rdbyte_M	0x0000f000
#define i2c_command_rdbyte_B	12
#define i2c_command_rdbyte_R	0x0
#define i2c_command_rdbyte_D	"Number of byte to read"

#define i2c_transmit  	0x00010004	//RW
#define i2c_transmit_M	0xFFFFFFFF
#define i2c_transmit_R	0x0
#define i2c_transmit_D	"Data to be transmitted"

#define i2c_receive  	0x00010008	//R
#define i2c_receive_M	0xFFFFFFFF
#define i2c_receive_R	0x0
#define i2c_receive_D	"Data received"

#define i2c_status  	0x0001000C	//RW
#define i2c_status_M	0xFFFFFFFF
#define i2c_status_R	0x0
#define i2c_status_D	"Missing description"

#define i2c_status_busy_M	0x00000001
#define i2c_status_busy_B	0
#define i2c_status_busy_R	0x0
#define i2c_status_busy_D	"Busy"

#define i2c_status_ack_error_M	0x00000002
#define i2c_status_ack_error_B	1
#define i2c_status_ack_error_R	0x0
#define i2c_status_ack_error_D	"Acknowledge error"

#define i2c_irq  	0x00010010	//RW
#define i2c_irq_M	0xFFFFFFFF
#define i2c_irq_R	0x0
#define i2c_irq_D	"Missing description"

#define i2c_irq_done_M	0x00000001
#define i2c_irq_done_B	0
#define i2c_irq_done_R	0x0
#define i2c_irq_done_D	"IRQ Done"

#define i2c_irq_ack_error_M	0x00000002
#define i2c_irq_ack_error_B	1
#define i2c_irq_ack_error_R	0x0
#define i2c_irq_ack_error_D	"IRQ Acknowledge error"

#define i2c_irq_en  	0x00010014	//RW
#define i2c_irq_en_M	0x00000003
#define i2c_irq_en_R	0x0
#define i2c_irq_en_D	"IRQ Enables"

#define i2c_update_network_config  	0x00010018	//RW
#define i2c_update_network_config_M	0x00000001
#define i2c_update_network_config_R	0x0
#define i2c_update_network_config_D	"Update network config"

#define i2c_mac_hi  	0x00010020	//RW
#define i2c_mac_hi_M	0x0000ffff
#define i2c_mac_hi_R	0x0
#define i2c_mac_hi_D	"MAC high part"

#define i2c_mac_lo  	0x00010024	//RW
#define i2c_mac_lo_M	0xffffffff
#define i2c_mac_lo_R	0x0
#define i2c_mac_lo_D	"MAC low part"

#define i2c_ip  	0x00010028	//RW
#define i2c_ip_M	0xffffffff
#define i2c_ip_R	0x0
#define i2c_ip_D	"IP"

#define i2c_netmask  	0x0001002C	//RW
#define i2c_netmask_M	0xffffffff
#define i2c_netmask_R	0x0
#define i2c_netmask_D	"Netmask"

#define i2c_gateway  	0x00010030	//RW
#define i2c_gateway_M	0xffffffff
#define i2c_gateway_R	0x0
#define i2c_gateway_D	"Gateway"

#define i2c_key  	0x00010034	//R
#define i2c_key_M	0x00ffffff
#define i2c_key_R	0x0
#define i2c_key_D	"Key"

#define i2c_password_lo  	0x00010038	//RW
#define i2c_password_lo_M	0xffffffff
#define i2c_password_lo_R	0x0
#define i2c_password_lo_D	"Password low part"

#define i2c_password  	0x0001003C	//RW
#define i2c_password_M	0xFFFFFFFF
#define i2c_password_R	0x0
#define i2c_password_D	"Missing description"

#define i2c_password_hi_M	0x0000ffff
#define i2c_password_hi_B	0
#define i2c_password_hi_R	0x0
#define i2c_password_hi_D	"Password high part"

#define i2c_password_ok_M	0x00010000
#define i2c_password_ok_B	16
#define i2c_password_ok_R	0x0
#define i2c_password_ok_D	"Password OK"

#endif /* TWI_FPGA_H_ */

/*
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

package wb_i2c_registers_pkg is
constant WB_FPGA_REGNUM  : integer := 8;  --              Max Number of registers per bank
constant I2C_CMD_BYTELEN : integer := 16;  --             Max Number of registers per bank

type i2c_reg_type is record
--I2C_CMD_BYTELEN  : std_logic_vector(15 downto 0);  --         0x0         R             (others =>'-')
command    : std_logic_vector(9 downto 0);  --                  0x4         RW            (others =>'-')
wrbyte     : std_logic_vector(23 downto 16);  --                0x4         RW            (others =>'-')
rdbyte     : std_logic_vector(31 downto 24);  --                0x4         RW            (others =>'-')
command_we : std_logic_vector(0 downto 0);  --                  non mappato
status     : std_logic_vector(1 downto 0);  --                  0x8         R             (others =>'-')
irq        : std_logic_vector(1 downto 0);  --                  0xc         RW            (others =>'-')
irq_en     : std_logic_vector(1 downto 0);  --                  0x10        RW            (others =>'-')
end record i2c_reg_type;

type i2c_data_type is array (0 to I2C_CMD_BYTELEN/4-1) of std_logic_vector(31 downto 0);

end package wb_i2c_registers_pkg;
*/