/*
 * IncFile1.h
 *
 * Created: 30/10/2019 10:50:23
 *  Author: luca
 */ 


#ifndef ONEWIREREG_H_
#define ONEWIREREG_H_

#define onewire_Command1WM 		0x00000000	//RW
#define onewire_Command1WM_M	0x000000ff
#define onewire_Command1WM_R	0x0
#define onewire_Command1WM_D	"Command Register"

#define onewire_Data1WM  		0x00000004	//RW
#define onewire_Data1WM_M		0x000000ff
#define onewire_Data1WM_R		0x0
#define onewire_Data1WM_D		"Data Register"

#define onewire_Int1WM  		0x00000008	//RW
#define onewire_Int1WM_M		0x000000ff
#define onewire_Int1WM_R		0x0
#define onewire_Int1WM_D		"Interrupt Register"

#define onewire_IntEn1WM  		0x0000000C	//RW
#define onewire_IntEn1WM_M		0x000000ff
#define onewire_IntEn1WM_R		0x0
#define onewire_IntEn1WM_D		"Interrupt Enable Register"

#define onewire_Clock1WM  		0x00000010	//RW
#define onewire_Clock1WM_M		0x000000ff
#define onewire_Clock1WM_R		0x0
#define onewire_Clock1WM_D		"DS1WM Clock Divider"

#define onewire_Ctrl1WM  		0x00000014	//RW
#define onewire_Ctrl1WM_M		0x000000ff
#define onewire_Ctrl1WM_R		0x0
#define onewire_Ctrl1WM_D		"Ctrl Register"

#define onewire_Mux1WM  		0x00000018	//RW
#define onewire_Mux1WM_M		0x000000ff
#define onewire_Mux1WM_R		0x0
#define onewire_Mux1WM_D		"Mux Register"



#endif /* ONEWIREREG_H_ */