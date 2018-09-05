#define mdio_mdio_addr  	0x00000000	//RW
#define mdio_mdio_addr_M	0xFFFFFFFF
#define mdio_mdio_addr_R	0x0
#define mdio_mdio_addr_D	"MDIO phy and reg addresses"

#define mdio_mdio_addr_phy  	0x00000000	//RW
#define mdio_mdio_addr_phy_M	0x0000001f
#define mdio_mdio_addr_phy_R	0x0
#define mdio_mdio_addr_phy_D	"PHY"

#define mdio_mdio_addr_mux  	0x00000000	//RW
#define mdio_mdio_addr_mux_M	0x00004000
#define mdio_mdio_addr_mux_R	0x0
#define mdio_mdio_addr_mux_D	"Mux"

#define mdio_mdio_addr_reg  	0x00000000	//RW
#define mdio_mdio_addr_reg_M	0x00001f00
#define mdio_mdio_addr_reg_R	0x0
#define mdio_mdio_addr_reg_D	"Reg"

#define mdio_mdio_write  	0x00000004	//RW
#define mdio_mdio_write_M	0x0000ffff
#define mdio_mdio_write_R	0x0
#define mdio_mdio_write_D	"Register data to be written."

#define mdio_mdio_cmd  	0x00000008	//RW
#define mdio_mdio_cmd_M	0xFFFFFFFF
#define mdio_mdio_cmd_R	0x0
#define mdio_mdio_cmd_D	"MDIO cmd and status"

#define mdio_mdio_cmd_int  	0x00000008	//R
#define mdio_mdio_cmd_int_M	0x00000030
#define mdio_mdio_cmd_int_R	0x0
#define mdio_mdio_cmd_int_D	"Interrupt, MDIO available"

#define mdio_mdio_cmd_done  	0x00000008	//R
#define mdio_mdio_cmd_done_M	0x00000004
#define mdio_mdio_cmd_done_R	0x0
#define mdio_mdio_cmd_done_D	"Done, '0' command in progress, '1' command finished."

#define mdio_mdio_cmd_read_not_write  	0x00000008	//RW
#define mdio_mdio_cmd_read_not_write_M	0x00000002
#define mdio_mdio_cmd_read_not_write_R	0x0
#define mdio_mdio_cmd_read_not_write_D	"Select read or write access"

#define mdio_mdio_cmd_start  	0x00000008	//RW
#define mdio_mdio_cmd_start_M	0x00000001
#define mdio_mdio_cmd_start_R	0x0
#define mdio_mdio_cmd_start_D	"Start Command"

#define mdio_mdio_read  	0x0000000C	//R
#define mdio_mdio_read_M	0x0000ffff
#define mdio_mdio_read_R	0x0
#define mdio_mdio_read_D	"Register data read. Valid when mdio_cmd.done = '1'"

