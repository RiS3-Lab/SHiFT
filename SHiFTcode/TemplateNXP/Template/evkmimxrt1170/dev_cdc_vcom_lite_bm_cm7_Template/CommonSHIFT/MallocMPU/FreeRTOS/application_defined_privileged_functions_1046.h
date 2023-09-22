/*
 * application_defined_privileged_functions.h
 *
 *  Created on: Nov 12, 2021
 *      Author: alejandro
 */

#ifndef APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS_H_
#define APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS_H_

#include "FreeRTOS.h"
#include "McuASAN.h"
#include "fuzzing.h"


/*
void *ASAN_malloc(size_t size) FREERTOS_SYSTEM_CALL;
void ASAN_free(void *ptr) FREERTOS_SYSTEM_CALL;
void ASAN_flush_alloc() FREERTOS_SYSTEM_CALL;
void MPU_WWDG_Refresh() FREERTOS_SYSTEM_CALL;
void MPU_HSEM_activate_notification(uint32_t HS) FREERTOS_SYSTEM_CALL;
void MPU_HSEM_notify(uint32_t HS) FREERTOS_SYSTEM_CALL;
void MPU_WWDG_activate() FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_1() FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_2() FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_3() FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_4(void *val)FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_5(void *val)FREERTOS_SYSTEM_CALL;
*/


/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h.  The functions
 * must take the same format as those above whereby the privilege state on exit
 * equals the privilege state on entry.  For example:
 *
 * void MPU_FunctionName( [parameters ] )
 * {
 * BaseType_t xRunningPrivileged = xPortRaisePrivilege();
 *
 *  FunctionName( [parameters ] );
 *
 *  vPortResetPrivilege( xRunningPrivileged );
 * }
 */
/*

void *MPU_mallocMPU( size_t size)
{
	uint32_t *pointer = NULL;

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	pointer = (uint32_t *)mallocMPU(size);

	vPortResetPrivilege( xRunningPrivileged );

	return pointer;
}



void MPU_freeMPU(void *ptr)
{
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	freeMPU(ptr);

	vPortResetPrivilege( xRunningPrivileged );

}


void MPU_InitmallocMPU(uint8_t *StartAddressA,
		uint8_t *StartAddressB,
		uint32_t Blocksize,
		uint32_t Regionsize,
		uint8_t Firstregion,
		int8_t  TotalRegion,
		func *callbackInvalidFree
		)
{

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	InitmallocMPU(StartAddressA,
			StartAddressB,
			Blocksize,
			Regionsize,
			Firstregion,
			TotalRegion,
			callbackInvalidFree
			);

	vPortResetPrivilege( xRunningPrivileged );

}
*/

// FreeRTOSReportFailure(type_exception_t  tEX);






void *MPU_ASAN_malloc(size_t size) FREERTOS_SYSTEM_CALL;
void *MPU_ASAN_malloc(size_t size)
{
	/*
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	void *ptr = Allocate(size, 8, FROM_MALLOC, true);

	vPortResetPrivilege( xRunningPrivileged );
	return  (void *	)ptr;
*/

	  void *ptr;

	 if( portIS_PRIVILEGED() == pdFALSE )
	 {
	       portRAISE_PRIVILEGE();
	       portMEMORY_BARRIER();


	       while(portIS_PRIVILEGED() == pdFALSE);


	       ptr = Allocate(size, 8, FROM_MALLOC, true);
           portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
       }
        else
        {
        	ptr = Allocate(size, 8, FROM_MALLOC, true);
        }

	  return  (void *	)ptr;

}





void MPU_ASAN_free(void *ptr) FREERTOS_SYSTEM_CALL;
void MPU_ASAN_free(void *ptr)
{
	/*
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	Deallocate(ptr, 0, 0, FROM_MALLOC);

	vPortResetPrivilege( xRunningPrivileged );

	 */
	 if( portIS_PRIVILEGED() == pdFALSE )
	 {
	       portRAISE_PRIVILEGE();
	       portMEMORY_BARRIER();

	       Deallocate(ptr, 0, 0, FROM_MALLOC);
	       portMEMORY_BARRIER();

	       portRESET_PRIVILEGE();
	       portMEMORY_BARRIER();
	   }
	   else
	   {
	      	Deallocate(ptr, 0, 0, FROM_MALLOC);
	   }

}

void MPU_ASAN_flush_alloc()
{

	//BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	//FlushAlloc();

	//vPortResetPrivilege( xRunningPrivileged );

}




void MPU_SytemCall_1() FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_1()
{


	 if( portIS_PRIVILEGED() == pdFALSE )
	 {
	       portRAISE_PRIVILEGE();
	       portMEMORY_BARRIER();


	   	   SytemCall_1_code();
	       portMEMORY_BARRIER();

	       portRESET_PRIVILEGE();
	       portMEMORY_BARRIER();
	   }
	   else
	   {
		   SytemCall_1_code();
	   }

}

void MPU_SytemCall_2() FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_2()
{

	 if( portIS_PRIVILEGED() == pdFALSE )
		 {
		       portRAISE_PRIVILEGE();
		       portMEMORY_BARRIER();


		   	   SytemCall_2_code();
		       portMEMORY_BARRIER();

		       portRESET_PRIVILEGE();
		       portMEMORY_BARRIER();
		   }
		   else
		   {
			   SytemCall_2_code();
		   }

}

void MPU_SytemCall_3() FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_3()
{

	 if( portIS_PRIVILEGED() == pdFALSE )
		 {
		       portRAISE_PRIVILEGE();
		       portMEMORY_BARRIER();


		   	   SytemCall_3_code();
		       portMEMORY_BARRIER();

		       portRESET_PRIVILEGE();
		       portMEMORY_BARRIER();
		   }
		   else
		   {
			   SytemCall_3_code();
		   }

}


void MPU_SytemCall_4(void *val) FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_4(void *val)
{

	 if( portIS_PRIVILEGED() == pdFALSE )
		 {
		       portRAISE_PRIVILEGE();
		       portMEMORY_BARRIER();


		   	   SytemCall_4_code(val);
		       portMEMORY_BARRIER();

		       portRESET_PRIVILEGE();
		       portMEMORY_BARRIER();
		   }
		   else
		   {
			   SytemCall_4_code(val);
		   }

}

void MPU_SytemCall_5(void *val) FREERTOS_SYSTEM_CALL;
void MPU_SytemCall_5(void *val)
{

	 if( portIS_PRIVILEGED() == pdFALSE )
		 {
		       portRAISE_PRIVILEGE();
		       portMEMORY_BARRIER();


		   	   SytemCall_5_code(val);
		       portMEMORY_BARRIER();

		       portRESET_PRIVILEGE();
		       portMEMORY_BARRIER();
		   }
		   else
		   {
			   SytemCall_5_code(val);
		   }

}



#if DUALCOREFUZZ

void MPU_WWDG_Refresh()
{

    if( portIS_PRIVILEGED() == pdFALSE )
    {
   	    portRAISE_PRIVILEGE();
   	    portMEMORY_BARRIER();


   	    refreshWWDG();

   	    portMEMORY_BARRIER();

   	    portRESET_PRIVILEGE();
   	    portMEMORY_BARRIER();
   	 }
   	 else
   	 {
   		refreshWWDG();
   	  }

}


void MPU_WWDG_activate()
{


    if( portIS_PRIVILEGED() == pdFALSE )
    {
   	    portRAISE_PRIVILEGE();
   	    portMEMORY_BARRIER();


   	 activateWWDG();

   	    portMEMORY_BARRIER();

   	    portRESET_PRIVILEGE();
   	    portMEMORY_BARRIER();
   	 }
   	 else
   	 {
   		activateWWDG();
   	  }


}


void MPU_HSEM_notify(uint32_t HS)
{


    if( portIS_PRIVILEGED() == pdFALSE )
    {
   	    portRAISE_PRIVILEGE();
   	    portMEMORY_BARRIER();


   	    NotifyHSEM(HS);

   	    portMEMORY_BARRIER();

   	    portRESET_PRIVILEGE();
   	    portMEMORY_BARRIER();
   	 }
   	 else
   	 {
   		NotifyHSEM(HS);
   	  }



}

void MPU_HSEM_activate_notification(uint32_t HS)
{


    if( portIS_PRIVILEGED() == pdFALSE )
    {
   	    portRAISE_PRIVILEGE();
   	    portMEMORY_BARRIER();


   	    ActivateNotificationHSEM(HS);

   	    portMEMORY_BARRIER();

   	    portRESET_PRIVILEGE();
   	    portMEMORY_BARRIER();
   	 }
   	 else
   	 {
   		ActivateNotificationHSEM(HS);
   	  }

}
#endif

#endif /* APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS_H_ */
