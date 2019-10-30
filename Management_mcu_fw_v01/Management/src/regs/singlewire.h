#define singlewire_ctrl_rnw  	0x00000000	//RW
#define singlewire_ctrl_rnw_M	0x00000001
#define singlewire_ctrl_rnw_R	0x0
#define singlewire_ctrl_rnw_D	"Read Not Write Command Execute"

#define singlewire_ctrl_txdata  	0x00000004	//RW
#define singlewire_ctrl_txdata_M	0x000000ff
#define singlewire_ctrl_txdata_R	0x0
#define singlewire_ctrl_txdata_D	"TX Data"

#define singlewire_ctrl_rxdata  	0x00000008	//R
#define singlewire_ctrl_rxdata_M	0x000000ff
#define singlewire_ctrl_rxdata_R	0x0
#define singlewire_ctrl_rxdata_D	"RX Data"

#define singlewire_ctrl_status  	0x0000000C	//R
#define singlewire_ctrl_status_M	0x00000003
#define singlewire_ctrl_status_R	0x0
#define singlewire_ctrl_status_D	"Status"

