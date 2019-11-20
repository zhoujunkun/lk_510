#ifndef __UTIL__HH__
#define __UTIL__HH__
#include "Global.h"
void SampleFilterHandler(_FilterSampleBuff *FilterSample,u16 SampleValue);
void SampleFilterFloatHandler(_FilterSampleBuffFloat *FilterSample,float SampleValue);
u8 CompareParaSize(u32 CompTV1,u32 CompSV2,u32 diff);


#endif
