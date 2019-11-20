#ifndef __LEDMOTOR_HH__
#define __LEDMOTOR_HH__


#define LED_1_Port GpioPortA
#define LED_1_Pin GpioPin11


#define Motor_Port GpioPortA
#define Motor_Pin  GpioPin7

#define Heater_Port GpioPortA
#define Heater_Pin  GpioPin9


#define LED_1_Open Gpio_SetIO(LED_1_Port,LED_1_Pin)
#define LED_1_Close Gpio_ClrIO(LED_1_Port,LED_1_Pin)

#define Motor_Open Gpio_SetIO(Motor_Port,Motor_Pin)
#define Motor_Close Gpio_ClrIO(Motor_Port,Motor_Pin)


#define Heater_Open Gpio_ClrIO(Heater_Port,Heater_Pin)
#define Heater_Close Gpio_SetIO(Heater_Port,Heater_Pin)



void Led_1_Init(void);
void Motor_Init(void);
void Heater_Init(void);

#endif
