#ifndef __WAVE__HH__
#define __WAVE__HH__
#include "Global.h"

#define TimeFreqDefine 24
#define TimeFreqPSC 256
#define SystemClkFreq 24000000

typedef struct
{
   _PwmPulseData *pwmPulseArray;
   u16 ArrayMax;
}_PwmPulseArray;


typedef struct
{
    _PwmPulse3Ddata *pwmPulseArray;
	u16 ArrayMax;
}_PwmPulse3DArray;



#ifndef _acupunctureMassage
#define _acupunctureMassage

_PwmPulseType AcupunctureeMode_to_83Hz=
{
   (10),
   ((SystemClkFreq)/(TimeFreqPSC*166)),
   450,
};

_PwmPulseType AcupunctureeMode_to_166Hz=
{
   (10),
   ((SystemClkFreq)/(TimeFreqPSC*244)),
   350,
};

_PwmPulseType AcupunctureeMode_to_122Hz=
{
   (10),
   ((SystemClkFreq)/(TimeFreqPSC*192)),
   400,
};


_PwmPulseType AcupunctureMode_toIDLE_2Hz_1S=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*2)),
   1,
};




_PwmPulseData AcupunctureMode[]=
{
   {&AcupunctureeMode_to_83Hz,DirPNAlter},
   {&AcupunctureMode_toIDLE_2Hz_1S,DirIDLE},
   {&AcupunctureeMode_to_122Hz,DirPNAlter},
   {&AcupunctureMode_toIDLE_2Hz_1S,DirIDLE},
   {&AcupunctureeMode_to_166Hz,DirPNAlter},
   {&AcupunctureMode_toIDLE_2Hz_1S,DirIDLE},
   {&AcupunctureeMode_to_83Hz,DirPNAlter},
   {&AcupunctureMode_toIDLE_2Hz_1S,DirIDLE},
   {&AcupunctureeMode_to_122Hz,DirPNAlter},
   {&AcupunctureMode_toIDLE_2Hz_1S,DirIDLE},
};

#endif
#ifndef _malaxationMode
#define _malaxationMode

_PwmPulseType malaxationMode_to_83Hz_1=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   24,
};

_PwmPulseType malaxationMode_toIDLE_8H9z=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*8.9)),
   1,
};

_PwmPulseType malaxationMode_to_83Hz_2=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   72,
};

_PwmPulseType malaxationMode_to_83Hz_3=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   144,
};

_PwmPulseType malaxationMode_to_83Hz_4=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   192,
};



_PwmPulseData MalaxationMode[]=
{
   {&malaxationMode_to_83Hz_1,DirPNAlter},
   {&malaxationMode_toIDLE_8H9z,DirIDLE},
   {&malaxationMode_to_83Hz_1,DirPNAlter},
   {&malaxationMode_toIDLE_8H9z,DirIDLE},
   {&malaxationMode_to_83Hz_2,DirPNAlter},
   {&malaxationMode_toIDLE_8H9z,DirIDLE},
   {&malaxationMode_to_83Hz_3,DirPNAlter},
   {&malaxationMode_toIDLE_8H9z,DirIDLE},
   {&malaxationMode_to_83Hz_4,DirPNAlter},
   {&malaxationMode_toIDLE_8H9z,DirIDLE},
};


#endif
#ifndef _scrapingMode
#define _scrapingMode


_PwmPulseType scrapingMode_to_120Hz_80=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*120)),
   80,
};

_PwmPulseType scrapingMode_to_160Hz_90=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*160)),
   90,
};

_PwmPulseType scrapingMode_to_200Hz_100=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*200)),
   100,
};



_PwmPulseType scrapingMode_toIDLE_8H9z=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*8.9)),
   2,
};

_PwmPulseType scrapingMode_to_240Hz_480=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*240)),
    480,
};

_PwmPulseType scrapingMode_toIDLE_2Hz_1=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*2)),
   1,
};



_PwmPulseData scrapingMode[]=
{
   {&scrapingMode_to_120Hz_80,DirPNAlter},
   {&scrapingMode_toIDLE_8H9z,DirIDLE},
   {&scrapingMode_to_160Hz_90,DirPNAlter},
   {&scrapingMode_toIDLE_8H9z,DirIDLE},
   {&scrapingMode_to_200Hz_100,DirPNAlter},
   {&scrapingMode_toIDLE_8H9z,DirIDLE},
   {&scrapingMode_to_240Hz_480,DirPNAlter},
   {&scrapingMode_toIDLE_2Hz_1,DirIDLE},
};

#endif

#ifndef _KnockMode1_Define
#define _KnockMode1_Define

_PwmPulseType sKMode_to_5Hz_80=
{
   ((50)),
   ((SystemClkFreq)/(TimeFreqPSC*5)),
    30,
};

_PwmPulseType sKMode_to_10Hz_10=
{
   ((50)),
   ((SystemClkFreq)/(TimeFreqPSC*7.5)),
   30,
};

_PwmPulseType sKMode_to_7H5z_8=
{
   ((50)),
   ((SystemClkFreq)/(TimeFreqPSC*10)),
   50,
};



_PwmPulseType sKMode_toIDLE_8H9z=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*10)),
   5,
};

_PwmPulseType sKMode_toIDLE_2Hz_1=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*2)),
   1,
};


_PwmPulseData KnockMode1Mode[]=
{
  
   {&sKMode_to_5Hz_80,DirPNAlter},
   {&sKMode_toIDLE_8H9z,DirIDLE},
   {&sKMode_to_10Hz_10,DirPNAlter},
   {&sKMode_toIDLE_8H9z,DirIDLE},
   {&sKMode_to_7H5z_8,DirPNAlter},
   {&sKMode_toIDLE_8H9z,DirIDLE},
};
#endif




_PwmPulseArray MassageModeArray[]=
{
   {&AcupunctureMode[0],(sizeof(AcupunctureMode)/sizeof(_PwmPulseData))},
   {&MalaxationMode[0],(sizeof(MalaxationMode)/sizeof(_PwmPulseData))},
   {&scrapingMode[0],(sizeof(scrapingMode)/sizeof(_PwmPulseData))},
   {&KnockMode1Mode[0],(sizeof(KnockMode1Mode)/sizeof(_PwmPulseData))},
};



#ifndef _acupuncture3DMassage
#define _acupuncture3DMassage

_PwmPulseType Acupuncturee3DMode_to_83Hz=
{
  ((25)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   1000,
};
_PwmPulseType Acupuncture3DMode_toIDLE_2Hz_1S=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*2)),
   2,
};




_PwmPulse3Ddata Acupuncture3DMode[]=
{

   {&Acupuncturee3DMode_to_83Hz,DirA_T_B_And_CD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirA_T_C_And_BD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirA_T_D_And_BC_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirB_T_A_And_CD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirB_T_C_And_AD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirB_T_D_And_AC_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirC_T_A_And_BD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirC_T_B_And_AD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirC_T_D_And_AB_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirD_T_A_And_BC_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirD_T_B_And_AC_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirD_T_C_And_AB_No_PN},
   #if 0
   {&Acupuncturee3DMode_to_83Hz,DirA_T_B_And_CD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirB_T_C_And_AD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirC_T_D_And_AB_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirD_T_C_And_AB_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirA_T_C_And_BD_No_PN},   
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirC_T_A_And_BD_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirB_T_D_And_AC_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirD_T_B_And_AC_No_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   #endif

	 #if 0
   {&Acupuncturee3DMode_to_83Hz,DirABAuto_And_CDAuto_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirACAutO_And_BDAut0_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirADAuto_And_BCAuto_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   #endif
   #if 0
   {&Acupuncturee3DMode_to_83Hz,DirABC_T_D_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirABD_T_C_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirACD_T_B_PN},
   {&Acupuncture3DMode_toIDLE_2Hz_1S,DirAB_And_CD_IDLE},
   {&Acupuncturee3DMode_to_83Hz,DirCBD_T_A_PN},
   #endif
};

#endif
#ifndef _3DmalaxationMode
#define _3DmalaxationMode

_PwmPulseType malaxation3DMode_to_83Hz_1=
{
   ((25)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   24,
};

_PwmPulseType malaxation3DMode_toIDLE_8H9z=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*8.9)),
   1,
};

_PwmPulseType malaxation3DMode_to_83Hz_2=
{
   ((25)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   82,
};



_PwmPulse3Ddata Malaxation3DMode[]=
{
   {&malaxation3DMode_to_83Hz_1,DirA_T_B_And_CD_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_1,DirA_T_C_And_BD_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_2,DirA_T_D_And_BC_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   
   {&malaxation3DMode_to_83Hz_1,DirB_T_A_And_CD_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_1,DirB_T_C_And_AD_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_2,DirB_T_D_And_AC_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},

   {&malaxation3DMode_to_83Hz_1,DirC_T_A_And_BD_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_1,DirC_T_B_And_AD_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_2,DirC_T_D_And_AB_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},

   {&malaxation3DMode_to_83Hz_1,DirD_T_A_And_BC_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_1,DirD_T_B_And_AC_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_2,DirD_T_C_And_AB_No_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},

   #if 0
   {&malaxation3DMode_to_83Hz_2,DirABAuto_And_CDAuto_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},

   {&malaxation3DMode_to_83Hz_2,DirACAutO_And_BDAut0_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},

   {&malaxation3DMode_to_83Hz_2,DirADAuto_And_BCAuto_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   #endif

   #if 0
   {&malaxation3DMode_to_83Hz_1,DirABC_T_D_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_1,DirABD_T_C_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_2,DirACD_T_B_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   {&malaxation3DMode_to_83Hz_2,DirCBD_T_A_PN},
   {&malaxation3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   #endif
};


#endif
#ifndef _scraping3DMode
#define _scraping3DMode


_PwmPulseType scraping3DMode_to_83Hz_1=
{
   ((25)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   240,
};

_PwmPulseType scraping3DMode_toIDLE_8H9z=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*8.9)),
   1,
};


_PwmPulse3Ddata scraping3DMode[]=
{
   {&scraping3DMode_to_83Hz_1,DirA_T_B_And_CD_No_PN},
   {&scraping3DMode_to_83Hz_1,DirA_T_C_And_BD_No_PN},
   {&scraping3DMode_to_83Hz_1,DirA_T_D_And_BC_No_PN},
   
   {&scraping3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   
   {&scraping3DMode_to_83Hz_1,DirB_T_A_And_CD_No_PN},
   {&scraping3DMode_to_83Hz_1,DirB_T_C_And_AD_No_PN},
   {&scraping3DMode_to_83Hz_1,DirB_T_D_And_AC_No_PN},
   
   {&scraping3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},

   {&scraping3DMode_to_83Hz_1,DirC_T_A_And_BD_No_PN},
   {&scraping3DMode_to_83Hz_1,DirC_T_B_And_AD_No_PN},
   {&scraping3DMode_to_83Hz_1,DirC_T_D_And_AB_No_PN},
   
   {&scraping3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},

   {&scraping3DMode_to_83Hz_1,DirD_T_A_And_BC_No_PN},
   {&scraping3DMode_to_83Hz_1,DirD_T_B_And_AC_No_PN},
   {&scraping3DMode_to_83Hz_1,DirD_T_C_And_AB_No_PN},
   
   {&scraping3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   #if 0

   {&scraping3DMode_to_83Hz_1,DirABAuto_And_CDAuto_PN},
   {&scraping3DMode_to_83Hz_1,DirACAutO_And_BDAut0_PN},
   {&scraping3DMode_to_83Hz_1,DirADAuto_And_BCAuto_PN},
   
   {&scraping3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
   #endif

   #if 0
   {&scraping3DMode_to_83Hz_1,DirABC_T_D_PN},
   {&scraping3DMode_to_83Hz_1,DirABD_T_C_PN},
   {&scraping3DMode_to_83Hz_1,DirACD_T_B_PN},
   {&scraping3DMode_to_83Hz_1,DirCBD_T_A_PN},
   #endif
   
   {&scraping3DMode_toIDLE_8H9z,DirAB_And_CD_IDLE},
};

#endif


#ifndef _Knock3DMode1_Define
#define _Knock3DMode1_Define

///  类似�?

 _PwmPulseType Knock3DMode1_short8Hz5=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*8.5)),
   18,
};
  _PwmPulseType Knock3DMode1_short4Hz9=
 {
	((30)),
	((SystemClkFreq)/(TimeFreqPSC*5.9)),
	16,
 };

 _PwmPulseType Knock3DMode1_short2Hz4=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*1.8)),
   10,
};
 _PwmPulseType Knock3DMode1_toIDLE_8H9z=
{
    0,
   ((SystemClkFreq)/(TimeFreqPSC*8.9)),
   10,
};

_PwmPulse3Ddata Knock3DMode1Mode[]=
{
   //	{&relieveMode1_short203ms_Count21,Dirforward},
	//{&relieveMode1_short203ms_Count21,Dirreverse},

    {&Knock3DMode1_short8Hz5,DirA_T_B_And_CD_No_PN},
    {&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
    {&Knock3DMode1_short8Hz5,DirA_T_C_And_BD_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short4Hz9,DirA_T_D_And_BC_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	
  	{&Knock3DMode1_short4Hz9,DirB_T_A_And_CD_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirB_T_C_And_AD_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirB_T_D_And_AC_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	
  	{&Knock3DMode1_short4Hz9,DirC_T_A_And_BD_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirC_T_B_And_AD_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirC_T_D_And_AB_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},

    {&Knock3DMode1_short4Hz9,DirD_T_A_And_BC_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirD_T_B_And_AC_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirD_T_C_And_AB_No_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	#if 0

    {&Knock3DMode1_short4Hz9,DirABAuto_And_CDAuto_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirABAuto_And_CDAuto_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirABAuto_And_CDAuto_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	#endif

    #if 0
    {&Knock3DMode1_short4Hz9,DirABC_T_D_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirABD_T_C_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirACD_T_B_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	{&Knock3DMode1_short2Hz4,DirCBD_T_A_PN},
  	{&Knock3DMode1_toIDLE_8H9z,DirAB_And_CD_IDLE},
  	#endif
};
#endif




_PwmPulse3DArray KnockMode3DMassage[]=
{
   {&Acupuncture3DMode[0],(sizeof(Acupuncture3DMode)/sizeof(_PwmPulse3Ddata))},
   {&Malaxation3DMode[0],(sizeof(Malaxation3DMode)/sizeof(_PwmPulse3Ddata))},
   {&scraping3DMode[0],(sizeof(scraping3DMode)/sizeof(_PwmPulse3Ddata))},
   {&Knock3DMode1Mode[0],(sizeof(Knock3DMode1Mode)/sizeof(_PwmPulse3Ddata))},
};



#ifndef __MassageIDLE_MODE__
#define __MassageIDLE_MODE__

_PwmPulseType MassageIDLEMode_to_116Hz=
{
   ((30)),
   ((SystemClkFreq)/(TimeFreqPSC*116)),
   24,
};
_PwmPulseData MassageIdleMode[]=
{
   	{&MassageIDLEMode_to_116Hz,DirPNAlter},
	{&MassageIDLEMode_to_116Hz,DirPNAlter},
	{&MassageIDLEMode_to_116Hz,DirPNAlter},
};



_PwmPulseArray MassageIDLEStatus[]=
{
   {&MassageIdleMode[0],(sizeof(MassageIdleMode)/sizeof(_PwmPulseData))},
};




#endif


#endif
