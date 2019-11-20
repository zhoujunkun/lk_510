#ifndef __NTCTEMPSAMPLE__HH__
#define __NTCTEMPSAMPLE__HH__

#include "TypedefDef.h"
#include "Global.h"


typedef struct
{
   _FilterSampleBuffFloat BatteryVoltageSample;
   _FilterSampleBuffFloat NTCTempSample;
   float NTCTempRsist;
   u8 tempvalue;
   u8 NTC_Count;
}_NTCDataSample;







extern _NTCDataSample NTCDataSmaple;

void NTCSampleDataHandler(void);

#endif
