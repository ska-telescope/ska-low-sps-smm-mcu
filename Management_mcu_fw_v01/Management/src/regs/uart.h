#define uart_ctrl_rnw  	0x00000000	//RW
#define uart_ctrl_rnw_M	0x00000001
#define uart_ctrl_rnw_R	0x0
#define uart_ctrl_rnw_D	"Read Not Write Command Execute"

#define uart_ctrl_txdata  	0x00000004	//RW
#define uart_ctrl_txdata_M	0x000000ff
#define uart_ctrl_txdata_R	0x0
#define uart_ctrl_txdata_D	"TX Data"

#define uart_ctrl_rxdata  	0x00000008	//R
#define uart_ctrl_rxdata_M	0x000000ff
#define uart_ctrl_rxdata_R	0x0
#define uart_ctrl_rxdata_D	"RX Data"

#define uart_ctrl_status  	0x0000000C	//R
#define uart_ctrl_status_M	0x00000003
#define uart_ctrl_status_R	0x0
#define uart_ctrl_status_D	"Status"

