#ifndef __TIMEHANDLER__HH__
#define __TIMEHANDLER__HH__
#include "TypedefDef.h"
#include "Global.h"

#define Boost_ValueMax 0x320
#define Breath_Pwm_Pulse 375
void TimestampInit(void);
void TimeBoostPwmInit(void);
void Boost_Pwm(u16 PwmValue);
void Update2Time(void);

void TimestampUpdateFreq(u16 ArrValue);
void TimestampStop(void);
void TimestampStart(void);
void Boost_Stop(void);
void Boost_Start(void);
void Update2TimeSleep(void);
void Ems_SleepInit(void);
void breathing_LightInit(void);
void Time3Breathing_Light_Duty(u16 pulse);
void breathing_SleepInit(void);


#endif
