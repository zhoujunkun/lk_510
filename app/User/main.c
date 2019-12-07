#include "main.h"
#include "TimeHandler.h"
#include "Key.h"
#include "AdcSample.h"
#include "UartHandler.h"
#include "Global.h"
#include "Gpio.h"
#include "EMS.h"
#include "adc.h"
#include "Util.h"
#include "lpm.h"
#include "EMS_Port.h"
#include "NTCTempSample.h"
//#include "HC595.h"
#include "LedMotor.h"
#include "stdbool.h"



//LK include 
#include "lk_led.h"

static void HardWareInit(void);
static void AdcSampleTask(void);
static void peripheralInit(void);
static void ClkInit24M(void);
static void EMSTimeInit(void);
static void Ems_CallTask(void);
static void SoftTimeTask(void);
static void EMS_Status_Check(void);
static void Motor_vibration_Control(void);
void LED_Status_Control(void);
static void Battery_Status_Check(void);
static void Heat_temperature_Control(void);
static void Ems_Control_F(void);
static void LowPowerHandler(void);
static void DeviceDataInit(void);
static void ExternBoardCheckHandler(void);
static void Heat_Temperature_Close(void);
static void key_Delay_Init(void);
static void Ems_Massage_Mode_update(void);
static void PeripheralBatterySwInit(void);


volatile u8 IRQ_Start_Enable=0;
volatile u8 invoking_interval_Time_flag=0;
volatile u8 softtime_Count_1ms=0;



_MassageControl MassageHandler;

RxHandlerBuffer RxBufferHandler;

_FilterSampleBuff VoltageSampleBuff;
_FilterSampleBuff HeatTemperatureBuff;
_FilterSampleBuff ExtensiondetectBuff;
volatile _Motor_vibr_Control_type Motor_Vibr_Control;
_LED_Blink_Control Led_Blink_control;
_LowPowerControl LowPowerControl;
_key_delay_init key_delay_init;
volatile _LED_Blink_Control Led_Ctl;
_Heater_Control Heater_Status_Data_Control;


static bool ifHeatStart =FALSE;  //是否启动加热
static uint16_t lk_led_runStatu= 0XFF;  //led 显示状态



int main(void)
{
    ClkInit24M();
	ExtTrigInterrupteRouseDisable(); 
	//PeripheralBatterySwInit();
 	HardWareInit();
    breathing_LightInit();
	Ems_Start();
	DeviceDataInit();
	Ems_ParaInit();
	//lk_device_control();
    while(1)
    {
       keyScan();
	   KeyHandler();
	   HallSwitchStatusScan();
	   AdcSampleTask();
	   Ems_Control_F();
	   EMS_Status_Check();
	   Battery_Status_Check();
	   LED_Status_Control();
	   Motor_vibration_Control();
	   UartDataParseHandler();
	   LowPowerHandler();
	   key_Delay_Init();
    }

}

static void key_Delay_Init(void)
{
    if(key_delay_init.key_init_Flag==0)
    {
       if(key_delay_init.key_delay_time>8)  //运行8秒后初始化按键，jlink将不能仿真下载
       	{
       	  key_delay_init.key_init_Flag=1;
       	  key_delay_init.key_delay_time=0;
	      KeyInit();
       	}
    }
}

static void Ems_Control_F(void)
{
   static volatile u8 flag=0,flagold=0;
	// MassageHandler.ChargeAndMassageStatus = ChargeNoMassageIng;
	// MassageHandler.ifEmsCheck = TRUE;
	//ifHeatStart = TRUE;  //启动加热
	switch(MassageHandler.ChargeAndMassageStatus)
	{
	  case ChargeStatusNo:
	  	{
			  	 Ems_CallTask();
				 Heat_Temperature_Close();
				 MassageHandler.MassageRunTime=0;
				 if(MassageHandler.MassageIDLETime>=Ems_Line_NoCheckTimeValue)
				 {
		             if(flag!=flagold)
		             {
		                flagold=flag;
					   LowPowerControl.LowPowerFlag=LowPowerImmedShutdown;
		             }
				 }
				 else
				 {
				    flag=0x01;
					flagold=0xfe;
				 }
	  	}
	 	 break;
	  case ChargeNOEnterMassageIng:
	  	   Ems_CallTask();
		   if(ifHeatStart) Heat_temperature_Control();
	  	   MassageHandler.Ems_LineCheckOldMassageIng=MassageHandler.ifEmsCheck;
			   if(MassageHandler.ifEmsCheck==TRUE) //检测到配搭进入按摩模式
			   {
			     MassageHandler.ChargeAndMassageStatus=ChargeNoMassageIng;
				   MassageHandler.MassageIDLETime=0;
			   }
		     else
		   	 {
		   	  	
			 	 if(MassageHandler.MassageIDLETime>=Ems_Line_NoCheckTimeValue)
				     {
		              if(flag!=flagold)
		               {
		                flagold=flag; 
					    LowPowerControl.LowPowerFlag=LowPowerImmedShutdown;
		               }
					   }
					 else
						 {
						    flag=0x01;
					        flagold=0xfe;
						 }
		   	}
		    MassageHandler.MassageRunTime=0;
	  	   break;
	  case ChargeNoMassageIng:
	  	  { 
		 	  Ems_CallTask();
		  	   if(ifHeatStart) Heat_temperature_Control();
		  	 if(MassageHandler.Ems_LineCheckOldMassageIng!=MassageHandler.ifEmsCheck)
		  	  {
		  	 	   MassageHandler.Ems_LineCheckOldMassageIng=MassageHandler.ifEmsCheck;
				   if(MassageHandler.ifEmsCheck==FALSE) //配搭不成功
				   	{
				   	    MassageHandler.StrengthOld=MassageHandler.Strength;
					  MassageHandler.Strength=0;

				   	}
				   else
				   	{
						StrengUpdateControl.StrgUpdateFlag=1; //进入按摩标识
						StrengUpdateControl.StrgUpdateTime=0; //计时清0
						StrengUpdateControl.StrengthOld=0;
				   	}
		  	  }
			 if(MassageHandler.ifEmsCheck==TRUE)
			   {
				 MassageHandler.MassageIDLETime=0;
			   }
			   else
			   	{
			   	  	if(MassageHandler.MassageIDLETime>=Ems_Line_NoCheckTimeValue)
					 {
			             if(flag!=flagold)
			             {
			                flagold=flag;
					 	   LowPowerControl.LowPowerFlag=LowPowerImmedShutdown;
			             }
					 }
					 else
					 {
					    flag=0x01;
				        flagold=0xfe;
					 }
			   	}
			 if(MassageHandler.MassageRunTime>MassageHandler.ConfigRunTime)
			   {
			 	  MassageHandler.ChargeAndMassageStatus=ChargeNoMassageComple; 
				  MassageHandler.Strength=0;
			   }
	  	  }
	  	 break;
		    case ChargeStatusIng:
		      	{
				   Ems_Output_Close();
		      	   Heat_Temperature_Close();
		           if(Battery_Chg_Compl_Status_Check()>0)
		           {
		             
		                if(TRUE==Chg_Status_CheckHandler.status_CheckData)
		             	  {
							   MassageHandler.ChargeAndMassageStatus=ChargeStatusComplete;
						  } 
					       else
					       {
							   MassageHandler.ChargeAndMassageStatus=ChargeStatusNo;
						   }			         
		               }
				      MassageHandler.MassageIDLETime=0;
		      	}break;
	  case ChargeNoMassageComple:
	  	// Ems_CallTask();
	  	 Ems_Output_Close();
		 Heat_Temperature_Close();
         MassageHandler.MassageRunTime=0;
         MassageHandler.ChargeAndMassageStatus=ChargeStatusNo;
	     MassageHandler.MassageIDLETime=0;
		 Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_Two_0s5;
	  	 break;
	  case ChargeStatusComplete:
		 Heat_Temperature_Close();
	  	 Ems_Output_Close();
	  	 MassageHandler.MassageIDLETime=0;
		 if(Chg_Status_CheckHandler.status_CheckData==FALSE)
		  {
		     MassageHandler.ChargeAndMassageStatus=ChargeStatusNo;
		  }
	  	 break;
	  case CharageStatusLowFault:
	  	 Ems_Output_Close();
		 Heat_Temperature_Close();
	  	 break;
	}
   	
}

static void HardWareInit(void)
{
   peripheralInit(); //寮€鐢垫�?
   //HC595_Init();
   Led_1_Init();
   Motor_Init();
   Heater_Init();
   HallSwitchTrigTouchKeyInit();
   UartInit();
   AdcSampleInit();   
   EMS_Port_Init(); 		
   EMSTimeInit();
   Update2Time();	 
   Battery_Chg_Status_Pin_Init();
   EMS_Port_Check_Pin_Init();
   Battery_Chg_Compl_Status_Init();
}

static void PeripheralBatterySwInit(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
   DDL_ZERO_STRUCT(stcGpioCfg);
   stcGpioCfg.enDir=GpioDirOut;
   stcGpioCfg.enDrv=GpioDrvH;
   stcGpioCfg.enOD=GpioOdDisable;
   stcGpioCfg.enPuPd=GpioNoPuPd;
   stcGpioCfg.enCtrlMode=GpioAHB;
   Gpio_Init(PeripheralBatterySwPort,PeripheralBatterySwPin,&stcGpioCfg);
   PeripheralSw_Open;
}

static void AdcSampleTask(void)
{
	float Tempdata=0;
	if(1==IRQ_Start_Enable)
	{
	    IRQ_Start_Enable=0;
		Tempdata=ADC_Result_Array[0]*250;
		Tempdata/=4095;
		Tempdata*=62; 
		SampleFilterHandler(&VoltageSampleBuff,(u16)Tempdata);

        Tempdata=((float)(ADC_Result_Array[1]*2500)/(4095));
		SampleFilterFloatHandler(&NTCDataSmaple.NTCTempSample,(u16)Tempdata);

        Tempdata=((float)((ADC_Result_Array[2]*2500)/4095));
		SampleFilterHandler(&ExtensiondetectBuff,(u16)Tempdata);
//		ExternBoardCheckHandler();

		Tempdata=((float)(ADC_Result_Array[3]*2500*3)/(4095));
		SampleFilterFloatHandler(&NTCDataSmaple.BatteryVoltageSample,(u16)Tempdata);
		if(NTCDataSmaple.BatteryVoltageSample.FilterCmpFlag>0)
		{
		  NTCDataSmaple.BatteryVoltageSample.FilterCmpFlag=0;
		  NTCSampleDataHandler();
		}
		Adc_SQR_Start();
		invoking_interval_Time_flag=1; //adc 测试完成
	}

}

static void Ems_CallTask(void)
{
   if(invoking_interval_Time_flag>0)  //adc 测试完成标记
   	{
   	   invoking_interval_Time_flag=0;
	   	
	   EMSControlHandler();
   	}
}


static void SoftTimeTask(void)
{
    static u8 time10ms=0,time100ms=0,time1s=0;
    if(softtime_Count_1ms>=10)
    {
      time10ms++;
      softtime_Count_1ms-=10;
    }
	else
	{
	  return ;
	}

	if(time10ms>=1) ///  10ms
	{
	  time10ms-=1;
	  time100ms++;
	  Motor_Vibr_Control.Motor_Vibr_Time++;
	  keyDataHandler.keyTime++;
	  Led_Ctl.runTime.Counts++;
	  Heater_Status_Data_Control.periodic_Time++;
	}
	
	if(time100ms>=10)/// 100ms
	{
	   time100ms-=10;
	   time1s++;
	   MassageHandler.Heat_time_interval++;
	   Ems_Status_Check.Ems_CkTime++;
	}

	if(time1s>=10) /// 1s
	{
	  time1s-=10;
	  MassageHandler.MassageRunTime++;
	  MassageHandler.Ems_LineCheckNoTime++;
	  if(MassageHandler.MassageIDLETime<0xfff)
	  {
	    MassageHandler.MassageIDLETime++;
	  }
	  key_delay_init.key_delay_time++;
	  if(LowPowerControl.LowPowerFlag!=LowPowerStopStatus)
	  LowPowerControl.LowPowerDelayTime++;
	}

	
}
static void peripheralInit(void)   ///  battery switch
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);  
   stcGpioCfg.enDir = GpioDirOut;
   stcGpioCfg.enDrv = GpioDrvH;
   stcGpioCfg.enPuPd = GpioPd;
   stcGpioCfg.enOD = GpioOdDisable;
   stcGpioCfg.enCtrlMode = GpioAHB;
   Gpio_Init(GpioPortB, GpioPin1,&stcGpioCfg);
   Battery_Open;
}
static _MassageModeType MassageTemp[]=
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

};

static void Ems_Massage_Mode_update(void)
{
   MassageHandler.ifEmsCheck = TRUE;   //测试。。
     if(MassageHandler.ElectrSliceTyp==electsliceExtFour)
      {
         if(MassageHandler.MassageMode<Massage3DAcupuncture)
         	{
         	  MassageHandler.MassageMode=Massage3DAcupuncture;
         	}
      }
	 else
	  {
	       if(MassageHandler.MassageMode>=Massage3DAcupuncture)
	       	{
	       	   MassageHandler.MassageMode=MassageAcupuncture;
	       	}
	  }
	 Ems_ParaInit();
}



void KeyHandler(void)
{
   volatile u8 Temp=0;
 
   if( KEY_POWR_INC==keyDataHandler.KeyData)
   	{
   	  keyDataHandler.KeyData=KEY_OFF;
	  MassageHandler.MassageIDLETime=0;
	  if((CharageStatusLowFault!=MassageHandler.ChargeAndMassageStatus)&& //不能在低电量+充电完成+充电中
	  	(ChargeStatusComplete!=MassageHandler.ChargeAndMassageStatus)&&
	  	(ChargeStatusIng!=MassageHandler.ChargeAndMassageStatus))
	  	{
		  if(MassageHandler.Strength<MassageStrengthMax)
		   {
		       if(TRUE==MassageHandler.ifEmsCheck) //检测到是否配搭上
		       	{
		  	      MassageHandler.Strength++;
		       	}
			   Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_One;
			   lk_led_runStatu = LK_LED_BLINK_ONCE;
		   }
		  else
		   {
		     Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_Two_Fast;
			 lk_led_runStatu = LK_LED_BLINK_TWICE;
		   }
		  if(MassageHandler.ChargeAndMassageStatus!=ChargeNoMassageIng) //按下按键进入待按摩模式
		  	{
		  	   MassageHandler.ChargeAndMassageStatus=ChargeNOEnterMassageIng;
		  	}	  
	  	}
	     
	 
   	}
   
   if(KEY_POWR_DEC==keyDataHandler.KeyData)
   	{
   	  keyDataHandler.KeyData=KEY_OFF;
	  MassageHandler.MassageIDLETime=0;
	  if((CharageStatusLowFault!=MassageHandler.ChargeAndMassageStatus)&&
	  	(ChargeStatusComplete!=MassageHandler.ChargeAndMassageStatus)&&
	  	(ChargeStatusIng!=MassageHandler.ChargeAndMassageStatus))
	  	{
		  if(MassageHandler.Strength>0) //强度是否是正
		    {
		  	  MassageHandler.Strength--;
			  Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_One;
              lk_led_runStatu = LK_LED_BLINK_ONCE;
		  	}
		  else
		  	{
		  	   Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_Two_Fast; 
			   Led_Ctl.Led_Switch_Flag=TRUE;
			   lk_led_runStatu = LK_LED_BLINK_TWICE;
		  	}
		  if(MassageHandler.ChargeAndMassageStatus!=ChargeNoMassageIng) //按下按键进入待按摩模式
		  	{
		  	   MassageHandler.ChargeAndMassageStatus=ChargeNOEnterMassageIng;
		  	}
	  	}
   	}

    
   if((KEY_START==keyDataHandler.KeyOld)&&(keyDataHandler.keyTime>=200))   ///  2s
   	{
      keyDataHandler.KeyOld=KEY_OFF;
	  MassageHandler.MassageIDLETime=0;
	  if((CharageStatusLowFault!=MassageHandler.ChargeAndMassageStatus)&&
	  	(ChargeStatusComplete!=MassageHandler.ChargeAndMassageStatus)&&
	  	(ChargeStatusIng!=MassageHandler.ChargeAndMassageStatus))
	  	{
	      Temp=MassageHandler.MassageMode;
		  if(MassageHandler.ElectrSliceTyp==electsliceExtFour)
		  	{
			  if(++Temp>Massage3DKnock)
			  	{
			  	  Temp=Massage3DAcupuncture;
			  	}
			  if(Temp<Massage3DAcupuncture)
			  	{
			  	  Temp=Massage3DAcupuncture;
			  	}
		  	}
		  else
		  	{
		  	   if(++Temp>MassageKnock)
			  	{
			  	  Temp=MassageAcupuncture;
			  	}

			   if(Temp<MassageAcupuncture)
			   	{
			   	  Temp=MassageAcupuncture;
			   	}
		  	}
		  if(MassageHandler.ChargeAndMassageStatus!=ChargeNoMassageIng)//按下按键进入待按摩模式
		  {
			  MassageHandler.ChargeAndMassageStatus=ChargeNOEnterMassageIng;
		  }


		   Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_One;
		  lk_led_runStatu = LK_LED_BLINK_TWICE;

		  if(Temp<=Massage3DKnock)
		  {
		   MassageHandler.MassageMode=MassageTemp[Temp];
		  }
		  MassageHandler.Strength=0;
		  Ems_ParaInit();
		  Ems_Start();
	  	}

   	}
    

   
   if((KEY_START==keyDataHandler.KeyOld)&&(keyDataHandler.keyTime<200))  ////  1s  &&(keyDataHandler.keyTime<200)
   	{
      keyDataHandler.KeyOld=KEY_OFF;
	  MassageHandler.MassageIDLETime=0;
	  if((CharageStatusLowFault!=MassageHandler.ChargeAndMassageStatus)&&
	  	(ChargeStatusComplete!=MassageHandler.ChargeAndMassageStatus)&&
	  	(ChargeStatusIng!=MassageHandler.ChargeAndMassageStatus))
	  	{
	  	  Temp=MassageHandler.Heat_TempInfo;
		  Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_One; //震动一次
		  lk_led_runStatu = LK_LED_BLINK_ONCE;
		  ifHeatStart = TRUE;  //启动加热
		  if(++Temp>Heat_temperature_Zero) //超过最大档
		  	{
		  	  ifHeatStart = FALSE;  
		  	  Temp=Heat_temperature_38;
		  	}
		  if(Heat_temperature_38==Temp)
		  	{
		  	  MassageHandler.Heat_TempInfo=Heat_temperature_38;
		  	}
		  else if(Heat_temperature_40==Temp)
		  	{
		  	  MassageHandler.Heat_TempInfo=Heat_temperature_40;
		  	}
		  else if(Heat_temperature_42==Temp)
		  	{
		  	  MassageHandler.Heat_TempInfo=Heat_temperature_42;
		  	}
		  else
		  	{
		  	  MassageHandler.Heat_TempInfo=Heat_temperature_Zero;
		  	}
		  if(MassageHandler.ChargeAndMassageStatus!=ChargeNoMassageIng)//按下按键进入待按摩模式
		  {
			  MassageHandler.ChargeAndMassageStatus=ChargeNOEnterMassageIng;
		  }
	  	}
   	}
   
   
}

#define ExternsionBoardResisFourVoltage 2000
#define ExternSionBoardResisTwoVoltage  1500


static void ExternBoardCheckHandler(void)
{
   static _electrodesliceType ElectriceTyp=electsliceExtNo,ElectriceTypOld=electsliceExtNo;
   static u8 CheckCount=0;


   if(CompareParaSize(ExtensiondetectBuff.FilterAvgValue,ExternsionBoardResisFourVoltage,200))
   	{
   	   ElectriceTyp=electsliceExtFour;
   	}
   else if(CompareParaSize(ExtensiondetectBuff.FilterAvgValue,ExternsionBoardResisFourVoltage,200))
   	{
   	   ElectriceTyp=electsliceExtLarge; 
   	}
   else
   	{
   	   ElectriceTyp=electsliceExtNo; 
   	}

   if(ElectriceTypOld!=ElectriceTyp)
   	{
   	   if(++CheckCount>=6)
   	   	{
   	   	  CheckCount=0;
		  ElectriceTypOld=ElectriceTyp;
   	   	}
   	}
   else
   	{
   	  CheckCount=0;
   	}
    
	if(MassageHandler.ElectrSliceTyp!=ElectriceTypOld)
	  {
	  	  MassageHandler.ElectrSliceTyp=ElectriceTypOld;
		  Ems_Massage_Mode_update();
	  }
}
static void EMSTimeInit(void)
{
  TimestampInit();
  TimeBoostPwmInit();
  Ems_Start();
}

static void DeviceDataInit(void)
{
  DDL_ZERO_STRUCT(Led_Ctl);
  DDL_ZERO_STRUCT(MassageHandler);
  DDL_ZERO_STRUCT(Heater_Status_Data_Control);
  Heater_Status_Data_Control.Heater_Status=_Heater_Ing;
  Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_StartUp;
  MassageHandler.MassageMode=MassageAcupuncture;
  MassageHandler.ConfigRunTime=15*60;
  MassageHandler.ChargeAndMassageStatus=ChargeStatusNo;
  MassageHandler.MassageIDLETime=0;
  MassageHandler.Heat_TempInfo=Heat_temperature_40;
  MassageHandler.Strength=0;
  MassageHandler.MassageRunTime=0;
  lk_led_runStatu = LK_LED_BREATH;
  
}
static void delay_us_ms_1(u16 cnt)
{
   u16 i=0,j=0;
   for(i=0;i<cnt;i++)
   	{
   	   for(j=0;j<10;j++)
   	   	{
   	   	  ;

   	   	}
	   	;
   	}
}


static void ClkInit24M(void)
{
   Sysctrl_SetRCHTrim(SysctrlRchFreq8MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
   delay10us(10);
   Sysctrl_SetRCHTrim(SysctrlRchFreq16MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
   delay10us(10);
   Sysctrl_SetRCHTrim(SysctrlRchFreq22_12MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
   delay10us(10);
   Sysctrl_SetRCHTrim(SysctrlRchFreq24MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
}

static void ClkInit4M(void)
{
   Sysctrl_SetRCHTrim(SysctrlRchFreq22_12MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
   delay10us(10);
   Sysctrl_SetRCHTrim(SysctrlRchFreq16MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
   delay10us(10);
   Sysctrl_SetRCHTrim(SysctrlRchFreq8MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
   delay10us(10);
   Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);
   Sysctrl_SysClkSwitch(SysctrlClkRCH);
}


static void SysEnterSleepMode(void)
{
   stc_lpm_config_t stcConfig;
   DDL_ZERO_STRUCT(stcConfig);
    stcConfig.enSEVONPEND   = SevPndDisable;
    stcConfig.enSLEEPDEEP   = SlpDpEnable;
    stcConfig.enSLEEPONEXIT = SlpExtDisable;
    Lpm_Config(&stcConfig);
    
    Lpm_GotoLpmMode();
}


static void EMS_Status_Check(void)
{
    EMS_Port_Pin_Status();  
}
#define Motor_Vibr_Time_Defin 50 
#define Motor_Vibr_Time_Short 20
static void Motor_vibration_Control(void)
{
   switch(Motor_Vibr_Control.Motor_Vibr_flag)
   	{
   	  case Motor_Vibr_StartUp:  ///  �?�?
	  	if(Motor_Vibr_Control.Motor_Vibr_flag!=Motor_Vibr_Control.Motor_Vibr_flagOld)
	  	  {
	  		 Motor_Vibr_Control.Motor_Vibr_flagOld=Motor_Vibr_Control.Motor_Vibr_flag;
			 Motor_Vibr_Control.Motor_Vibr_Time=0;
	  	  }
		if(Motor_Vibr_Control.Motor_Vibr_Time<(Motor_Vibr_Time_Defin+50)) ///  50ms
		  {
			 Motor_Open;
		  }
		else
		  {
		     Motor_Close;
			 Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_StopStatus;
			 Motor_Vibr_Control.Motor_Vibr_flagOld=0xff;
		  }
	  	break;
	  case Motor_Vibr_ShutDown:  ///   按键轻振
	  	 if(Motor_Vibr_Control.Motor_Vibr_flag!=Motor_Vibr_Control.Motor_Vibr_flagOld)
	  	  {
	  		 Motor_Vibr_Control.Motor_Vibr_flagOld=Motor_Vibr_Control.Motor_Vibr_flag;
			 Motor_Vibr_Control.Motor_Vibr_Time=0;
	  	  }
		if(Motor_Vibr_Control.Motor_Vibr_Time<(Motor_Vibr_Time_Defin*2+50)) ///  50ms
		  {
			 Motor_Open;
		  }
		else
		  {
		     Motor_Close;
			 Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_StopStatus;
			 Motor_Vibr_Control.Motor_Vibr_flagOld=0xff;
			 LowPowerControl.LowPowerFlag=LowPowerImmedShutdown;
		  }
	  	break;
	  case Motor_Vibr_One:  //  振动两次
	  	  if(Motor_Vibr_Control.Motor_Vibr_flag!=Motor_Vibr_Control.Motor_Vibr_flagOld)
	  	  {
	  		 Motor_Vibr_Control.Motor_Vibr_flagOld=Motor_Vibr_Control.Motor_Vibr_flag;
			 Motor_Vibr_Control.Motor_Vibr_Time=0;
			 Motor_Vibr_Control.Motor_Vibr_Count=1;
	  	  }
		if(Motor_Vibr_Control.Motor_Vibr_Time<Motor_Vibr_Time_Short) ///  50ms
		  {
			 Motor_Open;
		  }
		else if(Motor_Vibr_Control.Motor_Vibr_Time<(Motor_Vibr_Time_Short+1))
		  {
             Motor_Close; 		  
 		  }
		else 
		  {
			 if(--Motor_Vibr_Control.Motor_Vibr_Count==0)
			 {
			   Motor_Close; 
			   Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_StopStatus;
			   Motor_Vibr_Control.Motor_Vibr_flagOld=0xff;
			 }
			 else
			 {
			    Motor_Vibr_Control.Motor_Vibr_Time=0;
			 }
		  }
	  	break;
	  case Motor_Vibr_Two_Fast:
	  	if(Motor_Vibr_Control.Motor_Vibr_flag!=Motor_Vibr_Control.Motor_Vibr_flagOld)
	  	  {
	  		 Motor_Vibr_Control.Motor_Vibr_flagOld=Motor_Vibr_Control.Motor_Vibr_flag;
			 Motor_Vibr_Control.Motor_Vibr_Time=0;
			 Motor_Vibr_Control.Motor_Vibr_Count=2;
	  	  }
		if(Motor_Vibr_Control.Motor_Vibr_Time<Motor_Vibr_Time_Short) ///  50ms
		  {
			 Motor_Open;
		  }
		else if(Motor_Vibr_Control.Motor_Vibr_Time<(Motor_Vibr_Time_Short*2))
		  {
             Motor_Close;
 		  }
		else 
		  {
			 if(--Motor_Vibr_Control.Motor_Vibr_Count==0)
			 {
			   Motor_Close;
			   Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_StopStatus;
			   Motor_Vibr_Control.Motor_Vibr_flagOld=0xff;
			 }
			 else
			 {
			    Motor_Vibr_Control.Motor_Vibr_Time=0;
			 }
		  }
	  	break;
	  case Motor_Vibr_Two_0s5:
	  	if(Motor_Vibr_Control.Motor_Vibr_flag!=Motor_Vibr_Control.Motor_Vibr_flagOld)
	  	  {
	  		 Motor_Vibr_Control.Motor_Vibr_flagOld=Motor_Vibr_Control.Motor_Vibr_flag;
			 Motor_Vibr_Control.Motor_Vibr_Time=0;
			 Motor_Vibr_Control.Motor_Vibr_Count=2;
	  	  }
		if(Motor_Vibr_Control.Motor_Vibr_Time<Motor_Vibr_Time_Defin) ///  50ms
		  {
			 Motor_Open;
		  }
		else if(Motor_Vibr_Control.Motor_Vibr_Time<(Motor_Vibr_Time_Defin*2))
		  {
             Motor_Close;		  
 		  }
		else 
		  {
			 if(--Motor_Vibr_Control.Motor_Vibr_Count==0)
			 {
			   Motor_Open; 
			   Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_StopStatus;
			   Motor_Vibr_Control.Motor_Vibr_flagOld=0xff;
			 }
			 else
			 {
			    Motor_Vibr_Control.Motor_Vibr_Time=0;
			 }
		  }
	  	break;
	  case Motor_Vibr_EnterStopStatus:
	  	Motor_Close;
		Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_StopStatus;
	  	break;
	  case Motor_Vibr_StopStatus:
	  	Motor_Close;
	  	break;
   	}
}

#define Battery_Voltage_Limit_Value 3200
#define Battery_Voltage_Limit_MassageIng 3000
static void Battery_Status_Check(void)
{
   static u8 ErrorCount=0;
   Battery_Chg_Status_Pin_Scan();

   if(FALSE==Chg_Status_CheckHandler.status_CheckData)
   	{
   	  if((ChargeNoMassageIng==MassageHandler.ChargeAndMassageStatus
	  	)||(ChargeNOEnterMassageIng==MassageHandler.ChargeAndMassageStatus))
   	  	{
   	  	  if(TRUE==Heater_Status_Data_Control.Heater_Flag)
   	  	   {
	   	  	  if(NTCDataSmaple.BatteryVoltageSample.FilterAvgValue<Battery_Voltage_Limit_MassageIng)
			   	{
			   	   if(++ErrorCount>=40)
			   	   	{
			   	   	   ErrorCount=0;
			   	       MassageHandler.ChargeAndMassageStatus=CharageStatusLowFault;
			   	   	}
			   	}
			  else
			  	{
			  	   ErrorCount=0;
			  	}
   	  	  }
   	  	}
	  else
	  	{
	  	   if(NTCDataSmaple.BatteryVoltageSample.FilterAvgValue<Battery_Voltage_Limit_Value)
		   	{
		   	   if(++ErrorCount>=20)
		   	   	{
		   	   	   ErrorCount=0;
		   	       MassageHandler.ChargeAndMassageStatus=CharageStatusLowFault;
		   	   	}
		   	}
		  else
		  	{
		  	   ErrorCount=0;
		  	}
	  	}
   	  
   	}
   else
   	{
   	   ErrorCount=0;
   	   if(Motor_Vibr_ShutDown==Motor_Vibr_Control.Motor_Vibr_flag)
   	   	{
   	   	   Motor_Vibr_Control.Motor_Vibr_flag=Motor_Vibr_EnterStopStatus;
   	   	}
   	}
}
#define Heat_Time_Interval_Value 50
const u8 Heat_temperatureTable[]={
38,40,42,0
};

static void Heat_temperature_Control(void)
{

  switch(Heater_Status_Data_Control.Heater_Status)
  	{
	 case _Heater_Ing:
	 	if(MassageHandler.Heat_TempInfo!=Heat_temperature_Zero)
	    {
		   if(NTCDataSmaple.tempvalue>=Heat_temperatureTable[MassageHandler.Heat_TempInfo])
			 {
			      Heater_Close;
			 }
		  else
			 {
				  Heater_Open;
		    }
		}
	   else
		{
			     Heater_Close;
	    }
	    if(Heater_Status_Data_Control.periodic_Time>100)
		{
		   Heater_Status_Data_Control.periodic_Time=0;
		   Heater_Status_Data_Control.Heater_Status=_Heater_StDly;
		   Heater_Close;
		}
		Heater_Status_Data_Control.Heater_Flag=FALSE;
	 	break;
	 case _Heater_StDly:
	 	Heater_Close;
		Heater_Status_Data_Control.Heater_Flag=FALSE;
		if(Heater_Status_Data_Control.periodic_Time>1)
		{
		   Heater_Status_Data_Control.Heater_Status=_Heater_CheckBt;
		   Heater_Status_Data_Control.Heater_Flag=TRUE;
		}
	 	break;
	 case _Heater_CheckBt:
	 	Heater_Status_Data_Control.Heater_Flag=TRUE;
	 	if(Heater_Status_Data_Control.periodic_Time>3)
		{
		   Heater_Status_Data_Control.Heater_Status=_Heater_Ing;
		}
	 	break;
  	}
  
}

static void Heat_Temperature_Close(void)
{
    Heater_Close;
}

void SoftTimerCount(void)
{
  SoftTimeTask();
}

#define DefineLowPowerDelayTime 3
static void LowPowerHandler(void)
{
     switch(LowPowerControl.LowPowerFlag)
     	{
     	   case LowPowerImmedShutdown:
		   	//if(LowPowerControl.LowPowerDelayTime>DefineLowPowerDelayTime)
	         {
		        LowPowerControl.LowPowerFlag=LowPowerStopStatus;
				LowPowerControl.LowPowerDelayTime=0;
				LED_1_Close;
				Time3Breathing_Light_Duty(0);  //关闭�?
				Motor_Close;
				Heater_Close;
				Battery_Close;
		        Ems_SleepInit();
		        Update2TimeSleep();
				AdcSampleSleepInit();
				breathing_SleepInit();
				ClkInit4M();
				delay_us_ms_1(50);
				ExtTrigInterrupteRouseEnable();
				EMS_Port_Pin_Disable_IRQ();
				SysEnterSleepMode();
				
                
				ClkInit24M();
				DeviceDataInit();
				ExtTrigInterrupteRouseDisable();
				HardWareInit();
			    Ems_ParaInit();
				KeyInit2();
				breathing_LightInit();
	        }
		   	break;
		   case LowPowerDelayShutdown:
		   case LowPowerNoCancelShutdown:
		   	  // if(Motor_Vibr_Control.Motor_Vibr_flag==Motor_Vibr_StopStatus)
		   	   	{ 
							LowPowerControl.LowPowerFlag=LowPowerStopStatus;
							LED_1_Close;
							Motor_Close;							
							Heater_Close;
							Battery_Close;
							Time3Breathing_Light_Duty(0);  //关闭�?
							Ems_SleepInit();
							Update2TimeSleep();
							AdcSampleSleepInit();
							breathing_SleepInit();
							ClkInit4M();
							delay_us_ms_1(50);
							ExtTrigInterrupteRouseEnable();
							SysEnterSleepMode();
							
							ClkInit24M();
							ExtTrigInterrupteRouseDisable();
								HardWareInit();
							DeviceDataInit();
							Ems_ParaInit();
							KeyInit2();
							breathing_LightInit();
		   	   	}
		   	break;
		  case LowPowerStopStatus:
		  	break;
     	}
     
}


void LED_Status_Control(void)
{
     lk_led_handle(lk_led_runStatu);
}

void lk_control_f(void)
{

   
  
  


}


