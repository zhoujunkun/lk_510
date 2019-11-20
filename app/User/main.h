#ifndef __MAIN__HH__
#define __MAIN__HH__
#include "TypedefDef.h"

typedef struct
{
  u8 Led_Switch_Flag;
  u8 Led_Blink_Flag;
  u8 Led_Blink_Flag_old;
  u8 Led_Blink_Count;
  u16 Led_Blink_Time;
}_LED_Blink_Control;


#define PeripheralBatterySwPort GpioPortC 
#define PeripheralBatterySwPin GpioPin15


#define PeripheralSw_Open Gpio_ClrIO(PeripheralBatterySwPort,PeripheralBatterySwPin)
#define PeripheralSw_Clsoe Gpio_SetIO(PeripheralBatterySwPort,PeripheralBatterySwPin)



#define Battery_Open Gpio_ClrIO(GpioPortB,GpioPin1)
#define Battery_Close Gpio_SetIO(GpioPortB,GpioPin1)


#define Battery_Charge_Port_Voltage 4000


#endif
