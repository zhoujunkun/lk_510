#include "IIC.h"
#include "ddl.h"
#include "Mpu6050.h"
#include <math.h>

static u8 Mpu6050_writer_Byte(u8 Reg,u8 data);
static u8 MPU6050_Read_Byte(u8 Reg);
// u8 MPU6050_Write_Len(u8 Addr,u8 Reg,u8 Len,u8 *Buf);
// u8 MPU6050_Read_Len(u8 Addr,u8 Reg,u8 Len,u8 *Buf);

static void delayTms(u16 cnt)
{
   u16 i=0,j=0;
   for(i=0;i<cnt;i++)
   	{
   	   for(j=0;j<1000;j++)
   	   	{
   	   	  ;
   	   	}
	   ;
   	}
}


u8 MPU6050_Init(void)
{
   u8 res=0;
   IIC_Init(&My_IIC_Device[0]);
   Mpu6050_writer_Byte(MPU_PWR_MGMT1_REG,0x80);
   delayTms(100);
   Mpu6050_writer_Byte(MPU_PWR_MGMT1_REG,0x00);
   MPU6050_Set_Gyro_Fsr(3);
   MPU6050_Set_Accel_Fsr(2);
   MPU6050_Set_Rate(50);
   Mpu6050_writer_Byte(MPU_INT_EN_REG,0x00);
   Mpu6050_writer_Byte(MPU_USER_CTRL_REG,0x00);
   Mpu6050_writer_Byte(MPU_FIFO_EN_REG,0x00);
   Mpu6050_writer_Byte(MPU_INTBP_CFG_REG,0x80);
   res=MPU6050_Read_Byte(MPU_DEVICE_ID_REG);
   if(res==MPU_ADDR)
   	{
   	  Mpu6050_writer_Byte(MPU_PWR_MGMT1_REG,0x01);
	  Mpu6050_writer_Byte(MPU_PWR_MGMT2_REG,0x00);
	  MPU6050_Set_Rate(50);
	  return 0;
   	}
   return 1;
}

static u8 Mpu6050_writer_Byte(u8 Reg,u8 data)
{
   IIC_Start(&My_IIC_Device[0]);
   IIC_Send_Byte(&My_IIC_Device[0],(MPU_ADDR<<1|0));
   if(IIC_Waite_ACK(&My_IIC_Device[0]))
   	{
   	  IIC_Stop(&My_IIC_Device[0]);
	  return 1;
   	}
   IIC_Send_Byte(&My_IIC_Device[0],Reg);
   IIC_Waite_ACK(&My_IIC_Device[0]);
   IIC_Send_Byte(&My_IIC_Device[0],data);
   if(IIC_Waite_ACK(&My_IIC_Device[0]))
   	{
   	  IIC_Stop(&My_IIC_Device[0]);
	  return 1;
   	}
    IIC_Stop(&My_IIC_Device[0]);
	return 0;
}

static u8 MPU6050_Read_Byte(u8 Reg)
{
   u8 RegData=0;
   IIC_Start(&My_IIC_Device[0]);
   IIC_Send_Byte(&My_IIC_Device[0],((MPU_ADDR<<1)|0));
   IIC_Waite_ACK(&My_IIC_Device[0]);
   IIC_Send_Byte(&My_IIC_Device[0],Reg);
   IIC_Waite_ACK(&My_IIC_Device[0]);
   IIC_Start(&My_IIC_Device[0]);
   IIC_Send_Byte(&My_IIC_Device[0],((MPU_ADDR<<1)|1));
   IIC_Waite_ACK(&My_IIC_Device[0]);
   RegData=IIC_Read_Byte(&My_IIC_Device[0],0);
   IIC_Stop(&My_IIC_Device[0]);
   return RegData;
}

 u8 MPU6050_Read_Len(u8 Addr,u8 Reg,u8 Len,u8 *Buf)
{
  IIC_Start(&My_IIC_Device[0]);
  IIC_Send_Byte(&My_IIC_Device[0],(Addr<<1)|0);
  if(IIC_Waite_ACK(&My_IIC_Device[0]))
   {
     IIC_Stop(&My_IIC_Device[0]);
	 return 1;
   }

   IIC_Send_Byte(&My_IIC_Device[0],Reg);
   IIC_Waite_ACK(&My_IIC_Device[0]);
   IIC_Start(&My_IIC_Device[0]);
   IIC_Send_Byte(&My_IIC_Device[0],(Addr<<1)|1);
   IIC_Waite_ACK(&My_IIC_Device[0]);
   while(Len)
   	{
   	  if(Len==1)
	  	*Buf=IIC_Read_Byte(&My_IIC_Device[0],0);
	  else
	  	*Buf=IIC_Read_Byte(&My_IIC_Device[0],1);
	  Len--;
	  Buf++;
   	}
   IIC_Stop(&My_IIC_Device[0]);
   return 0;
}

u8 MPU6050_Write_Len(u8 Addr,u8 Reg,u8 Len,u8 *Buf)
{   
   u8 i=0;
   IIC_Start(&My_IIC_Device[0]);
   IIC_Send_Byte(&My_IIC_Device[0],(Addr<<1)|0);
   if(IIC_Waite_ACK(&My_IIC_Device[0])>0)
   	{
   	  IIC_Stop(&My_IIC_Device[0]);
	  return 1;
   	}
   IIC_Send_Byte(&My_IIC_Device[0],Reg);
   IIC_Waite_ACK(&My_IIC_Device[0]);
   for(i=0;i<Len;i++)
   {
   	  IIC_Send_Byte(&My_IIC_Device[0],*Buf);
	  if(IIC_Waite_ACK(&My_IIC_Device[0])>0)
	  	{
	  	  IIC_Stop(&My_IIC_Device[0]);
		  return 1;
	  	}
   }
   IIC_Stop(&My_IIC_Device[0]);
   return 0;
}

u8 MPU6050_Set_Gyro_Fsr(u8 fsr)
{
  return Mpu6050_writer_Byte(MPU_GYRO_CFG_REG,fsr<<3);
}

u8 MPU6050_Set_Accel_Fsr(u8 fsr)
{
  return Mpu6050_writer_Byte(MPU_ACCEL_CFG_REG,fsr<3);
}

u8 MPU6050_Set_LPF(u16 lpf)
{
    u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6;
	return Mpu6050_writer_Byte(MPU_CFG_REG,data);
}

u8 MPU6050_Set_Rate(u16 rate)
{
   u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=Mpu6050_writer_Byte(MPU_SAMPLE_RATE_REG,data);
 	return MPU6050_Set_LPF(rate/2);
}
short MPU6050_Get_Temperature(void)
{
   u8 Buff[2];
   float temp;
   short raw;
   MPU6050_Write_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,Buff);
   raw=((u16)Buff[0]<<8|Buff[1]);
   temp=36.53+((double)raw)/340;
   return temp*100;  ///  扩大一百倍
}

u8 MPU6050_Get_Gyroscope(u16 *ax,u16 *ay,u16 *az)
{
    u8 Buff[6],Res;
	Res=MPU6050_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,Buff);
	if(Res==0)
	{
	   *ax=(((u16)Buff[0]<<8)|Buff[1]);
	   *ay=(((u16)Buff[2]<<8)|Buff[3]);
	   *az=(((u16)Buff[4]<<8)|Buff[5]);
	}
	return Res;
}



