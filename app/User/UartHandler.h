#ifndef __UART_HANDLER_HH__
#define __UART_HANDLER_HH__
#include "TypedefDef.h"


void UartInit(void);
void UartDataParseHandler(void);
void UartToSendData(u8 *p,u16 length);


#define Get_Device_System_Info 0x03
#define Get_Device_Massage_Info 0x04
#define Get_System_Para_Info 0x05
#define Get_Heart_Rate_Info 0x06
#define Enter_Firware_upgrade 0xF0
#define Set_Device_Massage_Info 0x07
#define Set_Device_System_Info 0x08


#endif
