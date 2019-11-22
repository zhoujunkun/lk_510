#include "TimeHandler.h"
#include "bt.h"
#include "Gpio.h"
#include "TypedefDef.h"
#include "Adt.h"
#include "flash.h"
#include "Ems.h"
#include "ddl.h"
#include "Timer3.h"
static void Time0IntCallback(void);
static void Time3IntCallback(void);
void Tim2Int(void);

void TimestampInit(void)
{


  u16                      u16ArrValue;
  en_flash_waitcycle_t		enFlashWait;
  u16                      u16CntValue;
  u8                       u8ValidPeriod;
  
  stc_bt_mode23_config_t        stcBtBaseCfg;
  stc_bt_m23_compare_config_t   stcBtPortCmpCfg;
  stc_bt_m23_dt_config_t stc_bt_dt_Cfg;

  DDL_ZERO_STRUCT(stcBtBaseCfg);
  DDL_ZERO_STRUCT(stcBtPortCmpCfg);
  DDL_ZERO_STRUCT(enFlashWait);
  DDL_ZERO_STRUCT(stc_bt_dt_Cfg);

  enFlashWait = FlashWaitCycle1;                     
  Flash_WaitCycle(enFlashWait);    

  Sysctrl_SetPeripheralGate(SysctrlPeripheralBTim, TRUE);   
      
  stcBtBaseCfg.enWorkMode    = BtWorkMode2;             
  stcBtBaseCfg.enCT          = BtTimer;                  
  stcBtBaseCfg.enPRS         = BtPCLKDiv256;              
  stcBtBaseCfg.enCntDir    = BtCntUp;                 
  stcBtBaseCfg.enPWMTypeSel  = BtIndependentPWM;         
  stcBtBaseCfg.enPWM2sSel    = BtSinglePointCmp;        
  stcBtBaseCfg.bOneShot      = FALSE;                    
  stcBtBaseCfg.bURSSel       = FALSE;                   
  stcBtBaseCfg.pfnTim0Cb     =Time0IntCallback;

  Bt_Mode23_Init(TIM0, &stcBtBaseCfg);                   

  u16ArrValue = 0xEA60;  ////  向上计数
  Bt_M23_ARRSet(TIM0, u16ArrValue, TRUE);               
	
  u8ValidPeriod = 0;                                    
  Bt_M23_SetValidPeriod(TIM0,u8ValidPeriod);            
 
		
  u16CntValue = 0x0;
  Bt_M23_Cnt16Set(TIM0, u16CntValue);                    
  
  Bt_ClearAllIntFlag(TIM0);                              
  Bt_Mode23_EnableIrq(TIM0,BtUevIrq);                    
  EnableNvic(TIM0_IRQn, IrqLevel0, TRUE);               
    
  Bt_M23_Run(TIM0);                                    
 // Bt_M23_Run(TIM1);

}

static void Time0IntCallback(void)
{
  if(TRUE == Bt_GetIntFlag(TIM0, BtUevIrq))
    {
       Bt_ClearIntFlag(TIM0,BtUevIrq);
	   __set_PRIMASK(1);
	   EMS_PwmControl();
	   __set_PRIMASK(0);
   	}
}



void TimeBoostPwmInit(void)
{
    en_adt_unit_t             enAdt;
    uint16_t                  u16Period;
    en_adt_compare_t          enAdtCompareA;
    uint16_t                  u16CompareA;

    en_flash_waitcycle_t      enFlashWait;
    stc_adt_basecnt_cfg_t     stcAdtBaseCntCfg;
    stc_adt_CHxX_port_cfg_t   stcAdtTIM4ACfg;
    stc_adt_CHxX_port_cfg_t   stcAdtTIM4BCfg;
    stc_gpio_config_t         stcTIM4APort;
    stc_gpio_config_t         stcTIM4BPort;
    
    DDL_ZERO_STRUCT(stcAdtBaseCntCfg);
    DDL_ZERO_STRUCT(stcAdtTIM4ACfg);
    DDL_ZERO_STRUCT(stcAdtTIM4BCfg);
    DDL_ZERO_STRUCT(stcTIM4APort);
    DDL_ZERO_STRUCT(stcTIM4BPort);
    
    enFlashWait = FlashWaitCycle1;                     
    Flash_WaitCycle(enFlashWait);                      

   
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 

    stcTIM4APort.enDir  = GpioDirOut;
	Gpio_Init(GpioPortA, GpioPin8, &stcTIM4APort);
	Gpio_SetAfMode(GpioPortA,GpioPin8,GpioAf6);
    
    if (Ok != Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, TRUE))
    {
        return ;
    }
    
	enAdt = AdtTIM4;
    
    stcAdtBaseCntCfg.enCntMode = AdtSawtoothMode;
    stcAdtBaseCntCfg.enCntDir = AdtCntUp;
    stcAdtBaseCntCfg.enCntClkDiv = AdtClkPClk0;
    
    Adt_Init(enAdt, &stcAdtBaseCntCfg);                      
    u16Period = 0x320;
    
    Adt_SetPeriod(enAdt, u16Period);                       
    
    enAdtCompareA = AdtCompareA;
    u16CompareA = 0x230;
    
    Adt_SetCompareValue(enAdt, enAdtCompareA, u16CompareA);  
    
    //enAdtCompareB = AdtCompareB;
   // u16CompareB = 0x3000;//0x6000;
   // Adt_SetCompareValue(enAdt, enAdtCompareB, u16CompareB);  
    
    stcAdtTIM4ACfg.enCap = AdtCHxCompareOutput;            
    stcAdtTIM4ACfg.bOutEn = TRUE;                         
    stcAdtTIM4ACfg.enPerc = AdtCHxPeriodLow;              
    stcAdtTIM4ACfg.enCmpc = AdtCHxCompareHigh;            
    stcAdtTIM4ACfg.enStaStp = AdtCHxStateSelSS;           
    stcAdtTIM4ACfg.enStaOut = AdtCHxPortOutLow;            
    stcAdtTIM4ACfg.enStpOut = AdtCHxPortOutLow;           
    Adt_CHxXPortConfig(enAdt, AdtCHxA, &stcAdtTIM4ACfg);  

    Adt_StartCount(enAdt);

}


void Update2Time(void)
{

	  u16					   u16ArrValue;
	  en_flash_waitcycle_t	   enFlashWait;
	  u16					   u16CntValue;
	  u8					   u8ValidPeriod;
	  stc_bt_mode23_config_t   stcBtBaseCfg;
	  DDL_ZERO_STRUCT(stcBtBaseCfg);
	  DDL_ZERO_STRUCT(enFlashWait);
	  Sysctrl_SetPeripheralGate(SysctrlPeripheralBTim, TRUE);	
	  stcBtBaseCfg.enWorkMode	 = BtWorkMode2; 			
	  stcBtBaseCfg.enCT 		 = BtTimer; 				 
	  stcBtBaseCfg.enPRS		 = BtPCLKDiv64;				 
	  stcBtBaseCfg.enCntDir    = BtCntUp;				  
	  stcBtBaseCfg.enPWMTypeSel  = BtComplementaryPWM;		  
	  stcBtBaseCfg.enPWM2sSel	 = BtSinglePointCmp;		 
	  stcBtBaseCfg.bOneShot 	 = FALSE;					
	  stcBtBaseCfg.bURSSel		 = FALSE;					
	  stcBtBaseCfg.pfnTim2Cb=Tim2Int;
	  Bt_Mode23_Init(TIM2, &stcBtBaseCfg);					
	
	  u16ArrValue = 0x177;	
	  Bt_M23_ARRSet(TIM2, u16ArrValue, TRUE);	///  1ms			
	
	  u8ValidPeriod = 0;									 
	  Bt_M23_SetValidPeriod(TIM2,u8ValidPeriod);			 
			
	  u16CntValue = 0;
	  Bt_M23_Cnt16Set(TIM2, u16CntValue);					 
		
	  Bt_ClearAllIntFlag(TIM2);							   
	  Bt_Mode23_EnableIrq(TIM2,BtUevIrq); 				   
	  EnableNvic(TIM2_IRQn, IrqLevel3, TRUE); 			  
		
	  Bt_M23_EnPWM_Output(TIM2, TRUE, FALSE);				
	  Bt_M23_Run(TIM2);                                           
}

void Update2TimeSleep(void)
{
    Sysctrl_SetPeripheralGate(SysctrlPeripheralBTim,FALSE);	
	Bt_M23_Stop(TIM2); 
}

void Tim2Int(void)
{
    if(TRUE == Bt_GetIntFlag(TIM2, BtUevIrq))
    {
       Bt_ClearIntFlag(TIM2,BtUevIrq);
	   softtime_Count_1ms++;
	   StrengUpdateControl.StrgUpdateTime++;
	   SoftTimerCount();
    }
}


void breathing_LightInit(void)
{
	  u16                      u16CntValue;
	  u8                       u8ValidPeriod;
	  
	  stc_tim3_mode23_config_t        stcBtBaseCfg;
      stc_tim3_m23_compare_config_t   stcBtPortCmpCfg;
	  stc_gpio_config_t stcGpioCfg;

	  DDL_ZERO_STRUCT(stcBtBaseCfg);
	  DDL_ZERO_STRUCT(stcBtPortCmpCfg);

	  stcGpioCfg.enDir=GpioDirOut;
	  stcGpioCfg.enDrv=GpioDrvH;
	  
	  Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
	  Gpio_SetAfMode(GpioPortA,GpioPin10,GpioAf2);  
	 

	  Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, TRUE);   
	      
	  stcBtBaseCfg.enWorkMode    = Tim3WorkMode2;             
	  stcBtBaseCfg.enCT          = Tim3Timer;                  
	  stcBtBaseCfg.enPRS         = Tim3PCLKDiv16;              
	  stcBtBaseCfg.enCntDir    = Tim3CntUp;                 
	  stcBtBaseCfg.enPWMTypeSel  = Tim3IndependentPWM;         
	  stcBtBaseCfg.enPWM2sSel    = Tim3SinglePointCmp;        
	  stcBtBaseCfg.bOneShot      = FALSE;                    
	  stcBtBaseCfg.bURSSel       = FALSE;                   
	  stcBtBaseCfg.pfnTim3Cb=Time3IntCallback;

	  Tim3_Mode23_Init(&stcBtBaseCfg);                   

	  Tim3_M23_ARRSet(375, TRUE);                
		
	  Tim3_M23_CCR_Set(Tim3CCR2A, 0x90);       



	  stcBtPortCmpCfg.enCHxACmpCtrl= Tim3PWMMode1;          
	  stcBtPortCmpCfg.enCHxAPolarity= Tim3PortPositive;      
	  stcBtPortCmpCfg.bCHxACmpBufEn= TRUE;                
	  stcBtPortCmpCfg.enCHxACmpIntSel= Tim3CmpIntNone;        
	    
	  stcBtPortCmpCfg.enCHxBCmpCtrl= Tim3PWMMode1;         
	  stcBtPortCmpCfg.enCHxBPolarity  = Tim3PortPositive;     
	  stcBtPortCmpCfg.bCHxBCmpBufEn   = TRUE;               
	  stcBtPortCmpCfg.enCHxBCmpIntSel = Tim3CmpIntNone;        
	    
	  Tim3_M23_PortOutput_Config(Tim3CH2, &stcBtPortCmpCfg);     

	  
	  u8ValidPeriod = 0;                                    
	  Tim3_M23_SetValidPeriod(u8ValidPeriod);            

			
	  u16CntValue = 0;
	    
	  Tim3_M23_Cnt16Set(u16CntValue);   

		Tim3_M23_EnPWM_Output(TRUE, FALSE);
	    
	  Tim3_M23_Run();  
		Time3Breathing_Light_Duty(100);

}

void Time3Breathing_Light_Duty(u16 pulse)
{
    Tim3_M23_CCR_Set(Tim3CCR2A, pulse); 
}

static void Time3IntCallback(void)
{
  if(TRUE == Tim3_GetIntFlag(Tim3UevIrq))
    {
       Tim3_ClearIntFlag(Tim3UevIrq);
	   
   	}
}




void Boost_Pwm(u16 PwmValue)
{
   u16 Temp=0;
   Temp=Boost_ValueMax-PwmValue;
   Adt_SetCompareValue(AdtTIM4, AdtCompareA,Temp);
}


void Boost_Start(void)
{     
     Adt_StartCount(AdtTIM4);
}

void Boost_Stop(void)
{
   Boost_Pwm(0);
   Adt_StopCount(AdtTIM4);
}

void TimestampUpdateFreq(u16 ArrValue)
{
     Bt_M23_Cnt16Set(TIM0,0);
     Bt_M23_ARRSet(TIM0, ArrValue,TRUE);  
}

void TimestampStop(void)
{
   Bt_M23_Cnt16Set(TIM0,0);
   Bt_M23_Stop(TIM0);
   Bt_ClearAllIntFlag(TIM0);                              
   Bt_Mode23_DisableIrq(TIM0,BtUevIrq);                    
   EnableNvic(TIM0_IRQn, IrqLevel0, FALSE); 
}

void TimestampStart(void)
{
   Bt_ClearAllIntFlag(TIM0);                              
   Bt_Mode23_EnableIrq(TIM0,BtUevIrq);                    
   EnableNvic(TIM0_IRQn, IrqLevel0, TRUE);
   Bt_M23_Run(TIM0);
}

void Ems_SleepInit(void)
{
   TimestampStop();
   Boost_Stop();
   Sysctrl_SetPeripheralGate(SysctrlPeripheralBTim, FALSE);
   Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim,FALSE);
}


