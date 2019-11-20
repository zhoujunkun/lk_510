#include "HC595.h"
#include "Gpio.h"
#include "ddl.h"
#include "TypedefDef.h"
#include "ddl.h"

static void HC595_SendByte(u8 data);


/// SHCP  clk  
///  STCP  latch


#define HC595DataGpioPort  GpioPortA
#define HC595DataGpioPin   GpioPin7
#define HC595ClkGpioPort    GpioPortB
#define HC595ClkGpioPin     GpioPin1
#define HC595LatchGpioPort   GpioPortB
#define HC595LatchGpioPin   GpioPin0


static volatile u8 HC595SaveStatus_Bit=0;

#define Motor_Id 2
#define Led_Blue_Id 5
#define Led_Red_Id 3
#define Led_Green_Id 4
#define Heat_Port_Id 6

static void delay_us_ms(u16 cnt)
{
   u16 i=0,j=0;
   for(i=0;i<cnt;i++)
   	{
   	   for(j=0;j<5;j++)
   	   	{
   	   	  ;

   	   	}
	   	;
   	}
}


void HC595_Init(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
   DDL_ZERO_STRUCT(stcGpioCfg);
   stcGpioCfg.enDir=GpioDirOut;
   stcGpioCfg.enDrv=GpioDrvH;
   stcGpioCfg.enOD=GpioOdDisable;
   stcGpioCfg.enPuPd=GpioNoPuPd;
   stcGpioCfg.enCtrlMode=GpioAHB;
   Gpio_Init(HC595DataGpioPort,HC595DataGpioPin,&stcGpioCfg);
   Gpio_Init(HC595ClkGpioPort,HC595ClkGpioPin,&stcGpioCfg);
   Gpio_Init(HC595LatchGpioPort,HC595LatchGpioPin,&stcGpioCfg);

   Led_Blue_SetIO();
   Led_Green_ClrIO();
   Led_Red_SetIO();

   Heater_To_Port_Close;
   
   	
}



static void HC595_SendByte(u8 data)
{
    u8 i=0;
	for(i=0;i<8;i++)
	{
	  Gpio_SetIO(HC595ClkGpioPort,HC595ClkGpioPin);
	  if((data&0x80)!=0)
	  	{
	  	  Gpio_SetIO(HC595DataGpioPort,HC595DataGpioPin);
	  	}
	  else
	  	{
	  	  Gpio_ClrIO(HC595DataGpioPort,HC595DataGpioPin);
	  	}
	  data<<=1;
	  delay_us_ms(20);
	  Gpio_ClrIO(HC595ClkGpioPort,HC595ClkGpioPin);
	  delay_us_ms(20);
	}
	Gpio_SetIO(HC595LatchGpioPort,HC595LatchGpioPin);
	delay_us_ms(20);
	Gpio_ClrIO(HC595LatchGpioPort,HC595LatchGpioPin);
}

void Motor_Vibration_SetIO(void)
{
   HC595SaveStatus_Bit|=(1<<Motor_Id);
   HC595_SendByte(HC595SaveStatus_Bit);
}
void Motor_Vibration_ClrIO(void)
{
   HC595SaveStatus_Bit&=(~(1<<Motor_Id));
   HC595_SendByte(HC595SaveStatus_Bit);
}

void Led_Blue_SetIO(void)
{
   HC595SaveStatus_Bit|=(1<<Led_Blue_Id);
   HC595_SendByte(HC595SaveStatus_Bit);
}

void Led_Blue_ClrIO(void)
{
   HC595SaveStatus_Bit&=(~(1<<Led_Blue_Id));
   HC595_SendByte(HC595SaveStatus_Bit); 
}

void Led_Green_SetIO(void)
{
   HC595SaveStatus_Bit|=(1<<Led_Green_Id);
   HC595_SendByte(HC595SaveStatus_Bit);
}

void Led_Green_ClrIO(void)
{
   HC595SaveStatus_Bit&=(~(1<<Led_Green_Id));
   HC595_SendByte(HC595SaveStatus_Bit);
}


void Led_Red_SetIO(void)
{
   HC595SaveStatus_Bit|=(1<<Led_Red_Id);
   HC595_SendByte(HC595SaveStatus_Bit); 
}

void Led_Red_ClrIO(void)
{
   HC595SaveStatus_Bit&=(~(1<<Led_Red_Id));
   HC595_SendByte(HC595SaveStatus_Bit);
}

void Heater_To_Port_SetIO(void)
{
   HC595SaveStatus_Bit|=(1<<Heat_Port_Id);
   HC595_SendByte(HC595SaveStatus_Bit);
}

void Heater_To_Port_ClrIO(void)
{
   HC595SaveStatus_Bit&=(~(1<<Heat_Port_Id));
   HC595_SendByte(HC595SaveStatus_Bit);
}

void Led_Bright_Red_Close_Blue_Green(void)
{
    
	HC595SaveStatus_Bit&=(~(1<<Led_Red_Id));
	HC595SaveStatus_Bit|=(((1<<Led_Blue_Id)|(1<<Led_Green_Id)));
	HC595_SendByte(HC595SaveStatus_Bit);
}

void Led_Bright_Blue_Close_Red_Green(void)
{
    HC595SaveStatus_Bit&=(~(1<<Led_Blue_Id));
	HC595SaveStatus_Bit=(((1<<Led_Red_Id)|(1<<Led_Green_Id)));
	HC595_SendByte(HC595SaveStatus_Bit);
}

void Led_Bright_Green_Close_Blue_Red(void)
{
    HC595SaveStatus_Bit&=(~(1<<Led_Green_Id));
	HC595SaveStatus_Bit|=(((1<<Led_Red_Id)|(1<<Led_Blue_Id)));
	HC595_SendByte(HC595SaveStatus_Bit);
}

void Led_Blue_Close(void)
{
    Led_Blue_ClrIO();
}

void Led_Red_Close(void)
{
    Led_Red_ClrIO();
}

void Led_Green_Close(void)
{
    Led_Green_ClrIO();
}

void Led_All_Close(void)
{
   HC595SaveStatus_Bit|=(((1<<Led_Green_Id)|(1<<Led_Blue_Id)|(1<<Led_Red_Id)));
   HC595_SendByte(HC595SaveStatus_Bit);
}




