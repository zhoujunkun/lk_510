#include "Flash.h"
#include "TypedefDef.h"



volatile u32 VectorTable[48] __attribute__((at(0x20000000)));


#define Flash_Sector_Size 512
static u8 Flash_Init_Flag=FALSE;

#define FLASH_START_ADDRESS      0x08000000 
#define FLASH_APP_START_ADDR     (FLASH_START_ADDRESS + Flash_Sector_Size*8)


static void Flash_Int_CallBack(void)
{
   if (TRUE == Flash_GetIntFlag(FlashPCInt))
    {
        Flash_ClearIntFlag(FlashPCInt);
        Flash_DisableIrq(FlashPCInt);
    }
    if (TRUE == Flash_GetIntFlag(FlashSlockInt))
    {
        Flash_ClearIntFlag(FlashSlockInt);
        Flash_DisableIrq(FlashSlockInt);
    }
}

u8 Flash_Data_Writer(u8 *PageBuff,u32 PageAddress,u16 PageSize)
{
   u32 Flash_Page_Address=0,Flash_Page_EndAddress=0;
   u8 Error_Count=0;
   u8 Get_Page_Size_Sector=0;
   u8 i=0;
   u8 *PageSRData;
   PageSRData=PageBuff;

   Flash_Page_Address=PageAddress;
   Flash_Page_EndAddress=PageAddress+PageSize;
   if(FALSE==Flash_Init_Flag)
   	{
   	   Error_Count=0;
   	   while(Ok != Flash_Init(Flash_Int_CallBack, 1, TRUE))
	    {
	        if(++Error_Count>=3)
	        {
	          return FALSE;
	        }
	    }
	   Flash_Init_Flag=TRUE;
   	}
    Get_Page_Size_Sector=PageSize%Flash_Sector_Size;
	Get_Page_Size_Sector+=1;

    for(i=0;i<Get_Page_Size_Sector;i++)
    {
       Error_Count=0;
       while(Ok != Flash_SectorErase(PageAddress+i*Get_Page_Size_Sector))
	    {
	        if(++Error_Count>=3)
	        {
	          return FALSE;
	        }
	    }
    }

	while(Flash_Page_Address<Flash_Page_EndAddress)
	{
	
	   Flash_WriteByte(Flash_Page_Address,*PageSRData);
	   if(*(volatile u8 *)Flash_Page_Address!=*PageSRData)
	   	{
	   	   return FALSE;
	   	}
	   Flash_Page_Address++;
	   PageSRData++;
	}


	return TRUE;
	
}

void Flash_Data_Read(u8 *pageBuff,u32 PageAddress,u16 PageSize)
{
   u32 PageEndAddress=0,PageStartAddress=0;
   PageStartAddress=PageAddress;
   PageEndAddress=(PageAddress+PageSize);
   while(PageStartAddress<PageEndAddress)
   	{
   	   *pageBuff=*(volatile u8*)PageStartAddress;
	   PageStartAddress++;
   	}
}


void VectorTableOffset(void)
{
  uint8_t i;
  for(i = 0; i < 48; i++)
  {
    VectorTable[i] = *(volatile u32*)(FLASH_APP_START_ADDR + (i<<2));
  }
  
}
typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
u32 JumpAddress;

void Jump_AppRun(void)
{
	JumpAddress = *(volatile u32*) (FLASH_APP_START_ADDR + 4);
	Jump_To_Application = (pFunction) JumpAddress;
	__set_MSP(*(volatile u32*) FLASH_APP_START_ADDR);
	
	Jump_To_Application();
}








