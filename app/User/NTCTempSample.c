#include "NTCTempSample.h"
#include "TypedefDef.h"
_NTCDataSample NTCDataSmaple;
#define NTC_Divider_UpResist 51


static float NTCTempVoltage[]=
{
   80.3868,77.0106,73.794,70.7309,
   67.8113,65.0283,62.375,59.8448,
   57.4312,55.1284,52.930,50.8328,
   48.8297,46.9166,45.089,43.3428,
   41.6736,40.0779,38.552,37.0924,
   35.696, 34.3596,33.080,31.8556,
   30.6826,29.559, 28.482,27.4504,
   26.4612,25.5126
};


void NTCSampleDataHandler(void)
{
   float NTCSampledata=0;
   float NTCSampledata1=0;
   u8 i=0;
   if(3000>NTCDataSmaple.NTCTempSample.FilterAvgValue)
   	{
   	   NTCSampledata=(3000-NTCDataSmaple.NTCTempSample.FilterAvgValue);
	   NTCSampledata1=NTCSampledata/NTC_Divider_UpResist;
	   NTCDataSmaple.NTCTempRsist=NTCDataSmaple.NTCTempSample.FilterAvgValue/NTCSampledata1;
   	  // NTCDataSmaple.NTCTempRsist=(NTC_Divider_UpResist*NTCDataSmaple.NTCTempSample.FilterAvgValue/NTCSampledata);
	   for(i=0;i<(sizeof(NTCTempVoltage)/sizeof(float));i++)
	   	{
	   	    if(NTCDataSmaple.NTCTempRsist>NTCTempVoltage[i])
				break;
	   	}
	    NTCDataSmaple.tempvalue=(i+28);
   	}
}




