#include "Key.h"
#include "gpio.h"
#include "Global.h"

_keyHandler keyDataHandler;
_Ems_Status_Check Ems_Status_Check;
_Chg_Status_Check Chg_Status_CheckHandler;
_keyHandler HallSwitchScan;

#define Key_Port1  GpioPortA
#define Key_Pin1   GpioPin12

#define Key_Port2  GpioPortA
#define Key_Pin2   GpioPin13

#define Key_Port3  GpioPortA
#define Key_Pin3   GpioPin14


#define Ems_Status_shortTime 80

#define HallSwitchPort GpioPortD
#define HallSwitchPin GpioPin0


#define Battery_Chg_Status_Port GpioPortD
#define Battery_Chg_Status_Pin GpioPin3





void Gpio_IRQHandler(uint8_t u8Param)
{
    #if 0
    u8 Para=0;
    if(GpioPortA==HallSwitchPort)
    {
      Para=0;
    }
	else if(GpioPortB==HallSwitchPort)
	{
	  Para=1;
	}
	else if(GpioPortC==HallSwitchPort)
	{
	  Para=2;
	}
	else
	{
	  Para=3;
	}
    if(Para == u8Param)
	#endif
    {
        if(TRUE == Gpio_GetIrqStatus(HallSwitchPort, HallSwitchPin))
        {
            Gpio_ClearIrq(HallSwitchPort, HallSwitchPin);
        }
    }

    if(TRUE==Gpio_GetIrqStatus(Battery_Chg_Status_Port,Battery_Chg_Status_Pin))
    {
    	   Gpio_ClearIrq(Battery_Chg_Status_Port,Battery_Chg_Status_Pin);
    }

	if(TRUE==Gpio_GetIrqStatus(Key_Port1,Key_Pin1))
	 {
		  Gpio_ClearIrq(Key_Port1,Key_Pin1);  
	 }

	if(TRUE==Gpio_GetIrqStatus(Key_Port2,Key_Pin2))
	 {
	      Gpio_ClearIrq(Key_Port2,Key_Pin2);
	 }

	if(TRUE==Gpio_GetIrqStatus(Key_Port3,Key_Pin3))
	 {
	      Gpio_ClearIrq(Key_Port3,Key_Pin3);
	 }

	if(TRUE==Gpio_GetIrqStatus(EMS_Check_Port,EMS_Check_Pin))
	{
		Gpio_ClearIrq(EMS_Check_Port,EMS_Check_Pin);  
		Ems_Status_Check.Ems_CkIntFlag=TRUE;
	}

	
}   


void KeyInit(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);  //打开外设时钟
   Sysctrl_SetFunc(SysctrlSWDUseIOEn,TRUE);
   stcGpioCfg.enDir = GpioDirIn;  //输入
   stcGpioCfg.enDrv = GpioDrvH;
   stcGpioCfg.enPuPd = GpioPu;
   stcGpioCfg.enOD = GpioOdDisable;
   stcGpioCfg.enCtrlMode = GpioAHB;
   Gpio_Init(Key_Port1, Key_Pin1, &stcGpioCfg);
   Gpio_Init(Key_Port2, Key_Pin2, &stcGpioCfg);
   Gpio_Init(Key_Port3, Key_Pin3, &stcGpioCfg);
}

void KeyInit2(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
   Sysctrl_SetFunc(SysctrlSWDUseIOEn,TRUE);
   stcGpioCfg.enDir = GpioDirIn;
   stcGpioCfg.enDrv = GpioDrvH;
   stcGpioCfg.enPuPd = GpioPu;
   stcGpioCfg.enOD = GpioOdDisable;
   stcGpioCfg.enCtrlMode = GpioAHB;
   Gpio_Init(Key_Port1, Key_Pin1, &stcGpioCfg);
   Gpio_Init(Key_Port2, Key_Pin2, &stcGpioCfg);
   Gpio_Init(Key_Port3, Key_Pin3, &stcGpioCfg);
}


static void KeyEnableIRQ(void)
{
   Gpio_SfIrqModeConfig(GpioSfIrqDpslpMode);
   Gpio_EnableIrq(Key_Port1,Key_Pin1,GpioIrqFalling);
   if(Key_Port1==GpioPortA)
   	{
   	  EnableNvic(PORTA_IRQn,IrqLevel3,TRUE);
   	}
   else if(Key_Port1==GpioPortB)
   	{
   	   EnableNvic(PORTB_IRQn,IrqLevel3,TRUE); 
   	}
   else if(Key_Port1==GpioPortC)
   	{
   	  EnableNvic(PORTC_IRQn,IrqLevel3,TRUE);  
   	}
   else
   	{
   	   EnableNvic(PORTD_IRQn,IrqLevel3,TRUE);  
   	}
   Gpio_EnableIrq(Key_Port2,Key_Pin2,GpioIrqFalling);
   if(Key_Port2==GpioPortA)
   	{
   	  EnableNvic(PORTA_IRQn,IrqLevel3,TRUE);
   	}
   else if(Key_Port2==GpioPortB)
   	{
   	   EnableNvic(PORTB_IRQn,IrqLevel3,TRUE); 
   	}
   else if(Key_Port2==GpioPortC)
   	{
   	  EnableNvic(PORTC_IRQn,IrqLevel3,TRUE);  
   	}
   else
   	{
   	   EnableNvic(PORTD_IRQn,IrqLevel3,TRUE);  
   	}
   Gpio_EnableIrq(Key_Port3,Key_Pin3,GpioIrqFalling);
   if(Key_Port3==GpioPortA)
   	{
   	  EnableNvic(PORTA_IRQn,IrqLevel3,TRUE);
   	}
   else if(Key_Port3==GpioPortB)
   	{
   	   EnableNvic(PORTB_IRQn,IrqLevel3,TRUE); 
   	}
   else if(Key_Port3==GpioPortC)
   	{
   	  EnableNvic(PORTC_IRQn,IrqLevel3,TRUE);  
   	}
   else
   	{
   	   EnableNvic(PORTD_IRQn,IrqLevel3,TRUE);  
   	}
}

static void KeyDisableIRQ(void)
{
   Gpio_DisableIrq(Key_Port1,Key_Pin1,GpioIrqFalling);
   Gpio_DisableIrq(Key_Port2,Key_Pin2,GpioIrqFalling);
   Gpio_DisableIrq(Key_Port3,Key_Pin3,GpioIrqFalling);
}

void keyScan(void)
{
   static u8 OldKeyValue=0;
   volatile u32 temp=0;
   if(Gpio_GetInputIO(Key_Port1,Key_Pin1)==0)   ///   暂时 只用这个按键
   	{
   	  temp=1;
   	}
   else
   	{
   	  temp=0;
   	}
  // temp=0;
   if(Gpio_GetInputIO(Key_Port2,Key_Pin2)==0)
   	{
   	  temp|=1<<1;
   	}
   else
   	{
   	  temp&=~(1<<1);
   	}
   if(Gpio_GetInputIO(Key_Port3,Key_Pin3)==0)
   	{
   	  temp|=1<<2;
   	}
   else
   	{
   	  temp&=~(1<<2);
   	}

   
   if(keyDataHandler.KeyTemp!=temp)
   	{
   	   keyDataHandler.KeyBuffer=temp;
	   keyDataHandler.KeyCount=0;
	   keyDataHandler.KeyTemp=temp;
   	}
   else if(++keyDataHandler.KeyCount>=20)
   	{
   	   if(keyDataHandler.KeyBuffer!=keyDataHandler.KeyBufferOld)
   	   	{
   	   	   keyDataHandler.KeyBufferOld=keyDataHandler.KeyBuffer;
		   keyDataHandler.keyTime=0;
		   keyDataHandler.KeyData=keyDataHandler.KeyBuffer;
		  
		  if(1==key_delay_init.key_init_Flag)
		  	{
			   if(keyDataHandler.KeyBuffer>0)
			   	{
			   	  OldKeyValue=keyDataHandler.KeyBuffer;
			   	}
		  	}
   	   	}
   	}

	   if(0==keyDataHandler.KeyBuffer)
	   	{
	   	  keyDataHandler.KeyOld=OldKeyValue;
		  OldKeyValue=KEY_OFF;
	   	}

    
}



void EMS_Port_Check_Pin_Init(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
   stcGpioCfg.enDir = GpioDirIn;
   stcGpioCfg.enDrv = GpioDrvH;
   stcGpioCfg.enPuPd = GpioPu;
   stcGpioCfg.enOD = GpioOdDisable;
   stcGpioCfg.enCtrlMode = GpioAHB;
   Gpio_Init(EMS_Check_Port, EMS_Check_Pin, &stcGpioCfg);
   Gpio_EnableIrq(EMS_Check_Port,EMS_Check_Pin,GpioIrqFalling);
   if(EMS_Check_Port==GpioPortA)
   	{
   	  EnableNvic(PORTA_IRQn,IrqLevel3,TRUE);
   	}
   else if(EMS_Check_Port==GpioPortB)
   	{
   	   EnableNvic(PORTB_IRQn,IrqLevel3,TRUE); 
   	}
   else if(EMS_Check_Port==GpioPortC)
   	{
   	  EnableNvic(PORTC_IRQn,IrqLevel3,TRUE);  
   	}
   else
   	{
   	   EnableNvic(PORTD_IRQn,IrqLevel3,TRUE);  
   	}  
   
}

void EMS_Port_Pin_Enable_IRQ(void)
{
    Gpio_EnableIrq(EMS_Check_Port,EMS_Check_Pin,GpioIrqFalling);
   if(EMS_Check_Port==GpioPortA)
   	{
   	  EnableNvic(PORTA_IRQn,IrqLevel3,TRUE);
   	}
   else if(EMS_Check_Port==GpioPortB)
   	{
   	   EnableNvic(PORTB_IRQn,IrqLevel3,TRUE); 
   	}
   else if(EMS_Check_Port==GpioPortC)
   	{
   	  EnableNvic(PORTC_IRQn,IrqLevel3,TRUE);  
   	}
   else
   	{
   	   EnableNvic(PORTD_IRQn,IrqLevel3,TRUE);  
   	}  
}

void EMS_Port_Pin_Disable_IRQ(void)
{
   Gpio_DisableIrq(EMS_Check_Port,EMS_Check_Pin,GpioIrqFalling);
    
}

void EMS_Port_Pin_Status(void)
{
  volatile u8 Temp=0;
  //if(Gpio_GetInputIO(EMS_Check_Port,EMS_Check_Pin)==0)
   if(TRUE==Ems_Status_Check.Ems_Check_Flag)
   	{
   	   Ems_Status_Check.Ems_Check_Flag=FALSE;
	   if(Ems_Status_Check.Ems_CkIntFlag>0)
	  	{
	  	  Ems_Status_Check.Ems_CkIntFlag=0;
	  	  Temp=1;
	  	}
	  else
	  	{
	  	  Temp=0;
	  	}
	  if(Temp!=Ems_Status_Check.Ems_CkTemp)
	  	{
	  	   Ems_Status_Check.Ems_CkTemp=Temp;
		   Ems_Status_Check.Ems_CkCount=0;
	  	}
	  else if(++Ems_Status_Check.Ems_CkCount>=6)
	  	{
	  	  if(Ems_Status_Check.Ems_CkBuffer!=Ems_Status_Check.Ems_CkTemp)
	  	   	{
	  	   	   Ems_Status_Check.Ems_CkBuffer=Ems_Status_Check.Ems_CkTemp;
			   Ems_Status_Check.Ems_CkTime=0;
	  	   	}
	  	 
	  	}

	   if(Ems_Status_Check.Ems_CkBuffer==0)
	  	  	{
	  	  	    if(Ems_Status_Check.Ems_CkTime>Ems_Status_shortTime)
	  	  	      {
	  	  	        Ems_Status_Check.Ems_CkData=Ems_Status_Check.Ems_CkBuffer;
	  	  	      }
	  	  	}
		  else
		  	{
		  
			  	   Ems_Status_Check.Ems_CkData=Ems_Status_Check.Ems_CkBuffer;
			  	
		  	}
	  
	    if(1==Ems_Status_Check.Ems_CkData)
	    {
	    	MassageHandler.ifEmsCheck=TRUE;
	    }
	  else
		{
		   MassageHandler.ifEmsCheck=FALSE;
		}
   	}
}

#define Batter_Chg_Port GpioPortD
#define Batter_Chg_Pin GpioPin1

void Battery_Chg_Compl_Status_Init(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
   stcGpioCfg.enDir = GpioDirIn;
   stcGpioCfg.enDrv = GpioDrvL;
   stcGpioCfg.enPuPd = GpioNoPuPd;
   stcGpioCfg.enOD = GpioOdDisable;
   stcGpioCfg.enCtrlMode = GpioAHB;
   Gpio_Init(Batter_Chg_Port, Batter_Chg_Pin, &stcGpioCfg);
}

u8 Battery_Chg_Compl_Status_Check(void)
{
     u8 Temp=0;
	  static u8 TempErrcount=0;
	  if(Gpio_GetInputIO(Batter_Chg_Port,Batter_Chg_Pin)==0)
	  	{
	  	  Temp=0;
	  	}
	  else
	  	{
	  	  Temp=1;
	  	} 
       
	  if(0==Temp)
	  	{
	  	   if(++TempErrcount>=3)
	  	   	{
	  	   	  TempErrcount=0;
			     return 1;
	  	   	}
	  	}
	  else
	  	{
	  	   TempErrcount=0;
	  	}
	  return 0;
}



void Battery_Chg_Status_Pin_Init(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
   stcGpioCfg.enDir = GpioDirIn;
   stcGpioCfg.enDrv = GpioDrvH;
   stcGpioCfg.enPuPd = GpioNoPuPd;
   stcGpioCfg.enOD = GpioOdDisable;
   stcGpioCfg.enCtrlMode = GpioFastIO;
   Gpio_Init(Battery_Chg_Status_Port, Battery_Chg_Status_Pin, &stcGpioCfg);
}

void Battery_Chg_Status_Pin_Scan(void)
{
    u8 Temp=0;
	static u8 status_checkBuffOld=0;
    if(Gpio_GetInputIO(Battery_Chg_Status_Port,Battery_Chg_Status_Pin)==1)
    {
      Temp=1;
    }
	else
	{
	  Temp=0;
	}

	if(Chg_Status_CheckHandler.Status_CheckTemp!=Temp)
	{
	   Chg_Status_CheckHandler.Status_CheckTemp=Temp;
	   Chg_Status_CheckHandler.status_CheckCount=0;
	   Chg_Status_CheckHandler.Status_CheckBuff=Temp;
	}
	else if(++Chg_Status_CheckHandler.status_CheckCount>=10)
	{
	   if(Chg_Status_CheckHandler.Status_CheckBuff!=Chg_Status_CheckHandler.status_CheckBuffOld)
	   	{
	   	  Chg_Status_CheckHandler.status_CheckBuffOld=Chg_Status_CheckHandler.Status_CheckBuff;
		  Chg_Status_CheckHandler.status_CheckData=Chg_Status_CheckHandler.Status_CheckBuff;
	   	}
	}
	if(Chg_Status_CheckHandler.status_CheckData==TRUE)
	  {
		  MassageHandler.ChargeAndMassageStatus=ChargeStatusIng;
		  
	  }

	if(status_checkBuffOld!=Chg_Status_CheckHandler.status_CheckData)
	 {
	    if(status_checkBuffOld==1)
	    {
	      MassageHandler.ChargeAndMassageStatus=ChargeStatusNo; 
	    }
		status_checkBuffOld=Chg_Status_CheckHandler.status_CheckData;
	 }

}

static void Battery_Chg_Status_Enable_IRQ(void)
{
   Battery_Chg_Status_Pin_Init();
   Gpio_EnableIrq(Battery_Chg_Status_Port,Battery_Chg_Status_Pin,GpioIrqRising);
   if(Battery_Chg_Status_Port==GpioPortA)
   	{
   	  EnableNvic(PORTA_IRQn,IrqLevel3,TRUE);
   	}
   else if(Battery_Chg_Status_Port==GpioPortB)
   	{
   	   EnableNvic(PORTB_IRQn,IrqLevel3,TRUE); 
   	}
   else if(Battery_Chg_Status_Port==GpioPortC)
   	{
   	  EnableNvic(PORTC_IRQn,IrqLevel3,TRUE);  
   	}
   else
   	{
   	   EnableNvic(PORTD_IRQn,IrqLevel3,TRUE);  
   	}  
}

static void Battery_Chg_Status_Disable_IRQ(void)
{
   Gpio_DisableIrq(Battery_Chg_Status_Port,Battery_Chg_Status_Pin,GpioIrqRising); 
}

void HallSwitchTrigTouchKeyInit(void)
{
  stc_gpio_config_t stcGpioCfg;
  DDL_ZERO_STRUCT(stcGpioCfg);
  stcGpioCfg.enDir = GpioDirIn;
  stcGpioCfg.enDrv = GpioDrvH;
  stcGpioCfg.enPuPd = GpioNoPuPd;
  stcGpioCfg.enOD = GpioOdDisable;
  stcGpioCfg.enCtrlMode =GpioAHB;
  Gpio_Init(HallSwitchPort,HallSwitchPin,&stcGpioCfg);
 
}

static void HallSwitchTrigInterrupteIRQEnable(void)
{
  Gpio_SfIrqModeConfig(GpioSfIrqDpslpMode);
  Gpio_EnableIrq(HallSwitchPort,HallSwitchPin,GpioIrqRising);
  if(GpioPortA==HallSwitchPort)
    {
      EnableNvic(PORTA_IRQn,IrqLevel3,TRUE);
    }
	else if(GpioPortB==HallSwitchPort)
    {
	  EnableNvic(PORTB_IRQn,IrqLevel3,TRUE);
	}
	else if(GpioPortC==HallSwitchPort)
	{
	  EnableNvic(PORTC_IRQn,IrqLevel3,TRUE);
	}
	else
	{
	  EnableNvic(PORTD_IRQn,IrqLevel3,TRUE);
	}
}
////  霍尔开关没有接触时是高电平，接触后是低电平
void HallSwitchStatusScan(void)
{
   u8 temp;
   if(Gpio_GetInputIO(HallSwitchPort,HallSwitchPin)==0)
   	{
   	  temp=0;
   	}
   else
   	{
   	  temp=1;
   	}
   if(temp!=HallSwitchScan.KeyTemp)
   	{
   	   HallSwitchScan.KeyTemp=temp;
	   HallSwitchScan.KeyCount=0;
	   HallSwitchScan.KeyBuffer=temp;
   	}
   else if(++HallSwitchScan.KeyCount>=400)
   	{
   	    if(HallSwitchScan.KeyBuffer!=HallSwitchScan.KeyBufferOld)
   	     {
   	         HallSwitchScan.KeyBufferOld=HallSwitchScan.KeyBuffer;
			 HallSwitchScan.keyTime=0;
			 HallSwitchScan.KeyData=HallSwitchScan.KeyBuffer;

			 if(HallSwitchScan.KeyData==FALSE)
		      {
				  if(ChargeStatusIng!=MassageHandler.ChargeAndMassageStatus&&
				  	ChargeStatusComplete!=MassageHandler.ChargeAndMassageStatus)
				  {
				    LowPowerControl.LowPowerFlag=LowPowerImmedShutdown;
				  }
		      }
			if(HallSwitchScan.KeyData==TRUE)
			  {
			     if(LowPowerNoCancelShutdown==LowPowerControl.LowPowerFlag)
			       {
			         LowPowerControl.LowPowerFlag=LowPowerStopStatus;
			       }
				 if(Motor_Vibr_ShutDown==Motor_Vibr_Control.Motor_Vibr_flag)
				   {
				 	 Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_EnterStopStatus;
				   }
			  }
   	     }
   	}
}

static void HallSwitchTrigTouchKeyInitDisable(void)
{
  Gpio_DisableIrq(HallSwitchPort,HallSwitchPin,GpioIrqRising);
}


void ExtTrigInterrupteRouseEnable(void)
{
   KeyEnableIRQ();
   Battery_Chg_Status_Enable_IRQ();
   HallSwitchTrigInterrupteIRQEnable();
}

void ExtTrigInterrupteRouseDisable(void)
{
    KeyDisableIRQ();
	Battery_Chg_Status_Disable_IRQ();
	HallSwitchTrigTouchKeyInitDisable();
}


