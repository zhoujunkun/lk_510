#include "AdcSample.h"
#include "Adc.h"
#include "ddl.h"
#include "TypedefDef.h"
#include "Dmac.h"
#include "Gpio.h"
#include "Global.h"
#include "UartHandler.h"



void DmaContIrqCallback(void);

u32 ADC_Result_Array[10] = {0};

void Delay_us(u16 count)
{
   u16 j=0,i=0;
   for(i=0;i<count;i++)
   	{
   	   j=1000;
	   while(j--);
   	}
}

void AdcSampleInit(void)
{
   stc_adc_cfg_t              stcAdcCfg;

   stc_dma_config_t stcDmaCfg;
   stc_dma_irq_sel_t          stcDmaIrq;
   stc_dma_irq_calbakfn_pt_t  stcDmaIrqCalbaks;


   stc_gpio_config_t stcGpioCfg;
   

   Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);
   Sysctrl_SetPeripheralGate(SysctrlPeripheralDma,TRUE);
   Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, TRUE);
   DDL_ZERO_STRUCT(stcAdcCfg);
   DDL_ZERO_STRUCT(stcDmaCfg);
   DDL_ZERO_STRUCT(stcDmaIrq);
   DDL_ZERO_STRUCT(stcGpioCfg);
   DDL_ZERO_STRUCT(stcDmaIrqCalbaks);


    Gpio_SetAnalogMode(GpioPortA, GpioPin4);        //PA04 (AIN4)   ///  FB
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA, GpioPin4, &stcGpioCfg);

    Gpio_SetAnalogMode(GpioPortA, GpioPin2);        //PA02 (AIN2)    ///  NTC  
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA, GpioPin2, &stcGpioCfg);

	 Gpio_SetAnalogMode(GpioPortA, GpioPin5);        //PA05 (AIN5)  check Externison
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA, GpioPin5, &stcGpioCfg);

   Adc_Enable();
   M0P_BGR->CR_f.BGR_EN = 0x1u;                 //BGR必须使能
   M0P_BGR->CR_f.TS_EN = 0x0u;
   Delay_us(100); 

   stcAdcCfg.enAdcOpMode=AdcSCanMode;
   stcAdcCfg.enAdcClkDiv=AdcClkSysTDiv4;
   stcAdcCfg.bAdcInBufEn=TRUE;
   stcAdcCfg.enAdcRefVolSel=RefVolSelInBgr2p5;
   stcAdcCfg.enAdcSampTimeSel=AdcSampTime12Clk;

   Adc_Init(&stcAdcCfg);

   Adc_SetVref(RefVolSelInBgr2p5);
   
   Adc_ConfigSqrChannel(CH0MUX,AdcExInputCH4);
   Adc_ConfigSqrChannel(CH1MUX,AdcExInputCH2);
   Adc_ConfigSqrChannel(CH2MUX,AdcExInputCH5);
   Adc_ConfigSqrChannel(CH3MUX,AdcAVccDiV3Input);

   Adc_ConfigSqrMode(&stcAdcCfg, 4, FALSE);

   Adc_ConfigDmaTrig(DmaSqr);


  stcDmaCfg.enMode =  DmaBlock;                   
  stcDmaCfg.u16BlockSize = 0x04u;
  stcDmaCfg.u16TransferCnt = 0x01u;         //Block模式，一次传输数据大小为 1,传输三次
  stcDmaCfg.enTransferWidth = Dma32Bit;            
  stcDmaCfg.enSrcAddrMode = AddressIncrease;
  stcDmaCfg.enDstAddrMode = AddressIncrease;
  stcDmaCfg.bDestAddrReloadCtl = TRUE;
  stcDmaCfg.bSrcAddrReloadCtl = TRUE;
  stcDmaCfg.bSrcBcTcReloadCtl = TRUE;
  stcDmaCfg.u32SrcAddress = (uint32_t) &(M0P_ADC->SQRRESULT0);
  stcDmaCfg.u32DstAddress = (uint32_t)&ADC_Result_Array[0];
  stcDmaCfg.bMsk = TRUE;                                         //DMAC 在传输完成时不清除 CONFA:ENS 位。这个功能允许连续传输而不需要 CPU 干预。
  stcDmaCfg.enRequestNum = ADCSQRTrig;	                         //设置为ADC SQR触发
  
  Dma_InitChannel(DmaCh0,&stcDmaCfg);	


  Dma_EnableChannelIrq(DmaCh0);
  EnableNvic(DMAC_IRQn,IrqLevel3,TRUE);
  
  stcDmaIrq.TrnCpltIrq= TRUE;
  stcDmaIrqCalbaks.pfnDma0TranferCompleteIrq = (func_ptr_t)DmaContIrqCallback;
  
  Dma_ConfigIrq(DmaCh0,&stcDmaIrq, &stcDmaIrqCalbaks);
  
  //使能DMA，使能DMA0，启动DMA0
  Dma_Enable();
  Dma_EnableChannel(DmaCh0);
  Dma_Start(DmaCh0);
  Adc_SQR_Start();
   
}
void AdcSampleSleepInit(void)
{
   Sysctrl_SetPeripheralGate(SysctrlPeripheralDma,FALSE);
   Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr,FALSE);
   Adc_Disable();
   Dma_Stop(DmaCh0);
}
extern volatile u8 IRQ_Start_Enable;
void DmaContIrqCallback(void)
{    
  IRQ_Start_Enable=1;
}


