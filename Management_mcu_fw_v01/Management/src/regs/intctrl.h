#define intctrl_global_status  	0x00000000	//R
#define intctrl_global_status_M	0x00000007
#define intctrl_global_status_R	0x0
#define intctrl_global_status_D	"Global BAR Interrupt Status"

#define intctrl_global_mask  	0x00000004	//RW
#define intctrl_global_mask_M	0x00000007
#define intctrl_global_mask_R	0x7
#define intctrl_global_mask_D	"Global BAR Interrupt Value"

#define intctrl_bar_0_status  	0x00000100	//R
#define intctrl_bar_0_status_M	0x000000ff
#define intctrl_bar_0_status_R	0x00
#define intctrl_bar_0_status_D	"BAR Interrupt Status"

#define intctrl_bar_0_mask  	0x00000104	//RW
#define intctrl_bar_0_mask_M	0x000000ff
#define intctrl_bar_0_mask_R	0xff
#define intctrl_bar_0_mask_D	"BAR Interrupt Value"

#define intctrl_bar_0_ack  	0x00000108	//RW
#define intctrl_bar_0_ack_M	0x000000ff
#define intctrl_bar_0_ack_R	0x00
#define intctrl_bar_0_ack_D	"BAR Interrupt Acknowledge"

#define intctrl_bar_1_status  	0x00000200	//R
#define intctrl_bar_1_status_M	0x000000ff
#define intctrl_bar_1_status_R	0x00
#define intctrl_bar_1_status_D	"BAR Interrupt Status"

#define intctrl_bar_1_mask  	0x00000204	//RW
#define intctrl_bar_1_mask_M	0x000000ff
#define intctrl_bar_1_mask_R	0xff
#define intctrl_bar_1_mask_D	"BAR Interrupt Value"

#define intctrl_bar_1_ack  	0x00000208	//RW
#define intctrl_bar_1_ack_M	0x000000ff
#define intctrl_bar_1_ack_R	0x00
#define intctrl_bar_1_ack_D	"BAR Interrupt Acknowledge"

#define intctrl_bar_2_status  	0x00000300	//R
#define intctrl_bar_2_status_M	0x000000ff
#define intctrl_bar_2_status_R	0x00
#define intctrl_bar_2_status_D	"BAR Interrupt Status"

#define intctrl_bar_2_mask  	0x00000304	//RW
#define intctrl_bar_2_mask_M	0x000000ff
#define intctrl_bar_2_mask_R	0xff
#define intctrl_bar_2_mask_D	"BAR Interrupt Value"

#define intctrl_bar_2_ack  	0x00000308	//RW
#define intctrl_bar_2_ack_M	0x000000ff
#define intctrl_bar_2_ack_R	0x00
#define intctrl_bar_2_ack_D	"BAR Interrupt Acknowledge"

