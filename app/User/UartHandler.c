#include "TypedefDef.h"
#include "Gpio.h"
#include "Uart.h"
#include "stdio.h"
#include "Global.h"
#include "UartHandler.h"
#include "Lpuart.h"


uint8_t u8TxData[] = {0x00,0x55,0X44,0X22,0X45,0X98};
uint8_t u8RxData;
uint8_t u8TxCnt=0,u8RxCnt=0;
#define LK_UART  LPUART0
#define LK_UART_IRQ  LPUART0_IRQn
#define LK_LPUART_CLK SysctrlPeripheralLpUart0
#define LK_SendData(data)  { M0P_LPUART0->SBUF = data; }
void TxIntCallback(void)
{

}
void RxIntCallback(void)
{
    u8RxData=LPUart_ReceiveData(LK_UART);
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
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);//设置外设时钟
    Sysctrl_SetPeripheralGate(LK_LPUART_CLK,TRUE);
    
    Uart_PortInit();
    
    stcLPUartIrqCb.pfnRxIrqCb   = RxIntCallback;//中断服务函数入口地址
    stcLPUartIrqCb.pfnTxIrqCb   = TxIntCallback;
    stcLPUartIrqCb.pfnRxFEIrqCb = ErrIntCallback;
    stcLPUartIrqCb.pfnPEIrqCb   = PErrIntCallBack;
    stcLPUartIrqCb.pfnCtsIrqCb  = CtsIntCallBack;
    stcConfig.pstcIrqCb = &stcLPUartIrqCb;
    stcConfig.bTouchNvic = TRUE;
  	if(TRUE == stcConfig.bTouchNvic)
	{
		EnableNvic(LK_UART_IRQ,IrqLevel3,TRUE);
	}
    stcConfig.enStopBit = LPUart1bit;//1位停止位
    stcConfig.enRunMode = LPUartMode3;//模式3
    stcSclk.enSclk_Prs = LPUart4Or8Div;//4分频
    stcSclk.enSclk_sel =LPUart_Pclk;//时钟
    stcConfig.pstcLpuart_clk = &stcSclk;  
    

    stcMulti.enMulti_mode = LPUartNormal; //正常工作模式
	LPUart_SetMultiMode(LK_UART,&stcMulti);//模式配置
  
    LPUart_SetMMDOrCk(LK_UART,LPUartDataOrAddr);//主机模式配置
    LPUart_Init(LK_UART, &stcConfig);
    
    LPUart_SetClkDiv(LK_UART,LPUart4Or8Div);//采样分频

    stcBaud.u32Sclk = Sysctrl_GetPClkFreq();
    stcBaud.enRunMode = LPUartMode3;
    stcBaud.u32Baud = 9600;
    u16Scnt = LPUart_CalScnt(LK_UART,&stcBaud);//波特率计算值
    LPUart_SetBaud(LK_UART,u16Scnt);//波特率配置
    
    LPUart_EnableIrq(LK_UART,LPUartRxIrq);//通信中断使能
    LPUart_ClrStatus(LK_UART,LPUartRC);//通信状态清除

  //	LPUart_EnableIrq(LK_UART,LPUartTxIrq);
    LPUart_EnableFunc(LK_UART,LPUartRx);//通信状态使能,接收和发送
  	UartToSendData(u8TxData,sizeof(u8TxData)); 

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
    LPUart_SendData(LPUART0,(*datap));
	datap++;
  }
}

