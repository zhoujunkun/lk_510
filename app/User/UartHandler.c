#include "TypedefDef.h"
#include "Gpio.h"
#include "Uart.h"
#include "stdio.h"
#include "Global.h"
#include "UartHandler.h"
#include "Lpuart.h"
u8 u8TxData[50] = {0x00,0x55};
u8 u8RxData;
u8 u8TxCnt=0,u8RxCnt=0;

void TxIntCallback(void)
{
    u8TxCnt++;
    if(u8TxCnt<=1)
    {
        M0P_UART1->SBUF = u8TxData[1];
    }
}
void RxIntCallback(void)
{
    u8RxData=Uart_ReceiveData(UARTCH1);
    u8RxCnt++;
}
void ErrIntCallback(void)
{
  
}
void PErrIntCallBack(void)
{
	
}
void CtsIntCallBack(void)
{
	
}

void Uart_PortInit(void)
{
    stc_gpio_config_t stcGpioCfg;
    DDL_ZERO_STRUCT(stcGpioCfg);
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPortB,GpioPin0,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortB,GpioPin0,GpioAf3);
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortB,GpioPin11,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortB,GpioPin11,GpioAf3);
}



void UartInit(void)
{
    
    uint16_t u16Scnt = 0;
    stc_gpio_config_t stcGpioCfg;
    stc_lpuart_sclk_sel_t stcSclk;
    stc_lpuart_config_t  stcConfig;
    stc_lpuart_irq_cb_t stcLPUartIrqCb;
    stc_lpuart_multimode_t stcMulti;
    stc_lpuart_baud_t stcBaud;

    DDL_ZERO_STRUCT(stcConfig);
    DDL_ZERO_STRUCT(stcLPUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    DDL_ZERO_STRUCT(stcGpioCfg);
    DDL_ZERO_STRUCT(stcSclk);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);//赤a谷豕?㏒那?那㊣?車那1?邦
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart1,TRUE);
    
    Uart_PortInit();
    
    stcLPUartIrqCb.pfnRxIrqCb   = RxIntCallback;//?D??﹞t??o‘那y豕??迆米??﹞
    stcLPUartIrqCb.pfnTxIrqCb   = TxIntCallback;
    stcLPUartIrqCb.pfnRxFEIrqCb = ErrIntCallback;
    stcLPUartIrqCb.pfnPEIrqCb   = PErrIntCallBack;
    stcLPUartIrqCb.pfnCtsIrqCb  = CtsIntCallBack;
    stcConfig.pstcIrqCb = &stcLPUartIrqCb;
    stcConfig.bTouchNvic = TRUE;
  	if(TRUE == stcConfig.bTouchNvic)
	{
		EnableNvic(LPUART1_IRQn,IrqLevel3,TRUE);
	}
    stcConfig.enStopBit = LPUart1bit;//赤㏒?1??
    stcConfig.enRunMode = LPUartMode3;//?㏒那?3
    stcSclk.enSclk_Prs = LPUart4Or8Div;//2谷?迄﹞??米
    stcSclk.enSclk_sel =LPUart_Pclk;
    stcConfig.pstcLpuart_clk = &stcSclk;  
    

    stcMulti.enMulti_mode = LPUartNormal;
	LPUart_SetMultiMode(LPUART1,&stcMulti);//?角?迆?㏒那?谷豕??
  
    LPUart_SetMMDOrCk(LPUART1,LPUartDataOrAddr);//??D㏒?谷
    LPUart_Init(LPUART1, &stcConfig);
    
    LPUart_SetClkDiv(LPUART1,LPUart4Or8Div);//2谷?迄﹞??米
    
    stcBaud.u32Sclk = Sysctrl_GetPClkFreq();
    stcBaud.enRunMode = LPUartMode3;
    stcBaud.u32Baud = 115200;
    u16Scnt = LPUart_CalScnt(LPUART1,&stcBaud);//2“足??那????
    LPUart_SetBaud(LPUART1,u16Scnt);//2“足??那?米谷豕??
    
    LPUart_EnableIrq(LPUART1,LPUartRxIrq);//那1?邦?車那??D??
    LPUart_ClrStatus(LPUART1,LPUartRC);//???車那??D?????車
    LPUart_EnableFunc(LPUART1,LPUartRx);//那1?邦那y?Y那?﹞⊿
	
}


void UartDataParseHandler(void)
{
   if(++RxBufferHandler.RxBufferCycleIndex>=RxBufferCycleLength)
   	{
   	  RxBufferHandler.RxBufferCycleIndex=0;
   	}
   if(1==RxBufferHandler.RxBufferCycle[RxBufferHandler.RxBufferCycleIndex].HandlerFlag)
   	{
   	   RxBufferHandler.RxBufferCycle[RxBufferHandler.RxBufferCycleIndex].HandlerFlag=0;
	   switch(RxBufferHandler.RxBufferCycle[RxBufferHandler.RxBufferCycleIndex].RxBufferCopy[4])
	   	{
	   	   case Get_Device_System_Info:
		   	
		   	break;
           case Get_Device_Massage_Info:
		   	
		   	break;
           case Get_System_Para_Info:
		   	
		   	break;
           case Get_Heart_Rate_Info:
		   	
		   	break;
           case Enter_Firware_upgrade:
		   	
		   	break;
           case Set_Device_Massage_Info:
		   	
		   	break;
           case Set_Device_System_Info:
		   	
		   	break;
	   	}
   	}
}

void UartToSendData(u8 *p,u16 length)
{
  u16 i=0;
  u8 *datap;
  datap=p;
  for(i=0;i<length;i++)
  {
    LPUart_SendData(LPUART1,(*datap));
	datap++;
  }
}


