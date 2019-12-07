#ifndef __EMS__HH__
#define __EMS__HH__
#include "Global.h"
#include "TypedefDef.h"
#include "key.h"

#define MassageIndexMaxGuaSha 32
#define MassageIndexMaxBeat 32
typedef struct
{
  volatile u16 Pwm_Duty; 
  u16 Boost_calltime;
}_EMS_Control;

typedef struct
{
  u8 StrgUpdateFlag;  
  u8 StrengthOld;
  u16 StrgUpdateTime;
}_StrgUpdateControl;

extern _EMS_Control Ems_Control;
extern _PwmProcessDataHandler PwmProcessDataHandler;
extern _StrgUpdateControl StrengUpdateControl;

void EMSControlHandler(void);
void EMS_PwmControl(void);
void Ems_ParaInit(void);
void Ems_Start(void);
void Ems_Stop(void);
void Ems_Output_Close(void);


#endif
