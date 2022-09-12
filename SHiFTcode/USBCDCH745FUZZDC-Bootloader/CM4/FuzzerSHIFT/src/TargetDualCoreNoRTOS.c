#include "TargetDualCoreNoRTOS.h"
#include "bootloader.h"
#include "McuASAN.h"
#include "main.h"
#include "fuzzing.h"
#include "stdlib.h"
#include "stdbool.h"
#include "test.h"




#define PERSISTENMODE 1000



extern uint8_t redzone1[64]  __attribute__( ( aligned(64)));
extern uint8_t RxData[64] __attribute__( ( aligned(64)));
extern uint8_t redzone2[64] __attribute__( ( aligned(64)));
extern uint8_t redzone3[FLASH_PAGE_SIZE]  __attribute__( ( aligned(FLASH_PAGE_SIZE)));
extern uint8_t PageBuffer[FLASH_PAGE_SIZE] __attribute__( ( aligned(FLASH_PAGE_SIZE)));
extern uint8_t redzone4[FLASH_PAGE_SIZE] __attribute__( ( aligned(FLASH_PAGE_SIZE)));


uint32_t DataNoti;
uint32_t cycles;


void targetNoRTOS()
{


    Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
    HSEM_activate_notification(HSEM_ID_1);

#if WATCHDOGENABLED
    activateWWDG();
#endif

#if 0
    typedef struct
    {
      uint8_t                Enable;                /*!< Specifies the status of the region.
                                                         This parameter can be a value of @ref CORTEX_MPU_Region_Enable                 */
      uint8_t                Number;                /*!< Specifies the number of the region to protect.
                                                         This parameter can be a value of @ref CORTEX_MPU_Region_Number                 */
      uint32_t               BaseAddress;           /*!< Specifies the base address of the region to protect.                           */
      uint8_t                Size;                  /*!< Specifies the size of the region to protect.
                                                         This parameter can be a value of @ref CORTEX_MPU_Region_Size                   */
      uint8_t                SubRegionDisable;      /*!< Specifies the number of the subregion protection to disable.
                                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF    */
      uint8_t                TypeExtField;          /*!< Specifies the TEX field level.
                                                         This parameter can be a value of @ref CORTEX_MPU_TEX_Levels                    */
      uint8_t                AccessPermission;      /*!< Specifies the region access permission type.
                                                         This parameter can be a value of @ref CORTEX_MPU_Region_Permission_Attributes  */
      uint8_t                DisableExec;           /*!< Specifies the instruction access status.
                                                         This parameter can be a value of @ref CORTEX_MPU_Instruction_Access            */
      uint8_t                IsShareable;           /*!< Specifies the shareability status of the protected region.
                                                         This parameter can be a value of @ref CORTEX_MPU_Access_Shareable              */
      uint8_t                IsCacheable;           /*!< Specifies the cacheable status of the region protected.
                                                         This parameter can be a value of @ref CORTEX_MPU_Access_Cacheable              */
      uint8_t                IsBufferable;          /*!< Specifies the bufferable status of the protected region.
                                                         This parameter can be a value of @ref CORTEX_MPU_Access_Bufferable             */
    }MPU_Region_InitTypeDef;

#endif


    MPU_Region_InitTypeDef mpuregion;


    // Poisoning redzones
    HAL_MPU_Disable();

    mpuregion.Number = MPU_REGION_NUMBER0;
    mpuregion.Enable = MPU_REGION_ENABLE;
    mpuregion.BaseAddress = (uint32_t)&redzone1;
    mpuregion.Size = MPU_REGION_SIZE_64B;
    mpuregion.AccessPermission = MPU_REGION_NO_ACCESS;
    mpuregion.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    mpuregion.IsCacheable = MPU_ACCESS_CACHEABLE;
    mpuregion.IsShareable = MPU_ACCESS_SHAREABLE;
    mpuregion.TypeExtField = MPU_TEX_LEVEL0;
    mpuregion.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    mpuregion.SubRegionDisable = 0;

    HAL_MPU_ConfigRegion(&mpuregion);

    mpuregion.Number = MPU_REGION_NUMBER1;
    mpuregion.BaseAddress = (uint32_t)&redzone2;
    HAL_MPU_ConfigRegion(&mpuregion);

    mpuregion.Number = MPU_REGION_NUMBER2;
    mpuregion.BaseAddress = (uint32_t)&redzone3;
    mpuregion.Size = MPU_REGION_SIZE_128B;
    HAL_MPU_ConfigRegion(&mpuregion);

    mpuregion.Number = MPU_REGION_NUMBER3;
    mpuregion.BaseAddress = (uint32_t)&redzone4;
    HAL_MPU_ConfigRegion(&mpuregion);

    mpuregion.Number = MPU_REGION_NUMBER4;
    mpuregion.BaseAddress = (uint32_t)0x24060000; // CM7 area
    mpuregion.Size = MPU_REGION_SIZE_128KB;
    HAL_MPU_ConfigRegion(&mpuregion);

    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);


    DataNoti = 0;
    cycles = 0;
    NotifyHSEM(HSEM_ID_3); // notify the monitor that CM4 is up

    uint32_t *test = (uint32_t *)0x24060000;


    while(1)
    {
    	while(!DataNoti) //wait for data coming from CM& through CAN
    	{
            #if WATCHDOGENABLED
    		    refreshWWDG();
            #endif
    	}

    	DataNoti = 0;

    	#if WATCHDOGENABLED
    	    refreshWWDG();
        #endif



    	//AFLfuzzer.notiVCM4TOCM7 = test(&AFLfuzzer.inputAFL.uxBuffer[4], AFLfuzzer.inputAFL.u32availablenopad-4 );

    	//HSEM_activate_notification(HSEM_ID_1); //activate notification for data received
    	AFLfuzzer.notiVCM4TOCM7 = FAULT_NONE_RTOS; // we are not using RTOS but the returning values are the same
    	NotifyHSEM(HSEM_ID_2); //notify CM7 end of test

#if(PERSISTENMODE)
        	cycles++;
        	if(cycles>=PERSISTENMODE)
        	{
        	    //we don't need this for this firmware
        		//while(1); // force the watchdog timer to reset the CM4 core
        	}
#else
        	while(1);
#endif


    }




}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{

    #if WATCHDOGENABLED
  		    refreshWWDG();
    #endif
	HAL_FDCAN_RxFifo0CallbackDummie(hfdcan,RxFifo0ITs);
	DataNoti = 1;

	// notify the core that fuzzing input was processed

}


void HAL_HSEM_FreeCallback(uint32_t SemMask)
{

  // notification from CM7 to reboot CM4 forcing a hang
  if (SemMask == __HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1))
  {
	  //DataNoti = 1; // data
	   while(1); //force a hang

  }



}


