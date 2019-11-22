#include "EMS.h"
#include "TimeHandler.h"
#include "Wave.h"
#include "TypedefDef.h"
#include "EMS_Port.h"
#include "Global.h"
#include "base_types.h"
#include "Util.h"

static void _DirAB_And_CD_IDLE(u32 pulse,u8* L_R);
static void _DirAB_And_CD_DisCharge(u32 pulse,u8* L_R);
static void _DirA_T_B_And_CD_No(u32 pulse,u8* L_R);
static void _DirA_T_B_And_C_T_D(u32 pulse,u8* L_R);
static void _DirA_T_B_And_D_T_C(u32 pulse,u8* L_R);
static void _DirA_T_B_And_CDAuto_PN(u32 pulse,u8* L_R);
static void _DirA_T_C_And_BD_No(u32 pulse,u8* L_R);
static void _DirA_T_C_And_B_T_D(u32 pulse,u8* L_R);
static void _DirA_T_C_And_D_T_B(u32 pulse,u8* L_R);
static void _DirA_T_C_And_BDAuto_PN(u32 pulse,u8* L_R);
static void _DirA_T_D_And_BC_No(u32 pulse,u8* L_R);
static void _DirA_T_D_And_B_T_C(u32 pulse,u8* L_R);
static void _DirA_T_D_And_C_T_B(u32 pulse,u8* L_R);
static void _DirA_T_D_And_BCAuto_PN(u32 pulse,u8* L_R);
static void _DirB_T_A_And_CD_No(u32 pulse,u8* L_R);
static void _DirB_T_A_And_C_T_D(u32 pulse,u8* L_R);
static void _DirB_T_A_And_D_T_C(u32 pulse,u8* L_R);
static void _DirB_T_A_And_CDAuto_PN(u32 pulse,u8* L_R);
static void _DirB_T_C_And_AD_No(u32 pulse,u8* L_R);
static void _DirB_T_C_And_A_T_D(u32 pulse,u8* L_R);
static void _DirB_T_C_And_D_T_A(u32 pulse,u8* L_R);
static void _DirB_T_C_And_ADAuto_PN(u32 pulse,u8* L_R);
static void _DirB_T_D_And_AC_No(u32 pulse,u8* L_R);
static void _DirB_T_D_And_A_T_C(u32 pulse,u8* L_R);
static void _DirB_T_D_And_C_T_A(u32 pulse,u8* L_R);
static void _DirB_T_D_And_ACAuto_PN(u32 pulse,u8* L_R);
static void _DirC_T_A_And_BD_No(u32 pulse,u8* L_R);
static void _DirC_T_A_And_B_T_D(u32 pulse,u8* L_R);
static void _DirC_T_A_And_D_T_B(u32 pulse,u8* L_R);
static void _DirC_T_A_And_BDAuto_PN(u32 pulse,u8* L_R);
static void _DirC_T_B_And_AD_No(u32 pulse,u8* L_R);
static void _DirC_T_B_And_A_T_D(u32 pulse,u8* L_R);
static void _DirC_T_B_And_D_T_A(u32 pulse,u8* L_R);
static void _DirC_T_B_And_ADAuto_PN(u32 pulse,u8* L_R);
static void _DirC_T_D_And_AB_No(u32 pulse,u8* L_R);
static void _DirC_T_D_And_A_T_B(u32 pulse,u8* L_R);
static void _DirC_T_D_And_B_T_A(u32 pulse,u8* L_R);
static void _DirC_T_D_And_ABAuto_PN(u32 pulse,u8* L_R);
static void _DirD_T_A_And_CB_No(u32 pulse,u8* L_R);
static void _DirD_T_A_And_C_T_B(u32 pulse,u8* L_R);
static void _DirD_T_A_And_B_T_C(u32 pulse,u8* L_R);
static void _DirD_T_A_And_BC_AutO_PN(u32 pulse,u8* L_R);
static void _DirABAuto_And_CDAuto_PN(u32 pulse,u8* L_R);
static void _DirACAutO_And_BDAut0_PN(u32 pulse,u8* L_R);
static void _DirADAuto_And_BCAuto_PN(u32 pulse,u8* L_R);
static void _DirA_T_B_And_CD_No_PN(u32 pulse,u8* L_R);
static void _DirA_T_C_And_BD_No_PN(u32 pulse,u8* L_R);
static void _DirA_T_D_And_BC_No_PN(u32 pulse,u8* L_R);
static void _DirB_T_A_And_CD_No_PN(u32 pulse,u8* L_R);
static void _DirB_T_C_And_AD_No_PN(u32 pulse,u8* L_R);
static void _DirB_T_D_And_AC_No_PN(u32 pulse,u8* L_R);
static void _DirC_T_A_And_BD_No_PN(u32 pulse,u8* L_R);
static void _DirC_T_B_And_AD_No_PN(u32 pulse,u8* L_R);
static void _DirC_T_D_And_AB_No_PN(u32 pulse,u8* L_R);
static void _DirD_T_A_And_BC_No_PN(u32 pulse,u8* L_R);
static void _DirD_T_B_And_AC_No_PN(u32 pulse, u8* L_R);
static void _DirD_T_C_And_AB_No_PN(u32 pulse,u8* L_R);
static void _DirABC_T_D_PN(u32 pulse,u8*L_R);
static void _DirABD_T_C_PN(u32 pulse,u8*L_R);
static void _DirACD_T_B_PN(u32 pulse,u8*L_R);
static void _DirCBD_T_A_PN(u32 pulse,u8*L_R);


void (*Dir3DModeMassage_Invoke[DirCBD_T_A_PN+1])(u32,u8*)=
{
  _DirAB_And_CD_IDLE,
  _DirAB_And_CD_DisCharge,
  _DirA_T_B_And_CD_No,
  _DirA_T_B_And_C_T_D,
  _DirA_T_B_And_D_T_C,
  _DirA_T_B_And_CDAuto_PN,
  
  _DirA_T_C_And_BD_No,
  _DirA_T_C_And_B_T_D,
  _DirA_T_C_And_D_T_B,
  _DirA_T_C_And_BDAuto_PN,
  
  _DirA_T_D_And_BC_No,
  _DirA_T_D_And_B_T_C,
  _DirA_T_D_And_C_T_B,
  _DirA_T_D_And_BCAuto_PN,
  
  _DirB_T_A_And_CD_No,
  _DirB_T_A_And_C_T_D,
  _DirB_T_A_And_D_T_C,
  _DirB_T_A_And_CDAuto_PN,
  
  _DirB_T_C_And_AD_No,
  _DirB_T_C_And_A_T_D,
  _DirB_T_C_And_D_T_A,
  _DirB_T_C_And_ADAuto_PN,
  
  _DirB_T_D_And_AC_No,
  _DirB_T_D_And_A_T_C,
  _DirB_T_D_And_C_T_A,
  _DirB_T_D_And_ACAuto_PN,
  
  _DirC_T_A_And_BD_No,
  _DirC_T_A_And_B_T_D,
  _DirC_T_A_And_D_T_B,
  _DirC_T_A_And_BDAuto_PN,
  
  _DirC_T_B_And_AD_No,
  _DirC_T_B_And_A_T_D,
  _DirC_T_B_And_D_T_A,
  _DirC_T_B_And_ADAuto_PN,
  
  _DirC_T_D_And_AB_No,
  _DirC_T_D_And_A_T_B,
  _DirC_T_D_And_B_T_A,
  _DirC_T_D_And_ABAuto_PN,
  
  _DirD_T_A_And_CB_No,
  _DirD_T_A_And_C_T_B,
  _DirD_T_A_And_B_T_C,
  _DirD_T_A_And_BC_AutO_PN,

  _DirA_T_B_And_CD_No_PN,
  _DirA_T_C_And_BD_No_PN,
  _DirA_T_D_And_BC_No_PN,
  _DirB_T_A_And_CD_No_PN,
  _DirB_T_C_And_AD_No_PN,
  _DirB_T_D_And_AC_No_PN,
  _DirC_T_A_And_BD_No_PN,
  _DirC_T_B_And_AD_No_PN,
  _DirC_T_D_And_AB_No_PN,
  _DirD_T_A_And_BC_No_PN,
  _DirD_T_B_And_AC_No_PN,
  _DirD_T_C_And_AB_No_PN,
  _DirABC_T_D_PN,
  _DirABD_T_C_PN,
  _DirACD_T_B_PN,
  _DirCBD_T_A_PN,
  
  _DirABAuto_And_CDAuto_PN,
  _DirACAutO_And_BDAut0_PN,
  _DirADAuto_And_BCAuto_PN,
};




static void ModifyOne(u8*datap);
static void ModifyTwo(u8*datap);

void (*Modify2Data[2])(u8*)=
{
  ModifyOne,
  ModifyTwo,
};



 void (*Dischargeinvoke[3])(u32)=
{
  Ems_A_To_Ems_B_Double,
  Ems_A_To_Ems_B_Double,
  Ems_AB_And_CD_Four,
};

 void (*Dirforwardinvoke[3])(u32)=
{
   Ems_A_To_Ems_B_Single_P,
   Ems_A_To_Ems_B_Single_P,
   Ems_AToB_Ems_CToD_FS_P,
};

 void (*Dirreverseinvoke[3])(u32)=
{
   Ems_A_To_Ems_B_Single_N,
   Ems_A_To_Ems_B_Single_N,
   Ems_AToB_Ems_CToD_FS_N,
};

 void (*DirPNAlter_L_invoke[3])(u32)=
{
   Ems_A_To_Ems_B_PNAlter_P,
   Ems_A_To_Ems_B_PNAlter_P,
   Ems_AToB_And_Ems_CToD_PNAlter_P,
};

 void (*DirPNAlter_R_invoke[3])(u32)=
{
   Ems_A_To_Ems_B_PNAlter_N,
   Ems_A_To_Ems_B_PNAlter_N,
   Ems_AToB_And_Ems_CToD_PNAlter_N,
};

#define DirPNAlter_Move_Max 4
 void (*DirPNAlter_RL_Invoke[3][DirPNAlter_Move_Max])(u32)=
{
 	{Ems_A_To_Ems_B_PNAlter_P,Ems_A_To_Ems_B_PNAlter_N,Ems_A_To_Ems_B_PNAlter_N,Ems_A_To_Ems_B_PNAlter_P},
 	{Ems_A_To_Ems_B_PNAlter_P,Ems_A_To_Ems_B_PNAlter_N,Ems_A_To_Ems_B_PNAlter_N,Ems_A_To_Ems_B_PNAlter_P},
 	{Ems_AToB_And_Ems_CToD_PNAlter_P,Ems_AToB_And_Ems_CToD_PNAlter_N,Ems_AToB_And_Ems_CToD_PNAlter_N,Ems_AToB_And_Ems_CToD_PNAlter_P},
};

 void (*DiralternateInvoke[3][2])(u32)=
{
    {Ems_A_To_Ems_B_Single_P,Ems_A_To_Ems_B_Single_N},
    {Ems_A_To_Ems_B_Single_P,Ems_A_To_Ems_B_Single_N},
    {Ems_AToB_Ems_CToD_FS_P,Ems_AToB_Ems_CToD_FS_N},
};


#define PWM_Duty_Range 40
#define Current_Limit_Value 45
#define Pulse_Max_Value 50
#define Voltage_Ripple_Value 2000
#define Voltage_Upgrade_Range 2200
_EMS_Control Ems_Control;
static void MassagePwmCHandler(void);
static void BoostVoltageControl(u32 VoltageValue);
static void Massage3DModelPwmCHandler(void);
static void MassagePwmIdleHandler(void);
static void Ems_3DParaInit(void);
static void Ems_2DParaInit(void);
static void Ems_IDLEParaInit(void);
#define Temp_Power_Adc 25000
#define Temp_Power_Adc_Zero 5000

_PwmProcessDataHandler PwmProcessDataHandler;
_StrgUpdateControl StrengUpdateControl;


static void BoostVoltageControl(u32 VoltageValue)
{
      u32 Temp=0;
	  Temp=(VoltageValue/10);
      if((Temp+100)>VoltageSampleBuff.FilterAvgValue)
	    { 
			  if((Ems_Control.Pwm_Duty+60)<(Boost_ValueMax-PWM_Duty_Range))
			    {
					   Ems_Control.Pwm_Duty+=60;
			    }
			  else if((Ems_Control.Pwm_Duty+40)<(Boost_ValueMax-PWM_Duty_Range))
			    {
					  Ems_Control.Pwm_Duty+=40; 
				}
			  else if((Ems_Control.Pwm_Duty+20)<(Boost_ValueMax-PWM_Duty_Range))
			  	{
			  	     Ems_Control.Pwm_Duty+=20; 
			  	}
			  else
			  	{
			  	      Ems_Control.Pwm_Duty=(Boost_ValueMax-PWM_Duty_Range); 
			  	}
		 }
	 else if((Temp+10)>VoltageSampleBuff.FilterAvgValue)
		 {
			   if(Ems_Control.Pwm_Duty+40<(Boost_ValueMax-PWM_Duty_Range))
			  	 {
			  	    Ems_Control.Pwm_Duty+=40;
			  	 }	
			   else if(Ems_Control.Pwm_Duty+20<(Boost_ValueMax-PWM_Duty_Range))
			   	{
			   	    Ems_Control.Pwm_Duty+=20;
			   	}
			   else 
			   	    Ems_Control.Pwm_Duty++;
		 }	
	 else if((Temp+1)>VoltageSampleBuff.FilterAvgValue)
		 {
			  	 if(Ems_Control.Pwm_Duty+5<(Boost_ValueMax-PWM_Duty_Range))
			  	 {
			  	       Ems_Control.Pwm_Duty+=5;
			  	 }
				 else
				 {
				       Ems_Control.Pwm_Duty++;
				 }
		 }
	 
	if((Temp)<(VoltageSampleBuff.FilterAvgValue+100))
	  {	 

		    if(Ems_Control.Pwm_Duty>80)
			  {
				 Ems_Control.Pwm_Duty-=80;
			  }
			else if(Ems_Control.Pwm_Duty>60)
			  {
			     Ems_Control.Pwm_Duty-=60;
			  }
			else if(Ems_Control.Pwm_Duty>40)
			  {
			      Ems_Control.Pwm_Duty-=40;
			  }
			else if(Ems_Control.Pwm_Duty>20)
			  {
			      Ems_Control.Pwm_Duty-=20;
			  }
			else if(Ems_Control.Pwm_Duty>0)
			  {
			    Ems_Control.Pwm_Duty--;
			  }
									  		 
		}
	 else if(Temp<(VoltageSampleBuff.FilterAvgValue+10))
	    {
			if(Ems_Control.Pwm_Duty>60)
			  {
				 Ems_Control.Pwm_Duty-=60;
			  }
			else if(Ems_Control.Pwm_Duty>40)
			  {
				 Ems_Control.Pwm_Duty-=40;
			  }
			else if(Ems_Control.Pwm_Duty>20)
			  {
				 Ems_Control.Pwm_Duty-=20;
			  }
			else if(Ems_Control.Pwm_Duty>0)
			  {
				 Ems_Control.Pwm_Duty--;
			  }
				   
		}
	else if(Temp<(VoltageSampleBuff.FilterAvgValue+1))
		{
		      if(Ems_Control.Pwm_Duty>0)
			   {
				   Ems_Control.Pwm_Duty-=1;
			   }
		}
	    Boost_Pwm(Ems_Control.Pwm_Duty);
}


void Ems_Output_Close(void)
{
   Ems_Control.Pwm_Duty=0;
   Boost_Pwm(Ems_Control.Pwm_Duty);
}


void Ems_ParaInit(void)
{
    switch(MassageHandler.MassageMode)
     	{
     	 case MassageIDLE:
		 	Ems_IDLEParaInit();
		 	break;
		 case MassageAcupuncture:
		 case MassageMalaxation:
		 case Massagescraping:
		 case MassageKnock:
		 	Ems_2DParaInit();
		 	break;
		 case Massage3DAcupuncture:
		 case Massage3DMalaxation:
		 case Massage3Dscraping:
		 case Massage3DKnock:
		 	Ems_3DParaInit();
		 	break;
     	}
}

static void Ems_IDLEParaInit(void)
{
   _PwmPulseData *GetpwmPulseArray;
   
    GetpwmPulseArray=MassageIDLEStatus[MassageHandler.MassageMode-MassageIDLE].pwmPulseArray;
    PwmProcessDataHandler.PwmConfig_IndexMax=MassageIDLEStatus[MassageHandler.MassageMode-MassageIDLE].ArrayMax;
	PwmProcessDataHandler.PwmArrIndex=0;
	PwmProcessDataHandler.PwmOutDir=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmOutDir;	
	PwmProcessDataHandler.repetCount=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->repetCount;
	PwmProcessDataHandler.TimeArrValue=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmInterval;
	PwmProcessDataHandler.PwmPulse=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmPulse;
    PwmProcessDataHandler.SwitchOutDisable=TRUE; 
	TimestampUpdateFreq(PwmProcessDataHandler.TimeArrValue);
}

static void Ems_2DParaInit(void)
{
    _PwmPulseData *GetpwmPulseArray;
	 
    GetpwmPulseArray=MassageModeArray[MassageHandler.MassageMode-MassageAcupuncture].pwmPulseArray;
	PwmProcessDataHandler.PwmConfig_IndexMax=MassageModeArray[MassageHandler.MassageMode-MassageAcupuncture].ArrayMax;
	PwmProcessDataHandler.PwmArrIndex=0;
	PwmProcessDataHandler.PwmOutDir=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmOutDir;	
	PwmProcessDataHandler.repetCount=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->repetCount;
	PwmProcessDataHandler.TimeArrValue=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmInterval;
	PwmProcessDataHandler.PwmPulse=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmPulse;
    PwmProcessDataHandler.SwitchOutDisable=TRUE;
	TimestampUpdateFreq(PwmProcessDataHandler.TimeArrValue);
	
	
}

static void Ems_3DParaInit(void)
{
    _PwmPulse3Ddata *GetpwmPulseArray;
    GetpwmPulseArray=KnockMode3DMassage[MassageHandler.MassageMode-Massage3DAcupuncture].pwmPulseArray;
    PwmProcessDataHandler.PwmConfig_IndexMax=KnockMode3DMassage[MassageHandler.MassageMode-Massage3DAcupuncture].ArrayMax;
	PwmProcessDataHandler.PwmArrIndex=0;
	PwmProcessDataHandler.Pwm3DDir=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->Mode3Dgroup;	
	PwmProcessDataHandler.repetCount=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->repetCount;
	PwmProcessDataHandler.TimeArrValue=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmInterval;
	PwmProcessDataHandler.PwmPulse=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmPulse;
	PwmProcessDataHandler.SwitchOutDisable=TRUE;
	TimestampUpdateFreq(PwmProcessDataHandler.TimeArrValue);
}

void Ems_Start(void)
{
   
    Boost_Start();	  
    TimestampStart();
}

void Ems_Stop(void)
{
    TimestampStop();
	Boost_Stop();
}
#define StrengthUpdateTimeValue 500

void EMSControlHandler(void)
{
   switch(MassageHandler.MassageMode)
   	{
   	 case MassageIDLE:  //  智能模式
   	    if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	   StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
		      if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
		}
		break;
	 case MassageAcupuncture:  //  舒缓模式
        if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	   StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
          if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
		}
		break;
	 case MassageMalaxation:  //  活力模式
        if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	   StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
          if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
		}
		break;
	 case Massagescraping:  // 揉
        if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	    StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
         if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
			}
		break;
	 case MassageKnock:  // 压
        if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	    StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
          if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
			}
		break;
	 case Massage3DAcupuncture:   //  敲
        if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	   StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;				  
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
          if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
		}
		break;
	 case Massage3DMalaxation:    // 搓
        if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	   StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
          if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
		}
		break;
	 case Massage3Dscraping: //  振动
        if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	    StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
         if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
		}
		break;
	 case Massage3DKnock:
	 	if(StrengUpdateControl.StrgUpdateFlag>0)
   	    {
	   	    if(StrengUpdateControl.StrgUpdateTime>=StrengthUpdateTimeValue)
		  	{
		  	   StrengUpdateControl.StrgUpdateTime=0;
		  	   if(StrengUpdateControl.StrengthOld<MassageHandler.StrengthOld)
		  	   	{
		  	   	   StrengUpdateControl.StrengthOld++;
		  	   	}
			   else
			   	{
			   	  StrengUpdateControl.StrgUpdateFlag=0;				  
				  MassageHandler.Strength=StrengUpdateControl.StrengthOld;
			   	}
		  	}
			BoostVoltageControl(Temp_Power_Adc+(StrengUpdateControl.StrengthOld*Voltage_Upgrade_Range));
   	    }
		else
		{
          if(MassageHandler.Strength==0)
		      	{
		      	 BoostVoltageControl(Temp_Power_Adc_Zero+(MassageHandler.Strength*Voltage_Upgrade_Range));
		      	}
					else
						{
          BoostVoltageControl(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range));
						}
		}
	 	break;
		}

   if(TRUE==PwmProcessDataHandler.SwitchOutDisable)
   	{
   	   
   	   if(CompareParaSize(Temp_Power_Adc+(MassageHandler.Strength*Voltage_Upgrade_Range),
	   	VoltageSampleBuff.FilterAvgValue,Voltage_Ripple_Value)>0)
   	   	{
   	   	  PwmProcessDataHandler.SwitchOutDisable=FALSE;
   	   	}
   	}
}

void EMS_PwmControl(void)
{
    #if 0
     if(TRUE==PwmProcessDataHandler.SwitchOutDisable)
     	{
     	  return ;
     	}
	 #endif
     switch(MassageHandler.MassageMode)
     	{
     	 case MassageIDLE:
		 	MassagePwmIdleHandler();
		 	break;
		 case MassageAcupuncture:
		 case MassageMalaxation:
		 case Massagescraping:
		 case MassageKnock:
		 	MassagePwmCHandler();
		 	break;
		 case Massage3DAcupuncture:
		 case Massage3DMalaxation:
		 case Massage3Dscraping:
		 case Massage3DKnock:
		 	Massage3DModelPwmCHandler(); 
		 	break;
     	}
}

static void MassagePwmIdleHandler(void)
{
   
   static _PwmDir PwmDirOld;
   static u8 alternateDir=0;
   static u16 OldValue=0;   
   static u8 DirPNAlterMoveCount=0;
    _PwmPulseData *GetpwmPulseArray;
   GetpwmPulseArray=MassageIDLEStatus[0].pwmPulseArray; 
   if(--PwmProcessDataHandler.repetCount==0)
	 {
	   	   PwmProcessDataHandler.PwmArrIndex++;
		   if(PwmProcessDataHandler.PwmArrIndex>=PwmProcessDataHandler.PwmConfig_IndexMax)
			{
			    PwmProcessDataHandler.PwmArrIndex=0;
			}
		    PwmProcessDataHandler.PwmOutDir=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmOutDir;
			PwmProcessDataHandler.repetCount=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->repetCount;
			PwmProcessDataHandler.TimeArrValue=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmInterval;
			PwmProcessDataHandler.PwmPulse=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmPulse;
			PwmProcessDataHandler.PwmConfig_repetMax=PwmProcessDataHandler.repetCount;
			
	  }

    switch(PwmProcessDataHandler.PwmOutDir)
   	{
   	   case Dirdischarge:

       
        Dischargeinvoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);		
	   	break;
	   case Dirforward:
	   	if((PwmProcessDataHandler.repetCount+10)<PwmProcessDataHandler.PwmConfig_repetMax)
	   	{
	   	  if(OldValue!=(PwmProcessDataHandler.repetCount%10))
	   	  	{
	   	  	  OldValue=PwmProcessDataHandler.repetCount%10;
	   	  	  if(PwmProcessDataHandler.PwmPulse<Pulse_Max_Value)
	   	  	  	{
			  	  PwmProcessDataHandler.PwmPulse++;
	   	  	  	}
	   	  	}
	   	}
		Dirforwardinvoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
	   case Dirreverse:
	   	if((PwmProcessDataHandler.repetCount+10)<PwmProcessDataHandler.PwmConfig_repetMax)
	   	{
	   	  if(OldValue!=(PwmProcessDataHandler.repetCount%10))
	   	  	{
	   	  	  OldValue=PwmProcessDataHandler.repetCount%10;
	   	  	  if(PwmProcessDataHandler.PwmPulse<Pulse_Max_Value)
	   	  	  	{
			  	  PwmProcessDataHandler.PwmPulse++;
	   	  	  	}
	   	  	}
	   	}
		Dirreverseinvoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
		
	   case DirIDLE:
	   	
	   	break;
		
	   case DirPNAlter:
	   	if((PwmProcessDataHandler.repetCount+10)<PwmProcessDataHandler.PwmConfig_repetMax)
	   	{
	   	  if(OldValue!=(PwmProcessDataHandler.repetCount%10))
	   	  	{
	   	  	  OldValue=PwmProcessDataHandler.repetCount%10;
	   	  	  if(PwmProcessDataHandler.PwmPulse<Pulse_Max_Value)
	   	  	  	{
			  	  PwmProcessDataHandler.PwmPulse++;
	   	  	  	}
	   	  	}
	   	}
		DirPNAlter_RL_Invoke[MassageHandler.ElectrSliceTyp][DirPNAlterMoveCount](PwmProcessDataHandler.PwmPulse);
		if(++DirPNAlterMoveCount>=DirPNAlter_Move_Max)
		{
		    DirPNAlterMoveCount=0;
		}
	   	break;
		
	   case DirPNAlterL:
	   	DirPNAlter_L_invoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
		
       case DirPNAlterR:
	   	DirPNAlter_R_invoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
		
	   case Diralternate:
	   	DiralternateInvoke[MassageHandler.ElectrSliceTyp][alternateDir](PwmProcessDataHandler.PwmPulse);
		Modify2Data[alternateDir](&alternateDir);
	   	break;
   	}

   if(PwmDirOld!=PwmProcessDataHandler.PwmOutDir)
   	{
   	   PwmDirOld=PwmProcessDataHandler.PwmOutDir;
	   TimestampUpdateFreq(PwmProcessDataHandler.TimeArrValue);
   	}
}

static void MassagePwmCHandler(void)
{
   static _PwmDir PwmDirOld;
   static u8 alternateDir=0;
   static u16 OldValue=0;
   static u8 DirPNAlterMoveCount=0;
   _PwmPulseData *GetpwmPulseArray;
   GetpwmPulseArray=MassageModeArray[MassageHandler.MassageMode-MassageAcupuncture].pwmPulseArray;
   if(--PwmProcessDataHandler.repetCount==0)
	 {
	   	   PwmProcessDataHandler.PwmArrIndex++;
		   if(PwmProcessDataHandler.PwmArrIndex>=PwmProcessDataHandler.PwmConfig_IndexMax)
			{
			    PwmProcessDataHandler.PwmArrIndex=0;
			}
		    PwmProcessDataHandler.PwmOutDir=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmOutDir;
			PwmProcessDataHandler.repetCount=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->repetCount;
			PwmProcessDataHandler.TimeArrValue=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmInterval;
			PwmProcessDataHandler.PwmPulse=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmPulse;
			PwmProcessDataHandler.PwmConfig_repetMax=PwmProcessDataHandler.repetCount;
			
	  }
   
   switch(PwmProcessDataHandler.PwmOutDir)
   	{
   	   case Dirdischarge:
        Dischargeinvoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);		
	   	break;
	   case Dirforward:
	   	if((PwmProcessDataHandler.repetCount+10)<PwmProcessDataHandler.PwmConfig_repetMax)
	   	{
	   	  if(OldValue!=(PwmProcessDataHandler.repetCount%10))
	   	  	{
	   	  	  OldValue=PwmProcessDataHandler.repetCount%10;
	   	  	  if(PwmProcessDataHandler.PwmPulse<Pulse_Max_Value)
	   	  	  	{
			  	  PwmProcessDataHandler.PwmPulse++;
	   	  	  	}
	   	  	}
	   	}
		Dirforwardinvoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
	   case Dirreverse:
	   	if((PwmProcessDataHandler.repetCount+10)<PwmProcessDataHandler.PwmConfig_repetMax)
	   	{
	   	  if(OldValue!=(PwmProcessDataHandler.repetCount%10))
	   	  	{
	   	  	  OldValue=PwmProcessDataHandler.repetCount%10;
	   	  	  if(PwmProcessDataHandler.PwmPulse<Pulse_Max_Value)
	   	  	  	{
			  	  PwmProcessDataHandler.PwmPulse++;
	   	  	  	}
	   	  	}
	   	}
		Dirreverseinvoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
		
	   case DirIDLE:
	   	
	   	break;
		
	   case DirPNAlter:
	   	if((PwmProcessDataHandler.repetCount+10)<PwmProcessDataHandler.PwmConfig_repetMax)
	   	{
	   	  if(OldValue!=(PwmProcessDataHandler.repetCount%10))
	   	  	{
	   	  	  OldValue=PwmProcessDataHandler.repetCount%10;
	   	  	  if(PwmProcessDataHandler.PwmPulse<Pulse_Max_Value)
	   	  	  	{
			  	  PwmProcessDataHandler.PwmPulse++;
	   	  	  	}
	   	  	}
	   	}
		DirPNAlter_RL_Invoke[MassageHandler.ElectrSliceTyp][DirPNAlterMoveCount](PwmProcessDataHandler.PwmPulse);
		if(++DirPNAlterMoveCount>=DirPNAlter_Move_Max)
		{
		    DirPNAlterMoveCount=0;
		}
	   	break;
		
	   case DirPNAlterL:
	   	DirPNAlter_L_invoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
		
       case DirPNAlterR:
	   	DirPNAlter_R_invoke[MassageHandler.ElectrSliceTyp](PwmProcessDataHandler.PwmPulse);
	   	break;
		
	   case Diralternate:
	   	DiralternateInvoke[MassageHandler.ElectrSliceTyp][alternateDir](PwmProcessDataHandler.PwmPulse);
		Modify2Data[alternateDir](&alternateDir);
	   	break;
   	}

   if(PwmDirOld!=PwmProcessDataHandler.PwmOutDir)
   	{
   	   PwmDirOld=PwmProcessDataHandler.PwmOutDir;
	   TimestampUpdateFreq(PwmProcessDataHandler.TimeArrValue);
   	}
   
}

static void Massage3DModelPwmCHandler(void)
{
     _Massage3DModelType Pwm3DModeOld;
	 static u16 OldValue=0;
	 _PwmPulse3Ddata *GetpwmPulseArray;
	 static u8 L_R_Dir=0;
    GetpwmPulseArray=KnockMode3DMassage[MassageHandler.MassageMode-Massage3DAcupuncture].pwmPulseArray;
   if(--PwmProcessDataHandler.repetCount==0)
	 {
	   	   PwmProcessDataHandler.PwmArrIndex++;
		   if(PwmProcessDataHandler.PwmArrIndex>=PwmProcessDataHandler.PwmConfig_IndexMax)
			{
			    PwmProcessDataHandler.PwmArrIndex=0;
			}
		    PwmProcessDataHandler.Pwm3DDir=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->Mode3Dgroup;
			PwmProcessDataHandler.repetCount=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->repetCount;
			PwmProcessDataHandler.TimeArrValue=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmInterval;
			PwmProcessDataHandler.PwmPulse=(GetpwmPulseArray+PwmProcessDataHandler.PwmArrIndex)->PwmPulseOut->PwmPulse;
			PwmProcessDataHandler.PwmConfig_repetMax=PwmProcessDataHandler.repetCount;
			
	  }
	 if((PwmProcessDataHandler.repetCount+10)<PwmProcessDataHandler.PwmConfig_repetMax)
	   	{
	   	  if(OldValue!=(PwmProcessDataHandler.repetCount%10))
	   	  	{
	   	  	  OldValue=PwmProcessDataHandler.repetCount%10;
	   	  	  if(PwmProcessDataHandler.PwmPulse<Pulse_Max_Value)
	   	  	  	{
			  	  PwmProcessDataHandler.PwmPulse++;
	   	  	  	}
	   	  	}
	   	}
     Dir3DModeMassage_Invoke[PwmProcessDataHandler.Pwm3DDir](PwmProcessDataHandler.PwmPulse,&L_R_Dir);
	if(Pwm3DModeOld!=PwmProcessDataHandler.Pwm3DDir)
   	{
   	   Pwm3DModeOld=PwmProcessDataHandler.Pwm3DDir;
	   TimestampUpdateFreq(PwmProcessDataHandler.TimeArrValue);
   	}
}


static void ModifyOne(u8*datap)
{ 
   *datap=1;
}

static void ModifyTwo(u8*datap)
{
   *datap=0;
}


static void _DirAB_And_CD_IDLE(u32 pulse,u8* L_R)
{
  return ;
}
static void _DirAB_And_CD_DisCharge(u32 pulse,u8* L_R)
{
  Ems_AB_And_CD_Discharge(pulse);
}

static void _DirA_T_B_And_CD_No(u32 pulse,u8* L_R)
{
   if((*L_R)==0)
   	{
       Ems_A_To_Ems_B_FS_P(pulse);
   	}
   else
   	{
   	   Ems_A_To_Ems_B_FS_N(pulse);
   	}
}
static void _DirA_T_B_And_C_T_D(u32 pulse,u8* L_R)
{
   
    EmsA_T_B_And_C_T_D(pulse);
   	
}
static void _DirA_T_B_And_D_T_C(u32 pulse,u8* L_R)
{
     EmsA_T_B_And_D_T_C(pulse);
}
static void _DirA_T_B_And_CDAuto_PN(u32 pulse,u8* L_R)
{
    EmsA_T_B_And_CDAuto_PN(pulse,L_R);
}
  
static void _DirA_T_C_And_BD_No(u32 pulse,u8* L_R)
{
    EmsA_T_C_And_BD_No_PN(pulse,L_R);
}
static void _DirA_T_C_And_B_T_D(u32 pulse,u8* L_R)
{
    EmsA_T_C_And_B_T_D(pulse);
}
static void _DirA_T_C_And_D_T_B(u32 pulse,u8* L_R)
{
    EmsA_T_C_And_D_T_B(pulse);
}
static void _DirA_T_C_And_BDAuto_PN(u32 pulse,u8* L_R)
{
    EmsA_T_C_And_BDAuto_PN(pulse,L_R);
}

static void _DirA_T_D_And_BC_No(u32 pulse,u8* L_R)
{
   EmsA_T_D_And_BC_No_PN(pulse,L_R);
}
static void _DirA_T_D_And_B_T_C(u32 pulse,u8* L_R)
{
    EmsA_T_D_And_B_T_C(pulse);
}
static void _DirA_T_D_And_C_T_B(u32 pulse,u8* L_R)
{
    EmsA_T_D_And_C_T_B(pulse);
}
static void _DirA_T_D_And_BCAuto_PN(u32 pulse,u8* L_R)
{
    EmsA_T_D_And_BCAuto_PN(pulse,L_R);
}

static void _DirB_T_A_And_CD_No(u32 pulse,u8* L_R)
{
    Ems_A_To_Ems_B_FS_N(pulse);
}
static void _DirB_T_A_And_C_T_D(u32 pulse,u8* L_R)
{
    EmsB_T_A_And_C_T_D(pulse);
}
static void _DirB_T_A_And_D_T_C(u32 pulse,u8* L_R)
{
    EmsB_T_A_And_D_T_C(pulse);
}
static void _DirB_T_A_And_CDAuto_PN(u32 pulse,u8* L_R)
{
    EmsB_T_A_And_CDAuto_PN(pulse,L_R);
}

static void _DirB_T_C_And_AD_No(u32 pulse,u8* L_R)
{
   EmsB_T_C_And_AD_No_PN(pulse,L_R);
}
static void _DirB_T_C_And_A_T_D(u32 pulse,u8* L_R)
{
   EmsB_T_C_And_A_T_D(pulse);
}
static void _DirB_T_C_And_D_T_A(u32 pulse,u8* L_R)
{
   EmsB_T_C_And_D_T_A(pulse);
}
static void _DirB_T_C_And_ADAuto_PN(u32 pulse,u8* L_R)
{
  EmsB_T_C_And_ADAuto_PN(pulse,L_R);
}

static void _DirB_T_D_And_AC_No(u32 pulse,u8* L_R)
{
  EmsB_T_D_And_AC_No_PN(pulse,L_R);
}
static void _DirB_T_D_And_A_T_C(u32 pulse,u8* L_R)
{
  EmsB_T_D_And_A_T_C(pulse);
}
static void _DirB_T_D_And_C_T_A(u32 pulse,u8* L_R)
{
  EmsB_T_D_And_C_T_A(pulse);
}
static void _DirB_T_D_And_ACAuto_PN(u32 pulse,u8* L_R)
{
   EmsB_T_D_And_ACAuto_PN(pulse,L_R);
}

static void _DirC_T_A_And_BD_No(u32 pulse,u8* L_R)
{
   EmsC_T_A_And_BD_No(pulse);
}
static void _DirC_T_A_And_B_T_D(u32 pulse,u8* L_R)
{
  EmsC_T_A_And_B_T_D(pulse); 
}
static void _DirC_T_A_And_D_T_B(u32 pulse,u8* L_R)
{
   EmsC_T_A_And_D_T_B(pulse);
}
static void _DirC_T_A_And_BDAuto_PN(u32 pulse,u8* L_R)
{
  EmsC_T_A_And_BDAuto_PN(pulse,L_R);
}
static void _DirC_T_B_And_AD_No(u32 pulse,u8* L_R)
{
   EmsC_T_B_And_AD_No(pulse);
}
static void _DirC_T_B_And_A_T_D(u32 pulse,u8* L_R)
{
  EmsC_T_B_And_A_T_D(pulse);
}
static void _DirC_T_B_And_D_T_A(u32 pulse,u8* L_R)
{
   EmsC_T_B_And_D_T_A(pulse);
}
static void _DirC_T_B_And_ADAuto_PN(u32 pulse,u8* L_R)
{
   EmsC_T_B_And_ADAuto_PN(pulse,L_R);
}

static void _DirC_T_D_And_AB_No(u32 pulse,u8* L_R)
{
   EmsC_T_D_And_AB_No(pulse);
}
static void _DirC_T_D_And_A_T_B(u32 pulse,u8* L_R)
{
   EmsC_T_D_And_A_T_B(pulse);
}
static void _DirC_T_D_And_B_T_A(u32 pulse,u8* L_R)
{
   EmsC_T_D_And_B_T_A(pulse);
}
static void _DirC_T_D_And_ABAuto_PN(u32 pulse,u8* L_R)
{
   EmsC_T_D_And_ABAuto_PN(pulse,L_R);
}

static void _DirD_T_A_And_CB_No(u32 pulse,u8* L_R)
{
   EmsD_T_A_And_BC_No_PN(pulse,L_R);
}
static void _DirD_T_A_And_C_T_B(u32 pulse,u8* L_R)
{
   EmsD_T_A_And_C_T_B(pulse);
}
static void _DirD_T_A_And_B_T_C(u32 pulse,u8* L_R)
{
  EmsD_T_A_And_B_T_C(pulse);
}
static void _DirD_T_A_And_BC_AutO_PN(u32 pulse,u8* L_R)
{
  EmsD_T_A_And_BC_AutO_PN(pulse,L_R);
}

/*

*/


static void _DirA_T_B_And_CD_No_PN(u32 pulse,u8* L_R)
{
  Ems_A_T_B_And_CD_No_PN(pulse,L_R);
}
static void _DirA_T_C_And_BD_No_PN(u32 pulse,u8* L_R)
{
   EmsA_T_C_And_BD_No_PN(pulse,L_R);
}
static void _DirA_T_D_And_BC_No_PN(u32 pulse,u8* L_R)
{
   EmsA_T_D_And_BC_No_PN(pulse,L_R);
}
static void _DirB_T_A_And_CD_No_PN(u32 pulse,u8* L_R)
{
   EmsB_T_A_And_CD_No_PN(pulse,L_R);
}
static void _DirB_T_C_And_AD_No_PN(u32 pulse,u8* L_R)
{
    EmsB_T_C_And_AD_No_PN(pulse,L_R);
}
static void _DirB_T_D_And_AC_No_PN(u32 pulse,u8* L_R)
{
  EmsB_T_D_And_AC_No_PN(pulse,L_R);
}
static void _DirC_T_A_And_BD_No_PN(u32 pulse,u8* L_R)
{
  EmsC_T_A_And_BD_No_PN(pulse,L_R);
}
static void _DirC_T_B_And_AD_No_PN(u32 pulse,u8* L_R)
{
   EmsC_T_B_And_AD_No_PN(pulse,L_R);
}
static void _DirC_T_D_And_AB_No_PN(u32 pulse,u8* L_R)
{
  EmsC_T_D_And_AB_No_PN(pulse,L_R);
}
static void _DirD_T_A_And_BC_No_PN(u32 pulse,u8* L_R)
{
    EmsD_T_A_And_BC_No_PN(pulse,L_R);
}
static void _DirD_T_B_And_AC_No_PN(u32 pulse, u8* L_R)
{
  EmsD_T_B_And_AC_No_PN(pulse,L_R);
}
static void _DirD_T_C_And_AB_No_PN(u32 pulse,u8* L_R)
{
   EmsD_T_C_And_AB_No_PN(pulse,L_R);
}


/*

*/

static void _DirABAuto_And_CDAuto_PN(u32 pulse,u8* L_R)
{
   EmsABAuto_And_CDAuto_PN(pulse,L_R);
}
static void _DirACAutO_And_BDAut0_PN(u32 pulse,u8* L_R)
{
   EmsACAutO_And_BDAuto_PN(pulse,L_R);
}
static void _DirADAuto_And_BCAuto_PN(u32 pulse,u8* L_R)
{
    EmsADAuto_And_BCAuto_PN(pulse,L_R);
}

static void _DirABC_T_D_PN(u32 pulse,u8*L_R)
{
  EmsABC_T_D_PN(pulse,L_R);
}
static void _DirABD_T_C_PN(u32 pulse,u8*L_R)
{
  EmsABD_T_C_PN(pulse,L_R);
}
static void _DirACD_T_B_PN(u32 pulse,u8*L_R)
{
   EmsACD_T_B_PN(pulse,L_R);
}
static void _DirCBD_T_A_PN(u32 pulse,u8*L_R)
{
   EmsBCD_T_A_PN(pulse,L_R);
}




