#include "TypedefDef.h"

static u32  fac_us=0;							   
static u32 fac_ms=0;


void delay_init(u8 SYSCLK)
{
 	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SystemCoreClock/9000000;;						
	fac_ms=(u16)fac_us*1000;	
}								    


void delay_us(u32 nus)
{		
  u32 temp;
  SysTick->LOAD = 9*nus;
  SysTick->VAL=0X00;
  SysTick->CTRL=0X01;
  do
   {
	  temp=SysTick->CTRL;
   }while((temp&0x01)&&(!(temp&(1<<16))));
   SysTick->CTRL=0x00; 
   SysTick->VAL =0X00;			
}

void delay_xms(u16 nms)
{	 		  	  
	u32 temp;
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL=0X00;
	 SysTick->CTRL=0X01;
	 do
	 {
	  temp=SysTick->CTRL;
	 }while((temp&0x01)&&(!(temp&(1<<16))));
    SysTick->CTRL=0x00;
    SysTick->VAL =0X00;    	    
} 

void Delay_ms(u16 nms)
{	 	 
	delay_xms(nms);
} 


void Delay_s(u16 seconde)
{
   /*
   u16 remain=0;
   u16 repeat=0;
   u16 temp=0;
   temp=seconde*1000;
   repeat=temp%1000;
  while(repeat)
   	{
   	   Delay_ms(1000);
	   repeat--;
   	}
   remain=temp%1000;
   if(remain)
   Delay_ms(remain);
   */

   while(seconde)
   	{
   	  Delay_ms(1000);
	  seconde--;
   	}
}

