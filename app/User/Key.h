#ifndef __KEY__HH__
#define __KEY__HH__
#include "TypedefDef.h"
#include "gpio.h"
#define KEY_OFF 0
#define KEY_START 1
#define KEY_POWR_INC 4
#define KEY_POWR_DEC 2
#define KEY_MODE_INC 8


#define EMS_Check_Port GpioPortA 
#define EMS_Check_Pin GpioPin6


typedef struct
{
   u8 KeyTemp;
   u8 KeyBuffer;
   u8 KeyBufferOld;
   u16 KeyCount;
   u8 KeyData;
   u8 KeyOld;   
   u16 keyTime;
}_keyHandler;


typedef struct
{
  volatile u8 Ems_Check_Flag;
  volatile u8 Ems_CkIntFlag;
  u8 Ems_CkCount;
  u8 Ems_CkTemp;
  u8 Ems_CkBuffer;
  u8 Ems_CkData;
  volatile u16 Ems_CkTime;
}_Ems_Status_Check;

typedef struct
{
  u8 Status_CheckTemp;
  u8 Status_CheckBuff;
  u8 status_CheckBuffOld;
  u8 status_CheckCount;
  u8 status_CheckData;
}_Chg_Status_Check;


void keyScan(void);
void KeyInit(void);
void KeyInit2(void);
void KeyHandler(void);
void EMS_Port_Pin_Status(void);
void EMS_Port_Check_Pin_Init(void);
void Battery_Chg_Compl_Status_Init(void);
u8 Battery_Chg_Compl_Status_Check(void);
void TrigTouchKeyInitEnable(void);
void TrigTouchKeyInitDisable(void);
void Battery_Chg_Status_Pin_Scan(void);
void Battery_Chg_Status_Pin_Init(void);
void ExtTrigInterrupteRouseEnable(void);
void ExtTrigInterrupteRouseDisable(void);
void HallSwitchTrigTouchKeyInit(void);
void HallSwitchStatusScan(void);
void EMS_Port_Pin_Disable_IRQ(void);
extern _keyHandler keyDataHandler;
extern _Ems_Status_Check Ems_Status_Check;
extern _Chg_Status_Check Chg_Status_CheckHandler;
extern _keyHandler HallSwitchScan;

#endif
