#ifndef __MAIN__HH__
#define __MAIN__HH__

#include "TypedefDef.h"
#include "lk_board.h"
#define PeripheralBatterySwPort GpioPortC 
#define PeripheralBatterySwPin GpioPin15


#define PeripheralSw_Open Gpio_ClrIO(PeripheralBatterySwPort,PeripheralBatterySwPin)
#define PeripheralSw_Clsoe Gpio_SetIO(PeripheralBatterySwPort,PeripheralBatterySwPin)



#define Battery_Open Gpio_ClrIO(GpioPortB,GpioPin1)
#define Battery_Close Gpio_SetIO(GpioPortB,GpioPin1)


#define Battery_Charge_Port_Voltage 4000


#endif
