#include "Gpio.h"
#include "TypedefDef.h"
#include "EMS_Port.h"

#define EMS_A_U_Port   GpioPortB
#define EMS_A_U_Pin    GpioPin3
#define EMS_A_D_Port   GpioPortA
#define EMS_A_D_Pin    GpioPin15


#define EMS_B_U_Port   GpioPortB
#define EMS_B_U_Pin    GpioPin5
#define EMS_B_D_Port   GpioPortB
#define EMS_B_D_Pin    GpioPin4


#define EMS_C_U_Port   GpioPortB
#define EMS_C_U_Pin    GpioPin7
#define EMS_C_D_Port   GpioPortB
#define EMS_C_D_Pin    GpioPin6


#define EMS_D_U_Port   GpioPortC
#define EMS_D_U_Pin    GpioPin14
#define EMS_D_D_Port   GpioPortC
#define EMS_D_D_Pin    GpioPin15


#define EMS_A_U_Out_SetIO  Gpio_SetIO(EMS_A_U_Port,EMS_A_U_Pin)
#define EMS_A_U_Out_ClrIO  Gpio_ClrIO(EMS_A_U_Port,EMS_A_U_Pin)


#define EMS_A_D_Out_SetIO  Gpio_SetIO(EMS_A_D_Port,EMS_A_D_Pin)
#define EMS_A_D_Out_ClrIO  Gpio_ClrIO(EMS_A_D_Port,EMS_A_D_Pin)


#define EMS_B_U_Out_SetIO  Gpio_SetIO(EMS_B_U_Port,EMS_B_U_Pin)
#define EMS_B_U_Out_ClrIO  Gpio_ClrIO(EMS_B_U_Port,EMS_B_U_Pin)


#define EMS_B_D_Out_SetIO  Gpio_SetIO(EMS_B_D_Port,EMS_B_D_Pin)
#define EMS_B_D_Out_ClrIO  Gpio_ClrIO(EMS_B_D_Port,EMS_B_D_Pin)


#define EMS_C_U_Out_SetIO  Gpio_SetIO(EMS_C_U_Port,EMS_C_U_Pin)
#define EMS_C_U_Out_ClrIO  Gpio_ClrIO(EMS_C_U_Port,EMS_C_U_Pin)

#define EMS_C_D_Out_SetIO  Gpio_SetIO(EMS_C_D_Port,EMS_C_D_Pin)
#define EMS_C_D_Out_ClrIO  Gpio_ClrIO(EMS_C_D_Port,EMS_C_D_Pin)

#define EMS_D_U_Out_SetIO  Gpio_SetIO(EMS_D_U_Port,EMS_D_U_Pin)
#define EMS_D_U_Out_ClrIO  Gpio_ClrIO(EMS_D_U_Port,EMS_D_U_Pin)

#define EMS_D_D_Out_SetIO  Gpio_SetIO(EMS_D_D_Port,EMS_D_D_Pin)
#define EMS_D_D_Out_ClrIO  Gpio_ClrIO(EMS_D_D_Port,EMS_D_D_Pin)


#define DeadZonePulse 5
#define DELAy_T  2    //稍微延时降低刺痛，反向脉冲时候
void EMS_Port_Init(void)
{
   stc_gpio_config_t stcGpioCfg;
   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
   DDL_ZERO_STRUCT(stcGpioCfg);
   stcGpioCfg.enDir=GpioDirOut;
   stcGpioCfg.enDrv=GpioDrvH;
   stcGpioCfg.enOD=GpioOdDisable;
   stcGpioCfg.enPuPd=GpioNoPuPd;
   stcGpioCfg.enCtrlMode=GpioAHB;
   Gpio_Init(EMS_A_U_Port,EMS_A_U_Pin,&stcGpioCfg);
   Gpio_Init(EMS_A_D_Port,EMS_A_D_Pin,&stcGpioCfg);
   Gpio_Init(EMS_B_U_Port,EMS_B_U_Pin,&stcGpioCfg);
   Gpio_Init(EMS_B_D_Port,EMS_B_D_Pin,&stcGpioCfg);
   Gpio_Init(EMS_C_U_Port,EMS_C_U_Pin,&stcGpioCfg);
   Gpio_Init(EMS_C_D_Port,EMS_C_D_Pin,&stcGpioCfg);
   Gpio_Init(EMS_D_U_Port,EMS_D_U_Pin,&stcGpioCfg);
   Gpio_Init(EMS_D_D_Port,EMS_D_D_Pin,&stcGpioCfg);

   EMS_A_U_Out_ClrIO;
   EMS_A_D_Out_ClrIO;
   EMS_B_U_Out_ClrIO;
   EMS_B_D_Out_ClrIO;
   EMS_C_U_Out_ClrIO;
   EMS_C_D_Out_ClrIO;
   EMS_D_U_Out_ClrIO;
   EMS_D_D_Out_ClrIO;

   
}

///  no extern  Of electrodes
void Ems_A_To_Ems_B_PNAlter_P(u32 pulse)  ////   A_u->B_d   B_u->A_d  
{
     EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;

     delay1us(DeadZonePulse);

	 
	 EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
}

void Ems_A_To_Ems_B_PNAlter_N(u32 pulse)  ///  B_u->A_d  A_u->B_d
{
     EMS_B_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;

	 delay1us(DeadZonePulse);

	 EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}

void Ems_A_To_Ems_B_Single_P(u32 pulse)  //// A_u->B_d  
{
     EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}


void Ems_A_To_Ems_B_Single_N(u32 pulse) ///  B_u->A_d
{
     EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
}

void Ems_A_To_Ems_B_Double(u32 pulse)  ///  
{
     EMS_A_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}

////  When extended to large electrode plates

void Ems_C_To_Ems_D_PNAlter_P(u32 pulse) ///  C_u->D_d   C_d->D_u
{  
     EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;

	 delay1us(DeadZonePulse);

	 EMS_D_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_D_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}

void Ems_C_To_Ems_D_PNAlter_N(u32 pulse) ///  C_d->D_u   C_u->D-d
{
     EMS_C_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;

	 delay1us(DeadZonePulse);

	 EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}

void Ems_C_To_Ems_D_Single_P(u32 pulse) ///  C_u->D_d
{
     EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}

void Ems_C_To_Ems_D_Single_N(u32 pulse) ///  C_d->D_u
{
     EMS_C_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
}

void Ems_C_To_Ems_D_Double(u32 pulse)
{
     EMS_C_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}


//The electrode was extended to 4 pieces
/*
  A-B  C-D第一组
  
*/


void Ems_A_To_Ems_B_PNAlter_Four_P(u32 pulse) /// A_u->B_d   A_D->B_u
{
     EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;

	 delay1us(DeadZonePulse);

	 EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
}

void Ems_A_To_Ems_B_PNAlter_Four_N(u32 pulse) /// A_d->B_u   A_u->B_d
{
      EMS_A_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
}


void Ems_C_To_Ems_D_PNAlter_Four_P(u32 pulse) /// C_u->D_d   C_D->D_u
{
      EMS_C_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_C_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_C_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_C_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
}
void Ems_C_To_Ems_D_PNAlter_Four_N(u32 pulse) /// C_d->D_u   C_u->D_d
{
      EMS_C_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_C_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_C_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_C_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
}


/*

    B-C  D-A  第二组
 
*/

void Ems_B_To_Ems_C_PNAlter_Four_P(u32 pulse) /// B_u->C_d   B_d->C_u
{
     EMS_B_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;

	 delay1us(DeadZonePulse);

	 EMS_B_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_B_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
}

void Ems_B_To_Ems_C_PNAlter_Four_N(u32 pulse) /// B_d->C_u   B_u->C_d
{
     EMS_B_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;

	 delay1us(DeadZonePulse);


	 EMS_B_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_B_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}


void Ems_D_To_Ems_A_PNAlter_Four_P(u32 pulse) /// D_u->A_d   D_d->A_u
{
     EMS_D_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_D_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;

	 delay1us(DeadZonePulse);

	 EMS_D_D_Out_SetIO;
	 EMS_A_U_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_D_D_Out_ClrIO;
	 EMS_A_U_Out_ClrIO;
}

void Ems_D_To_Ems_A_PNAlter_Four_N(u32 pulse) /// D_d->A_u   D_u->A_d
{
     EMS_D_D_Out_SetIO;
	 EMS_A_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_D_D_Out_ClrIO;
	 EMS_A_U_Out_ClrIO;

	 delay1us(DeadZonePulse);

	 EMS_D_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse+DELAy_T);
	 EMS_D_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
}


/*

    A-C    B-D   斜对角  
    
*/

void Ems_A_To_Ems_C_PNAlter_Four_P(u32 pulse) /// A_u->C_d   A_d->C_u
{
    EMS_A_U_Out_SetIO;
	EMS_C_D_Out_SetIO;
	delay1us(pulse);
	EMS_A_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;

	delay1us(DeadZonePulse);

    EMS_A_D_Out_SetIO;
	EMS_C_U_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_A_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	
}

void Ems_A_To_Ems_C_PNAlter_Four_N(u32 pulse) /// A_d->C_u   A_u->C_d
{
    EMS_A_D_Out_SetIO;
	EMS_C_U_Out_SetIO;
	delay1us(pulse);
	EMS_A_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_A_U_Out_SetIO;
	EMS_C_D_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_A_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
}

void Ems_B_To_Ems_D_PNAlter_Four_P(u32 pulse) /// B_u->D_d   B_d->D_u
{
    EMS_B_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	delay1us(pulse);
	EMS_B_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_B_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_B_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
}

void Ems_B_To_Ems_D_PNAlter_Four_N(u32 pulse) /// B_d->D_u   B_u->D_d
{
    EMS_B_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	delay1us(pulse);
	EMS_B_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_B_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_B_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
}


void Ems_A_To_Ems_B_FS_P(u32 pulse) ///  A_u->B_d
{
     EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}

void Ems_A_To_Ems_B_FS_N(u32 pulse) ///  A_d->B_u
{
     EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
}

void Ems_C_To_Ems_D_FS_P(u32 pulse) /// C_u->D_d
{
     EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}


void Ems_C_To_Ems_D_FS_N(u32 pulse) /// C_u->D_d
{
     EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}




void Ems_A_To_Ems_C_FS_P(u32 pulse) ///A_u->C_d
{
     EMS_A_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}

void Ems_A_To_Ems_C_FS_N(u32 pulse)  /// A_d->C_u
{
     EMS_A_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
}

void Ems_B_To_Ems_D_FS_P(u32 pulse)  /// B_u->D_d
{
     EMS_B_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}

void Ems_B_To_Ems_D_FS_N(u32 pulse) /// B_d->D_u
{
     EMS_B_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
}



void Ems_B_To_Ems_C_FS_P(u32 pulse)  /// B_u->C_d
{
     EMS_B_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}

void Ems_B_To_Ems_C_FS_N(u32 pulse)  ///  B_d->C_u
{
     EMS_B_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
}

void Ems_A_To_Ems_D_FS_P(u32 pulse)   //A_u->D_d
{
     EMS_A_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}

void Ems_A_To_Ems_D_FS_N(u32 pulse)  /// A_d->D_u
{
     EMS_A_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
}

void Ems_AB_And_CD_Four(u32 pulse)
{
     EMS_A_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}
void Ems_AToB_Ems_CToD_FS_P(u32 pulse) /// A_u->B_d    C_u->D_d
{
     EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;

	 EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);

	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;

	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
	 
}
void Ems_AToB_Ems_CToD_FS_N(u32 pulse) /// A_d->B_U    C_d->D_u
{
     EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;

	 EMS_C_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 
	 delay1us(pulse);

	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;

	 EMS_C_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 
}


void Ems_AToB_And_Ems_CToD_PNAlter_P(u32 pulse) /// A_u->B_d   C_u->D_d   <-> A_d->B_u  C_d->D_u
{
    EMS_A_U_Out_SetIO;
	EMS_B_D_Out_SetIO;

	EMS_C_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	delay1us(pulse);
	EMS_A_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_A_D_Out_SetIO;
	EMS_B_U_Out_SetIO;

	EMS_C_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	delay1us(pulse+DELAy_T);

	EMS_A_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
}

void Ems_AToB_And_Ems_CToD_PNAlter_N(u32 pulse) /// A_d->B_u   C_d->D_u   <-> A_u->B_d  C_u->D_d
{
    EMS_A_D_Out_SetIO;
	EMS_B_U_Out_SetIO;

	EMS_C_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	delay1us(pulse);
	EMS_A_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_A_U_Out_SetIO;
	EMS_B_D_Out_SetIO;
	EMS_C_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_A_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
}

void Ems_AToC_And_Ems_BToD_PNAlter_P(u32 pulse) /// A_u->C_d   B_u->D_d   <-> A_d->C_u  B_d->D_u
{
    EMS_A_U_Out_SetIO;
	EMS_C_D_Out_SetIO;

	EMS_B_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	delay1us(pulse);
	EMS_A_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;

	delay1us(DeadZonePulse);


	EMS_A_D_Out_SetIO;
	EMS_C_U_Out_SetIO;

	EMS_B_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_A_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
	
}

void Ems_AToC_And_Ems_BToD_PNAlter_N(u32 pulse) /// A_d->C_u   B_d->D_u   <-> A_u->C_d  B_u->D_d
{
	EMS_A_D_Out_SetIO;
	EMS_C_U_Out_SetIO;

	EMS_B_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	delay1us(pulse);
    EMS_A_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_A_U_Out_SetIO;
	EMS_C_D_Out_SetIO;
	EMS_B_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_A_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
	
}

void Ems_AToD_And_Ems_BToC_PNAlter_P(u32 pulse) /// A_u->D_d   B_u->C_d   <-> A_d->D_u  B_d->C_u
{
    EMS_A_U_Out_SetIO;
	EMS_D_D_Out_SetIO;

	EMS_B_U_Out_SetIO;
	EMS_C_D_Out_SetIO;
	delay1us(pulse);
	EMS_A_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_A_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	EMS_B_D_Out_SetIO;
	EMS_C_U_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_A_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
}

void Ems_AToD_And_Ems_BToC_PNAlter_N(u32 pulse) /// A_d->D_u   B_d->C_u   <-> A_u->D_d  B_u->C_d
{
    EMS_A_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	EMS_B_D_Out_SetIO;
	EMS_C_U_Out_SetIO;
	delay1us(pulse);
	EMS_A_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;

	delay1us(DeadZonePulse);

	EMS_A_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	EMS_B_U_Out_SetIO;
	EMS_C_D_Out_SetIO;
	delay1us(pulse+DELAy_T);
	EMS_A_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
}

void Ems_AB_And_CD_Idle(u32 pulse)
{
    EMS_A_U_Out_ClrIO;
	EMS_A_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
}

void Ems_AB_And_CD_Discharge(u32 pulse)
{
    EMS_A_U_Out_SetIO;
	EMS_A_D_Out_SetIO;
	EMS_B_U_Out_SetIO;
	EMS_B_D_Out_SetIO;
	EMS_C_U_Out_SetIO;
	EMS_C_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
    delay1us(pulse);
    EMS_A_U_Out_ClrIO;
	EMS_A_D_Out_ClrIO;
	EMS_B_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	EMS_C_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
}

void EmsA_T_B_And_C_T_D(u32 pulse)
{
    EMS_A_U_Out_SetIO;
	EMS_B_D_Out_SetIO;
	EMS_C_U_Out_SetIO;
	EMS_D_D_Out_SetIO;
	delay1us(pulse);
	EMS_A_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
	EMS_C_U_Out_ClrIO;
	EMS_D_D_Out_ClrIO;
}
void EmsA_T_B_And_D_T_C(u32 pulse)
{
     EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}
void EmsA_T_B_And_CDAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
       (*(L_R))=1;
       EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;

	   EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

       EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   
     }
	 else if(1==(*L_R))
	 {
	   (*(L_R))=2;
	   EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;

	   EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

       EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO; 
	 }
	 else if(2==(*L_R))
	 {
	   (*(L_R))=3;
	   EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;

	   EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

       EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO; 
	 }
	 else 
	 {
	   (*(L_R))=0;
	   EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;

	   EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

       EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	 }
}
  
void EmsA_T_C_And_B_T_D(u32 pulse)
{
     EMS_A_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}
void EmsA_T_C_And_D_T_B(u32 pulse)
{
     EMS_A_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}
void EmsA_T_C_And_BDAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
       EMS_A_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;

	   EMS_B_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	 	(*L_R)=2;
       EMS_A_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;

	   EMS_B_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO; 
	 }
	 else if(2==(*L_R))
	 {
	   (*L_R)=3;
       EMS_A_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;

	   EMS_B_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	 }
	 else
	 {
	   (*L_R)=0;
       EMS_A_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;

	   EMS_B_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	 }
}

void EmsA_T_D_And_B_T_C(u32 pulse)
{
     EMS_A_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}
void EmsA_T_D_And_C_T_B(u32 pulse)
{
     EMS_A_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_A_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}
void EmsA_T_D_And_BCAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;

	   
	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	   (*L_R)=2;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;  
	 }
	 else if(2==(*L_R))
	 {
	    (*L_R)=3;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO; 
	 }
	 else
	 {
	   (*L_R)=0;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	 }
}

void EmsB_T_A_And_C_T_D(u32 pulse)
{
     EMS_B_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}
void EmsB_T_A_And_D_T_C(u32 pulse)
{
     EMS_B_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}
void EmsB_T_A_And_CDAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
      {
        (*L_R)=1;
		EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_C_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_C_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_C_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_C_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	    (*L_R)=2;
		EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_C_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_C_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_C_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_C_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	 {
	    (*L_R)=3;
		EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_C_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_C_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_C_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_C_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;
	 }
	 else 
	 {
	 	(*L_R)=0;
		EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_C_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_C_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_C_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_C_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO; 
	 }
}

void EmsB_T_C_And_A_T_D(u32 pulse)
{  
     EMS_B_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 EMS_A_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
	 EMS_A_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}
void EmsB_T_C_And_D_T_A(u32 pulse)
{
     EMS_B_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
}
void EmsB_T_C_And_ADAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
       EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	   (*L_R)=1;
       EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	 }
	 else if(2==(*L_R))
	 {
	   (*L_R)=3;
       EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	 }
	 else
	 {
	   (*L_R)=1;
       EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	 }
	 
}

void EmsB_T_D_And_A_T_C(u32 pulse)
{
     EMS_B_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 EMS_A_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
	 EMS_A_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}
void EmsB_T_D_And_C_T_A(u32 pulse)
{
     EMS_B_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_B_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
}
void EmsB_T_D_And_ACAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
	   EMS_B_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	 	    (*L_R)=2;
	   EMS_B_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	 }
	 else
	 {
	    (*L_R)=3;
	   EMS_B_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	 }
}

void EmsC_T_A_And_B_T_D(u32 pulse)
{
     EMS_C_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}
void EmsC_T_A_And_D_T_B(u32 pulse)
{
    EMS_C_U_Out_SetIO;
	EMS_A_D_Out_SetIO;
	EMS_D_U_Out_SetIO;
	EMS_B_D_Out_SetIO;
	delay1us(pulse);
	EMS_C_U_Out_ClrIO;
	EMS_A_D_Out_ClrIO;
	EMS_D_U_Out_ClrIO;
	EMS_B_D_Out_ClrIO;
}
void EmsC_T_A_And_BDAuto_PN(u32 pulse,u8* L_R)
{
    if(0==(*L_R))
    {
        (*L_R)=1;
	    EMS_C_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_B_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse);
		EMS_C_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_B_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_B_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;
    }
	else if(1==(*L_R))
	{
	    (*L_R)=2;
	    EMS_C_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_B_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse);
		EMS_C_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_B_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;
		delay1us(DeadZonePulse);

		EMS_B_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;
	}
	else if(2==(*L_R))
	{
	   (*L_R)=3;
	    EMS_C_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_B_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse);
		EMS_C_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_B_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;
		delay1us(DeadZonePulse);

		EMS_B_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;
	}
	else
	{
	   (*L_R)=0;
	    EMS_C_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		EMS_B_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse);
		EMS_C_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
		EMS_B_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;
		delay1us(DeadZonePulse);

		EMS_B_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;
	}
}
void EmsC_T_B_And_A_T_D(u32 pulse)
{
     EMS_C_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 EMS_A_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
	 EMS_A_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
}
void EmsC_T_B_And_D_T_A(u32 pulse)
{
     EMS_C_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 EMS_D_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
	 EMS_D_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
}
void EmsC_T_B_And_ADAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
	   EMS_C_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	   (*L_R)=2;
	   EMS_C_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	 }
	 else if(2==(*L_R))
	 {
	   (*L_R)=3;
	   EMS_C_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;  
	 }
	 else
	 {
	   (*L_R)=0;
	   EMS_C_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO; 
	 }
}

void EmsC_T_D_And_A_T_B(u32 pulse)
{
     EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 EMS_A_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
	 EMS_A_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}
 void EmsC_T_D_And_B_T_A(u32 pulse)
 {
     EMS_C_U_Out_SetIO;
	 EMS_D_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_D_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
 }
void EmsC_T_D_And_ABAuto_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
       EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;

	   EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	   (*L_R)=2;
       EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;

	   EMS_A_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	 }
	 else if(2==(*L_R))
	 {
	   (*L_R)=1;
       EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;

	   EMS_A_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	 }
	 else
	 {
	    (*L_R)=0;
       EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;

	   EMS_A_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	 }
}

void EmsD_T_A_And_C_T_B(u32 pulse)
{
     EMS_D_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 EMS_C_U_Out_SetIO;
	 EMS_B_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_D_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
	 EMS_C_U_Out_ClrIO;
	 EMS_B_D_Out_ClrIO;
}
void EmsD_T_A_And_B_T_C(u32 pulse)
{
     EMS_D_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 EMS_B_U_Out_SetIO;
	 EMS_C_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_D_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
	 EMS_B_U_Out_ClrIO;
	 EMS_C_D_Out_ClrIO;
}
void EmsD_T_A_And_BC_AutO_PN(u32 pulse,u8* L_R)
{
    if(0==(*L_R))
    {
       (*L_R)=1;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;

	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
    }
	else if(1==(*L_R))
	{
	    (*L_R)=2;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;

	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   
	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	}
	else if(2==(*L_R))
	{
	   (*L_R)=3;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;

	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	}
	else
	{
	   (*L_R)=0;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;

	   EMS_B_U_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	}
}
void Ems_A_T_B_And_CD_No_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
     {
        (*L_R)=1;
		 EMS_A_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 
		 EMS_A_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	    (*L_R)=2;
		 EMS_A_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;

		 delay1us(DeadZonePulse);
		 
		 EMS_A_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;
	 }
	 else if(2==(*L_R))
	 {
	     (*L_R)=3;
		 EMS_A_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 
		 EMS_A_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;
	 }
	 else
	 {
	     EMS_A_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 
		 EMS_A_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;
	 }
}
void EmsA_T_C_And_BD_No_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
      {
         (*L_R)=1;
         EMS_A_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;
      }
	 else if((*L_R)==1)
	 {
	     (*L_R)=2;
         EMS_A_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;
	 }
	 else if(*L_R==2)
	 {
	     (*L_R)=2;
         EMS_A_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;
	 }
	 else
	 {
	    (*L_R)=0;
         EMS_A_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;
	 }
}
void EmsA_T_D_And_BC_No_PN(u32 pulse,u8* L_R)
{
     if((*L_R)==0)
       {
     	 (*L_R)=1;
		 EMS_A_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;
       }
	 else if(1==(*L_R))
	   {
	       (*L_R)=2;
		 EMS_A_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;
	   }
	 else if(2==(*L_R))
	  {
	 	 (*L_R)=3;
		 EMS_A_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;
	  }
	 else 
	   {
	     (*L_R)=0;
		 EMS_A_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_A_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_A_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_A_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;
	   }
}
void EmsB_T_A_And_CD_No_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
      {
        (*L_R)=1;
        EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_B_D_Out_SetIO;
		EMS_A_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_D_Out_ClrIO;
		EMS_A_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	    (*L_R)=2;
        EMS_B_D_Out_SetIO;
		EMS_A_U_Out_SetIO;
		delay1us(pulse);
		EMS_B_D_Out_ClrIO;
		EMS_A_U_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	    (*L_R)=3;
        EMS_B_D_Out_SetIO;
		EMS_A_U_Out_SetIO;
		delay1us(pulse);
		EMS_B_D_Out_ClrIO;
		EMS_A_U_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;
	  }
	 else
	  {
	    (*L_R)=0;
        EMS_B_U_Out_SetIO;
		EMS_A_D_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_A_D_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_B_D_Out_SetIO;
		EMS_A_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_D_Out_ClrIO;
		EMS_A_U_Out_ClrIO; 
	  }
}
void EmsB_T_C_And_AD_No_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
      {
         (*L_R)=1;
		 EMS_B_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_B_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_B_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_B_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	     (*L_R)=2;
		 EMS_B_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_B_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_B_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_B_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	     (*L_R)=3;
		 EMS_B_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_B_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_B_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_B_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;
	  }
	 else
	  {
	     (*L_R)=0;
		 EMS_B_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_B_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_B_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_B_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;
	  }
}
void EmsB_T_D_And_AC_No_PN(u32 pulse,u8* L_R)
{
    if(0==(*L_R))
      {
        (*L_R)=1;
        EMS_B_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_B_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	     (*L_R)=1; 
		 EMS_B_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_B_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_B_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_B_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	     (*L_R)=1;
		 EMS_B_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_B_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_B_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_B_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;
	  }
	 else
	  {
	     (*L_R)=1;
		 EMS_B_U_Out_SetIO;
		EMS_D_D_Out_SetIO;
		delay1us(pulse);
		EMS_B_U_Out_ClrIO;
		EMS_D_D_Out_ClrIO;

		delay1us(DeadZonePulse);

		EMS_B_D_Out_SetIO;
		EMS_D_U_Out_SetIO;
		delay1us(pulse+DELAy_T);
		EMS_B_D_Out_ClrIO;
		EMS_D_U_Out_ClrIO;
	  }
}
void EmsC_T_A_And_BD_No_PN(u32 pulse,u8* L_R)
{
   if(0==(*L_R))
      {
         (*L_R)=1;
		 EMS_C_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	      (*L_R)=2;
		  EMS_C_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	      (*L_R)=3;
		  EMS_C_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;
	  }
	 else
	  {
	      (*L_R)=0;
		  EMS_C_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;
	  }
}
void EmsC_T_B_And_AD_No_PN(u32 pulse,u8* L_R)
{
 if(0==(*L_R))
      {
         (*L_R)=1;
		 EMS_C_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	      (*L_R)=2;
		  EMS_C_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	      (*L_R)=3;
		  EMS_C_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;
	  }
	 else
	  {
	      (*L_R)=0;
		  EMS_C_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;
	  }
}
void EmsC_T_D_And_AB_No_PN(u32 pulse,u8* L_R)
{
     if(0==(*L_R))
      {
         (*L_R)=1;
		 EMS_C_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	      (*L_R)=2;
		  EMS_C_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	      (*L_R)=3;
		  EMS_C_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;
	  }
	 else
	  {
	      (*L_R)=0;
		  EMS_C_U_Out_SetIO;
		 EMS_D_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_C_U_Out_ClrIO;
		 EMS_D_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_C_D_Out_SetIO;
		 EMS_D_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_C_D_Out_ClrIO;
		 EMS_D_U_Out_ClrIO;
	  }
}
void EmsD_T_A_And_BC_No_PN(u32 pulse,u8*L_R)
{
   if(0==(*L_R))
      {
         (*L_R)=1;
		 EMS_D_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	      (*L_R)=2;
		 EMS_D_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	      (*L_R)=3;
		 EMS_D_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;
	  }
	 else
	  {
	      (*L_R)=0;
		  EMS_D_U_Out_SetIO;
		 EMS_A_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_U_Out_ClrIO;
		 EMS_A_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_D_Out_SetIO;
		 EMS_A_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_D_Out_ClrIO;
		 EMS_A_U_Out_ClrIO;
	  }
}
void EmsD_T_B_And_AC_No_PN(u32 pulse,u8*L_R)
{
  if(0==(*L_R))
      {
         (*L_R)=1;
		 EMS_D_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;
      }
	 else if(1==(*L_R))
	  {
	      (*L_R)=2;

		 EMS_D_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	      (*L_R)=3;
		  EMS_D_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;
	  }
	 else
	  {
	      (*L_R)=0;
		  EMS_D_U_Out_SetIO;
		 EMS_B_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_U_Out_ClrIO;
		 EMS_B_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_D_Out_SetIO;
		 EMS_B_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_D_Out_ClrIO;
		 EMS_B_U_Out_ClrIO;
	  }
}
void EmsD_T_C_And_AB_No_PN(u32 pulse,u8* L_R)
{
   if(0==(*L_R))
      {
         (*L_R)=1;
		 EMS_D_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;
		 
      }
	 else if(1==(*L_R))
	  {
	      (*L_R)=2;
		  EMS_D_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;
	  }
	 else if(2==(*L_R))
	  {
	      (*L_R)=3;
		  EMS_D_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;
	  }
	 else
	  {
	      (*L_R)=0;
		  EMS_D_U_Out_SetIO;
		 EMS_C_D_Out_SetIO;
		 delay1us(pulse);
		 EMS_D_U_Out_ClrIO;
		 EMS_C_D_Out_ClrIO;

		 delay1us(DeadZonePulse);

		 EMS_D_D_Out_SetIO;
		 EMS_C_U_Out_SetIO;
		 delay1us(pulse+DELAy_T);
		 EMS_D_D_Out_ClrIO;
		 EMS_C_U_Out_ClrIO;
	  }
}

void EmsABC_T_D_PN(u32 pulse,u8*L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
       EMS_A_U_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   
     }
	 else if(1==(*L_R))
	 {
	   (*L_R)=2;
	   EMS_A_D_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	 }
	 else if(2==(*L_R))
	 {
      
	   (*L_R)=3; 
	   EMS_A_D_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	 }
	 else
	 {
	   (*L_R)=0;
	   EMS_A_U_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_U_Out_ClrIO; 
	 }
}

void EmsABD_T_C_PN(u32 pulse,u8*L_R)
{
   if(0==(*L_R))
   	{
   	  (*L_R)=1;
	  EMS_A_U_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
   	}
   else if(1==(*L_R))
   	{
   	   (*L_R)=2;
	  EMS_A_D_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
   	}
   else if(2==(*L_R))
   	{
   	   (*L_R)=3;
	  EMS_A_D_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
   	}
   else
   	{
   	   (*L_R)=0;
	  EMS_A_U_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
   	}

}

void EmsACD_T_B_PN(u32 pulse,u8*L_R)
{
    if(0==(*L_R))
    {
       (*L_R)=1;
	   EMS_A_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
    }
	else if(1==(*L_R))
	{
	  (*L_R)=2;
	   EMS_A_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	}
	else if(2==(*L_R))
	{
	   (*L_R)=3;
	   EMS_A_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;
	}
	else
	{
	   (*L_R)=0;
	   EMS_A_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_B_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_A_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_B_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_A_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_B_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_A_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_B_U_Out_ClrIO;
	}
}

void EmsBCD_T_A_PN(u32 pulse,u8*L_R)
{
     if(0==(*L_R))
     {
       (*L_R)=1;
       EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
     }
	 else if(1==(*L_R))
	 {
	   (*L_R)=2;
       EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;  
	 }
	 else if(2==(*L_R))
	 {
	   (*L_R)=3;
       EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;   
	 }
	 else
	 {
	   (*L_R)=0;
       EMS_B_U_Out_SetIO;
	   EMS_C_U_Out_SetIO;
	   EMS_D_U_Out_SetIO;
	   EMS_A_D_Out_SetIO;
	   delay1us(pulse);
	   EMS_B_U_Out_ClrIO;
	   EMS_C_U_Out_ClrIO;
	   EMS_D_U_Out_ClrIO;
	   EMS_A_D_Out_ClrIO;

	   delay1us(DeadZonePulse);

	   EMS_B_D_Out_SetIO;
	   EMS_C_D_Out_SetIO;
	   EMS_D_D_Out_SetIO;
	   EMS_A_U_Out_SetIO;
	   delay1us(pulse+DELAy_T);
	   EMS_B_D_Out_ClrIO;
	   EMS_C_D_Out_ClrIO;
	   EMS_D_D_Out_ClrIO;
	   EMS_A_U_Out_ClrIO;
	 }
}

void EmsC_T_A_And_BD_No(u32 pulse)
{
     EMS_C_U_Out_SetIO;
	 EMS_A_D_Out_SetIO;
	 delay1us(pulse);
	 EMS_C_U_Out_ClrIO;
	 EMS_A_D_Out_ClrIO;
}

void EmsC_T_B_And_AD_No(u32 pulse)
{
   EMS_C_U_Out_SetIO;
   EMS_B_D_Out_SetIO;
   delay1us(pulse);
   EMS_C_U_Out_ClrIO;
   EMS_B_D_Out_ClrIO;
}

void EmsC_T_D_And_AB_No(u32 pulse)
{
   EMS_C_U_Out_SetIO;
   EMS_D_D_Out_SetIO;
   delay1us(pulse);
   EMS_C_U_Out_ClrIO;
   EMS_D_D_Out_ClrIO;
}

void EmsABAuto_And_CDAuto_PN(u32 pulse,u8*L_R)
{
    if(0==(*L_R))
   	{
   	  *L_R=1;
	  EMS_A_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
    }
	else if(1==(*L_R))
	{
	  *L_R=2;
	  EMS_A_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	}
	else if(2==(*L_R))
	{
	   *L_R=3;
	  EMS_A_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	}
	else
	{
	   *L_R=0;
	  EMS_A_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	}
}

void EmsACAutO_And_BDAuto_PN(u32 pulse,u8*L_R)
{
   if(0==(*L_R))
   	{
   	  (*L_R)=1;
	  EMS_A_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
   	}
   else if(1==(*L_R))
   	{
   	  (*L_R)=2;

	  EMS_A_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  
   	}
   else if(2==(*L_R))
   	{
   	  (*L_R)=3;
	  EMS_A_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
   	}
   else
   	{
   	  (*L_R)=0;
	  EMS_A_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
   	}
}

void EmsADAuto_And_BCAuto_PN(u32 pulse,u8*L_R)
{
    if(0==(*L_R))
    {
      (*L_R)=1;
	  EMS_A_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
    }
	else if(1==(*L_R))
	{
	  (*L_R)=2;
	  EMS_A_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO; 
	}
	else if(2==(*L_R))
	{
	   (*L_R)=3;
	  EMS_A_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;
	}
	else
	{
	   (*L_R)=0;
	  EMS_A_U_Out_SetIO;
	  EMS_D_D_Out_SetIO;
	  EMS_B_U_Out_SetIO;
	  EMS_C_D_Out_SetIO;
	  delay1us(pulse);
	  EMS_A_U_Out_ClrIO;
	  EMS_D_D_Out_ClrIO;
	  EMS_B_U_Out_ClrIO;
	  EMS_C_D_Out_ClrIO;

	  delay1us(DeadZonePulse);

	  EMS_A_D_Out_SetIO;
	  EMS_D_U_Out_SetIO;
	  EMS_B_D_Out_SetIO;
	  EMS_C_U_Out_SetIO;
	  delay1us(pulse+DELAy_T);
	  EMS_A_D_Out_ClrIO;
	  EMS_D_U_Out_ClrIO;
	  EMS_B_D_Out_ClrIO;
	  EMS_C_U_Out_ClrIO;
	}
}

