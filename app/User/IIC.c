#include "IIC.h"
#include "ddl.h"

_IIC_Device My_IIC_Device[]={
  	{GpioPortC,GpioPin15,GpioPortC,GpioPin14},  /// mpu6050 
  	{GpioPortB,GpioPin5,GpioPortB,GpioPin6},    ///  HRS3300
};


static void delayTous(u16 cnt)
{
   u8 i=0,j=0;
   for(i=0;i<cnt;i++)
   	{
   	    for(j=0;j<10;j++)
   	   	{;};
   	}
}

static u8 IIC_SDA_Input_Status(_IIC_Device *IIC_Device)
{
    return Gpio_GetInputIO(IIC_Device->Gpio_port_SDA,IIC_Device->Gpio_Pin_SDA);
}

static void IIC_SDA_Out_Dir(_IIC_Device *IIC_Device,en_gpio_dir_t OutDir)
{
   stc_gpio_config_t stcGpioCfg;
   stcGpioCfg.enCtrlMode=GpioFastIO;
   stcGpioCfg.enDir=OutDir;
   stcGpioCfg.enDrv=GpioDrvH;
   stcGpioCfg.enOD=GpioOdDisable;
   stcGpioCfg.enPuPd=GpioNoPuPd;
   Gpio_Init((IIC_Device->Gpio_port_SDA),(IIC_Device->Gpio_Pin_SDA),&stcGpioCfg);
}

static void IIC_SDA_Out_Status(_IIC_Device *IIC_Device,u8 OutValue)
{
  if(OutValue>0)
  	{
  	  Gpio_SetIO((IIC_Device->Gpio_port_SDA),(IIC_Device->Gpio_Pin_SDA));
  	}
  else
  	{
  	  Gpio_ClrIO((IIC_Device->Gpio_port_SDA),(IIC_Device->Gpio_Pin_SDA));
  	}
}

static void IIC_SCL_Out_Status(_IIC_Device *IIC_Device,u8 OutValue)
{
   if(OutValue>0)
   	{
   	   Gpio_SetIO((IIC_Device->Gpio_port_SCL),(IIC_Device->Gpio_Pin_SCL));
   	}
   else
   	{
   	  Gpio_ClrIO((IIC_Device->Gpio_port_SCL),(IIC_Device->Gpio_Pin_SCL));
   	}
}
static void IIC_Port_Init(_IIC_Device *IIC_Device,en_gpio_dir_t OutDir)
{
   stc_gpio_config_t stcGpioCfg;
   stcGpioCfg.enCtrlMode=GpioFastIO;
   stcGpioCfg.enDir=OutDir;
   stcGpioCfg.enDrv=GpioDrvH;
   stcGpioCfg.enOD=GpioOdDisable;
   stcGpioCfg.enPuPd=GpioNoPuPd;
   Gpio_Init((IIC_Device->Gpio_port_SDA),(IIC_Device->Gpio_Pin_SDA),&stcGpioCfg);
   Gpio_Init((IIC_Device->Gpio_port_SCL),(IIC_Device->Gpio_Pin_SCL),&stcGpioCfg);
   
}

void IIC_Init(_IIC_Device *IIC_Device)
{
  IIC_Port_Init(IIC_Device,GpioDirOut);
  Gpio_SetIO((IIC_Device->Gpio_port_SDA),(IIC_Device->Gpio_Pin_SDA));
  Gpio_SetIO((IIC_Device->Gpio_port_SCL),(IIC_Device->Gpio_Pin_SCL));
}


void IIC_Start(_IIC_Device *IIC_Device)
{
  IIC_SDA_Out_Dir(IIC_Device,GpioDirOut);
  IIC_SDA_Out_Status(IIC_Device,1);
  IIC_SCL_Out_Status(IIC_Device,1);
  delayTous(4);
  IIC_SDA_Out_Status(IIC_Device,0);
  delayTous(4);
  IIC_SCL_Out_Status(IIC_Device,0);
}

void IIC_Stop(_IIC_Device *IIC_Device)
{
   IIC_SDA_Out_Dir(IIC_Device,GpioDirOut);
   IIC_SCL_Out_Status(IIC_Device,0);
   IIC_SDA_Out_Status(IIC_Device,0);
   delayTous(4);
   IIC_SCL_Out_Status(IIC_Device,1);
   IIC_SDA_Out_Status(IIC_Device,1);
   delayTous(4);
   IIC_SCL_Out_Status(IIC_Device,0);
}

u8 IIC_Waite_ACK(_IIC_Device *IIC_Device)
{
   u8 ErrorTime=0;
   IIC_SDA_Out_Dir(IIC_Device,GpioDirIn);
   IIC_SCL_Out_Status(IIC_Device,1);
   delayTous(1);
   IIC_SDA_Out_Status(IIC_Device,1);
   delayTous(1);
   while(IIC_SDA_Input_Status(IIC_Device))
   	{
   	  ErrorTime++;
	  if(ErrorTime>250)
	  	{
	  	  IIC_Stop(IIC_Device);
	  	  return 1;
	  	}
   	}
   IIC_SCL_Out_Status(IIC_Device,0);
   return 0;
}

void IIC_ACK(_IIC_Device *IIC_Device)
{
  IIC_SCL_Out_Status(IIC_Device,0);
  IIC_SDA_Out_Dir( IIC_Device,GpioDirOut);
  IIC_SDA_Out_Status(IIC_Device,0);
  delayTous(2);
  IIC_SCL_Out_Status(IIC_Device,1);
  delayTous(2);
  IIC_SCL_Out_Status( IIC_Device,0);
}

void IIC_NACK(_IIC_Device *IIC_Device)
{
  IIC_SCL_Out_Status(IIC_Device,0);
  IIC_SDA_Out_Dir( IIC_Device,GpioDirOut);
  IIC_SDA_Out_Status(IIC_Device,1);
  delayTous(2);
  IIC_SCL_Out_Status(IIC_Device,1);
  delayTous(2);
  IIC_SCL_Out_Status( IIC_Device,0);
}


void IIC_Send_Byte(_IIC_Device *IIC_Device,u8 TxD)
{
  u8 i=0;
  IIC_SDA_Out_Dir(IIC_Device,GpioDirOut);
  IIC_SCL_Out_Status(IIC_Device,0);
  for(i=0;i<8;i++)
  {
  	if((TxD&0x80)>>7)
  	{
  	   IIC_SDA_Out_Status(IIC_Device,1);
  	}
	else
	{
	   IIC_SDA_Out_Status(IIC_Device,0);
	}

	TxD<<=1;
	delayTous(2);
	IIC_SCL_Out_Status(IIC_Device,1);
	delayTous(2);
	IIC_SCL_Out_Status(IIC_Device,0);
	delayTous(2);
  }
}

u8 IIC_Read_Byte(_IIC_Device *IIC_Device,u8 ack)
{
   u8 i=0,recData=0;
   IIC_SDA_Out_Dir(IIC_Device,GpioDirIn);
   for(i=0;i<8;i++)
   {
   	  IIC_SCL_Out_Status(IIC_Device,0);
	  delayTous(2);
	  IIC_SCL_Out_Status(IIC_Device,1);
	  recData<<=1;
	  if(IIC_SDA_Input_Status(IIC_Device))
	   {
	  	 recData++;
	   }
	  delayTous(1);
   }
   if(!ack)
   	{
   	  IIC_NACK(IIC_Device);
   	}
   else
   	{
   	  IIC_ACK(IIC_Device);
   	}
   return recData;
}



























