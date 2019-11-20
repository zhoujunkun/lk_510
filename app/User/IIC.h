#ifndef __IIC__HH__
#define __IIC__HH__
#include "Global.h"
#include "TypedefDef.h"
#include "Gpio.h"

typedef struct
{
   en_gpio_port_t Gpio_port_SDA;
   en_gpio_pin_t Gpio_Pin_SDA;
   en_gpio_port_t Gpio_port_SCL;
   en_gpio_pin_t Gpio_Pin_SCL;
}_IIC_Device;



extern _IIC_Device My_IIC_Device[];
void IIC_Init(_IIC_Device *IIC_Device);
void IIC_Start(_IIC_Device *IIC_Device);
void IIC_Stop(_IIC_Device *IIC_Device);
u8 IIC_Waite_ACK(_IIC_Device *IIC_Device);
void IIC_ACK(_IIC_Device *IIC_Device);
void IIC_NACK(_IIC_Device *IIC_Device);
void IIC_Send_Byte(_IIC_Device *IIC_Device,u8 TxD);
u8 IIC_Read_Byte(_IIC_Device *IIC_Device,u8 ack);


#endif
