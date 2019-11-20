#ifndef _HC595_HH__
#define _HC595_HH__


#define Heater_To_Port_Close  Heater_To_Port_SetIO()


#define Heater_To_Port_Open  Heater_To_Port_ClrIO()






void HC595_Init(void);
void Motor_Vibration_SetIO(void);
void Motor_Vibration_ClrIO(void);
void Led_Blue_SetIO(void);
void Led_Blue_ClrIO(void);
void Led_Green_SetIO(void);
void Led_Green_ClrIO(void);
void Led_Red_SetIO(void);
void Led_Red_ClrIO(void);
void Heater_To_Port_SetIO(void);
void Heater_To_Port_ClrIO(void);
void Led_Bright_Red_Close_Blue_Green(void);
void Led_Bright_Blue_Close_Red_Green(void);
void Led_Bright_Green_Close_Blue_Red(void);
void Led_Blue_Close(void);
void Led_Red_Close(void);
void Led_Green_Close(void);
void Led_All_Close(void);

#endif
