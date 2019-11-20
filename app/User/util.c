#include "Util.h"


void SampleFilterHandler(_FilterSampleBuff *FilterSample,u16 SampleValue)
{
   volatile u32 Temp=0;
   u32 Max_Value=0,Min_Value=0xffff;
   u8 i=0;
   FilterSample->FilterBuffer[FilterSample->FilterIndex++]=SampleValue;
   if(FilterSample->FilterIndex>=FilterBufferMaxLength)
   	{
   	  FilterSample->FilterIndex=0;
   	}
   Temp=0;
   for(i=0;i<FilterBufferMaxLength;i++)
   	{
   	   Temp+=FilterSample->FilterBuffer[i];
	   if(Max_Value<FilterSample->FilterBuffer[i])
	   	Max_Value=FilterSample->FilterBuffer[i];
	   if(Min_Value>FilterSample->FilterBuffer[i])
	   	Min_Value=FilterSample->FilterBuffer[i];
   	}
   Temp/=(FilterBufferMaxLength);
   FilterSample->FilterAvgValue=Temp;
   FilterSample->FilterMaxValue=Max_Value;
   FilterSample->FilterMinValue=Min_Value;
   
}


void SampleFilterFloatHandler(_FilterSampleBuffFloat *FilterSample,float SampleValue)
{
   volatile float Temp=0;
   u32 Max_Value=0,Min_Value=0xffff;
   u8 i=0;
   FilterSample->FilterBuffer[FilterSample->FilterIndex++]=SampleValue;
   if(FilterSample->FilterIndex>=FilterBufferMaxLength)
   	{
   	  FilterSample->FilterIndex=0;
	  FilterSample->FilterCmpFlag=1;
   	}
   Temp=0;
   for(i=0;i<FilterBufferMaxLength;i++)
   	{
   	   Temp+=FilterSample->FilterBuffer[i];
	   if(Max_Value<FilterSample->FilterBuffer[i])
	   	Max_Value=FilterSample->FilterBuffer[i];
	   if(Min_Value>FilterSample->FilterBuffer[i])
	   	Min_Value=FilterSample->FilterBuffer[i];
   	}
   Temp/=(FilterBufferMaxLength);
   FilterSample->FilterAvgValue=Temp;
   FilterSample->FilterMaxValue=Max_Value;
   FilterSample->FilterMinValue=Min_Value;
   
}

u8 CompareParaSize(u32 CompTV1,u32 CompSV2,u32 diff)
{
   if(CompTV1>=CompSV2)
   	{
   	  if((CompTV1-CompSV2)<=diff)
   	  	{
   	  	  return 1;
   	  	}
	  return 0;
   	}

   if(CompSV2>=CompTV1)
   	{
   	   if((CompSV2-CompTV1)<=diff)
   	   	{
   	   	  return 1;
   	   	}
	   return 0;
   	}
   
}





