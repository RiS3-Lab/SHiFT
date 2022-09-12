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







void *MPU_ASAN_malloc(size_t size)
{
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	void *ptr = Allocate(size, 8, FROM_MALLOC, true);

	vPortResetPrivilege( xRunningPrivileged );
	return  (void *	)ptr;
}


void MPU_ASAN_free(void *ptr)
{
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	Deallocate(ptr, 0, 0, FROM_MALLOC);

	vPortResetPrivilege( xRunningPrivileged );
}

void MPU_ASAN_flush_alloc()
{

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	//FlushAlloc();

	vPortResetPrivilege( xRunningPrivileged );

}



void MPU_SytemCall_1()
{

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	SytemCall_1_code();

	vPortResetPrivilege( xRunningPrivileged );

}


void MPU_SytemCall_2()
{

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	SytemCall_2_code();

	vPortResetPrivilege( xRunningPrivileged );

}


void MPU_SytemCall_3()
{

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	SytemCall_3_code();

	vPortResetPrivilege( xRunningPrivileged );

}



void MPU_SytemCall_4(void *val)
{

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	SytemCall_4_code(val);

	vPortResetPrivilege( xRunningPrivileged );

}

void MPU_SytemCall_5(void *val)
{

	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	SytemCall_5_code(val);

	vPortResetPrivilege( xRunningPrivileged );

}



#if DUALCOREFUZZ

void MPU_WWDG_Refresh()
{
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	refreshWWDG();

    vPortResetPrivilege( xRunningPrivileged );
}


void MPU_WWDG_activate()
{
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	activateWWDG();

    vPortResetPrivilege( xRunningPrivileged );
}


void MPU_HSEM_notify(uint32_t HS)
{
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	NotifyHSEM(HS);

    vPortResetPrivilege( xRunningPrivileged );
}

void MPU_HSEM_activate_notification(uint32_t HS)
{
	BaseType_t xRunningPrivileged = xPortRaisePrivilege();

	ActivateNotificationHSEM(HS);

    vPortResetPrivilege( xRunningPrivileged );
}
#endif

#endif /* APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS_H_ */
