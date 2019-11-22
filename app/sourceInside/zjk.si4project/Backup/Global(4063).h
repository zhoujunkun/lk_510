#ifndef __GLOBAL_HH__
#define __GLOBAL_HH__
#include "TypedefDef.h"

#define Heart_rate_sensor_enable 1



#define MassageStrengthMax 15
#define MassageModeMax 2

typedef enum
{
  electsliceExtNo,
  electsliceExtLarge,
  electsliceExtFour,
}_electrodesliceType;


typedef enum
{
  DirAB_And_CD_IDLE,
  DirAB_And_CD_DisCharge,
  DirA_T_B_And_CD_No,
  DirA_T_B_And_C_T_D,
  DirA_T_B_And_D_T_C,
  DirA_T_B_And_CDAuto_PN,
  
  DirA_T_C_And_BC_No,
  DirA_T_C_And_B_T_D,
  DirA_T_C_And_D_T_B,
  DirA_T_C_And_BDAuto_PN,

  DirA_T_D_And_BC_No,
  DirA_T_D_And_B_T_C,
  DirA_T_D_And_C_T_B,
  DirA_T_D_And_BCAuto_PN,

  DirB_T_A_And_CD_No,
  DirB_T_A_And_C_T_D,
  DirB_T_A_And_D_T_C,
  DirB_T_A_And_CDAuto_PN,

  DirB_T_C_And_AD_No,
  DirB_T_C_And_A_T_D,
  DirB_T_C_And_D_T_A,
  DirB_T_C_And_ADAuto_PN,


  DirB_T_D_And_AC_No,
  DirB_T_D_And_A_T_C,
  DirB_T_D_And_C_T_A,
  DirB_T_D_And_ACAuto_PN,

  DirC_T_A_And_BD_No,
  DirC_T_A_And_B_T_D,
  DirC_T_A_And_D_T_B,
  DirC_T_A_And_BDAuto_PN,

  DirC_T_B_And_AD_No,
  DirC_T_B_And_A_T_D,
  DirC_T_B_And_D_T_A,
  DirC_T_B_And_ADAuto_PN,

  DirC_T_D_And_AB_No,
  DirC_T_D_And_A_T_B,
  DirC_T_D_And_B_T_A,
  DirC_T_D_And_ABAuto_PN,

  DirD_T_A_And_CB_No,
  DirD_T_A_And_C_T_B,
  DirD_T_A_And_B_T_C,
  DirD_T_A_And_BC_AutO_PN,

  DirA_T_B_And_CD_No_PN,
  DirA_T_C_And_BD_No_PN,
  DirA_T_D_And_BC_No_PN,
  DirB_T_A_And_CD_No_PN,
  DirB_T_C_And_AD_No_PN,
  DirB_T_D_And_AC_No_PN,
  DirC_T_A_And_BD_No_PN,
  DirC_T_B_And_AD_No_PN,
  DirC_T_D_And_AB_No_PN,
  DirD_T_A_And_BC_No_PN,
  DirD_T_B_And_AC_No_PN,
  DirD_T_C_And_AB_No_PN,

  DirABAuto_And_CDAuto_PN,
  DirACAutO_And_BDAut0_PN,
  DirADAuto_And_BCAuto_PN,

  DirABC_T_D_PN,
  DirABD_T_C_PN,
  DirACD_T_B_PN,
  DirCBD_T_A_PN,
  
}_Massage3DModelType;





typedef enum
{
   PwmOutIdle,
   PwmOutOne,
   PwmOutTwo,
   PwmOutOneAndTwo,
}_PwmOutCSel;



typedef enum
{
   DeviceClose,
   DeviceOpen,
}_DeviceRunStatus;

typedef enum
{
   Dirdischarge,
   Dirforward,
   Dirreverse,
   DirIDLE,
   DirPNAlter,
   DirPNAlterL,
   DirPNAlterR,
   Diralternate,/// 交替切换
}_PwmDir;

typedef enum
{
  MassageIDLE,
  MassageAcupuncture,
  MassageMalaxation,
  Massagescraping,
  MassageKnock,
  Massage3DAcupuncture,
  Massage3DMalaxation,
  Massage3Dscraping,
  Massage3DKnock,
}_MassageModeType;

typedef enum
{
  Heat_temperature_38,
  Heat_temperature_40,
  Heat_temperature_42,
  Heat_temperature_Zero,
}_Heat_temperature_type;

typedef enum
{
   Motor_Vibr_StartUp,
   Motor_Vibr_ShutDown,
   Motor_Vibr_One,
   Motor_Vibr_Two_Fast,
   Motor_Vibr_Two_0s5,
   Motor_Vibr_EnterStopStatus,
   Motor_Vibr_StopStatus=0xfe,
}_Motor_Vibr_Typedef;

typedef struct
{
  _Motor_Vibr_Typedef Motor_Vibr_flag;
  u8 Motor_Vibr_flagOld;  
  u8 Motor_Vibr_Count;
  u16 Motor_Vibr_Time;
}_Motor_vibr_Control_type;

typedef enum
{
   LED_Starting_Disp,///  LED 开机时显示
   LED_Chg_Status_Dip,  ///  LED 充电式显
   LED_Battery_Low_Disp,   //// LED 电池电压低时显示
   LED_Battery_Chg_Compl_Disp,   //// LED 电池充电完成显示
   LED_Battery_Chg_NO_Compl_Disp,  ///  LED 电池充电没有完成显示
   LED_ADJ_STG_Level_Max_Disp, ///   LED  调整最大时显示
   LED_ADJ_STG_Level_Min_Disp,  ///  LED 调整到最小时显示
   LED_App_operate_Success,   ///  LED 操作成功显示
}_LED_Status;

typedef enum
{
  DeviceIDLE,
  DeviceCharge,
  DeviceWorke,
}_DeviceStatus;

typedef enum
{
  ChargeStatusNo,   /// 待机中
  ChargeStatusIng,   /// 充电中
  ChargeNOEnterMassageIng, /// 等待进入到按摩中
  ChargeNoMassageIng,   /// 按摩�?
  ChargeNoMassageComple, //// 按摩完成
  ChargeStatusComplete, //// 充电完成
  CharageStatusLowFault,  ///  低电量报错中
}_ChgAndMassgeStatus;

#define Ems_Line_NoCheckTimeValue 30

typedef struct
{
    u8 Ems_LineCheck;    ////  EMS 检测状态情�?
	u8 Ems_LineCheckOldMassageIng;   ///  EMS 检测状态保�?
    u8 Heat_time_interval;
    u8 Strength;  
	u8 StrengthOld;
	u16 ConfigRunTime;
	u16 MassageRunTime;
	u16 MassageIDLETime;
	u16 Ems_LineCheckNoTime;
	volatile _MassageModeType MassageMode;
	_Heat_temperature_type Heat_TempInfo;
	_LED_Status Led_Status;
	_electrodesliceType ElectrSliceTyp;
	_DeviceStatus DeviceRunStatus;
	_ChgAndMassgeStatus ChargeAndMassageStatus;
}_MassageControl;
typedef enum
{
    LowPowerImmedShutdown=1,
	LowPowerDelayShutdown,
	LowPowerNoCancelShutdown,
	LowPowerStopStatus,
}_LowPowerShutdownTyped;



typedef struct
{
  _LowPowerShutdownTyped LowPowerFlag;
  u16 LowPowerDelayTime;
}_LowPowerControl;


typedef struct
{
   u32 PwmPulse;
   u32 PwmInterval;
   u16 repetCount;
}_PwmPulseType;

typedef struct
{
   _PwmPulseType *PwmPulseOut;
   _PwmDir PwmOutDir;
}_PwmPulseData;


typedef struct
{
   _PwmPulseType *PwmPulseOut;
   _Massage3DModelType Mode3Dgroup;
}_PwmPulse3Ddata;

typedef struct
{
  volatile _PwmDir PwmOutDir;
  _Massage3DModelType Pwm3DDir;
  volatile u8 SwitchOutDisable;
  volatile u16 TimeArrValue;
  volatile u16 repetCount;
  volatile u16 PwmArrIndex;
  u16 PwmPulse;
  u16 PwmConfig_IndexMax;
  u16 PwmConfig_repetMax;
}_PwmProcessDataHandler;

typedef struct
{
  u8 key_init_Flag;
  u16 key_delay_time;
}_key_delay_init;



typedef struct
{
  u8 HandlerFlag;
  u8 RxBufferCopy[30];
}_RxBufferCycle;

#define RxBufferCycleLength 4
typedef struct
{
   u8 outtime;
   volatile u8 RxIndex;
   volatile u8 datalength;
   volatile u8 TxCount;
   u8 RxBufferCycleIndex;
   u8 RxBuffer[30];
   _RxBufferCycle RxBufferCycle[RxBufferCycleLength];
   u8 TxBuffer[256];
}RxHandlerBuffer;
extern RxHandlerBuffer RxBufferHandler;

#define FilterBufferMaxLength 2
typedef struct
{
   volatile u8 FilterIndex;
   volatile u32 FilterBuffer[FilterBufferMaxLength];
   u32 FilterMaxValue;
   u32 FilterMinValue;
   volatile u32 FilterAvgValue;
}_FilterSampleBuff;


typedef struct
{
   volatile u8 FilterIndex;
   volatile float FilterBuffer[FilterBufferMaxLength];
   u32 FilterMaxValue;
   u32 FilterMinValue;
   volatile float FilterAvgValue;
   u8 FilterCmpFlag;
}_FilterSampleBuffFloat;


extern _FilterSampleBuff VoltageSampleBuff;
extern _MassageControl MassageHandler;
extern volatile u8 invoking_interval_Time_flag;
extern volatile u8 softtime_Count_1ms;
extern _Motor_vibr_Control_type Motor_Vibr_Control;
extern _LowPowerControl LowPowerControl;
extern _key_delay_init key_delay_init;
void SoftTimerCount(void);

#endif