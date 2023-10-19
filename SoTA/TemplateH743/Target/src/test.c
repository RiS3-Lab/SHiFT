#include <stdio.h>
#include "test.h"
#include "stdio.h"
#include "afl.h"

uint32_t bufferGlobal[10]; // accessing this buffer should trigger a memfault since there is no MPU region for it








/*
int test(uint8_t *buf, uint32_t size)
{

	if(size<7)
	{
		return FAULT_NONE_RTOS;
	}
	if(buf[0] == 'H' && buf[1] == 'a' && buf[2] == 'n' && buf[3] == 'g' )
	{
		//printf("\n Ouch time out!\n");

		//while(1)  // fake hang
		//{}
		return FAULT_TMOUT;
	}
	else if (buf[0] == 0)
	{
	    //printf("\n Looks like a zero to me!\n");
	}
	else if(buf[0] == 'B' && buf[1] == 'U' && buf[2] == 'G' )
	{
		//printf("\n You find me!!, I am a bug\n");
		bufferGlobal[0]++;
		return FAULT_CRASH; // we will not execute this line
	}
	else
	{
	    //printf("\n A non-zero value? How quaint!\n");
	    if(buf[3] == 'D' && buf[4] == 'E' && buf[5] == 'A' && buf[6] == 'D')
	    {
	    	//printf("\n I am a dead bug =)\n");
	    	bufferGlobal[1]++;
	    	return FAULT_CRASH; // we will not execute this line
	    }
	}

	return FAULT_NONE_RTOS;

}
*/

int test(uint8_t *buf, uint32_t size)
{

	uint8_t *localbuff;
    uint32_t arr32[4];
	uint16_t *ptr16;



	if(size<7)
	{
		return FAULT_NONE_RTOS; //normal execution does not trigger any bug
	}

	if(buf[0] == 'H' && buf[1] == 'A' && buf[2] == 'N' && buf[3] == 'G' )
	{

		buf[100]='T';
		while(1);  //Hang the task will be killed  by FreeRTOS
	}

	/***** MPU specific *******/
	else if(buf[0] == 'S' && buf[1] == 'E' && buf[2] == 'G' )
	{
		bufferGlobal[0]++; // Segmentation fault accessing a global variable outside the scope of the current task
		//return FAULT_CRASH; //this  line is not executed
	}

	else if(buf[0] == 'N' && buf[1] == 'U' && buf[2] == 'L' && buf[2] == 'L') //Null dereference
	{
			localbuff = 0x00;
			buf[0] = *localbuff;

	}

	/**** Cortex M specific *********/
	else if(buf[0] == 'Z' && buf[1] == 'E' && buf[2] == 'R' && buf[3] == '0')
	{
		arr32[0]= buf[0] / (buf[5]); //this should trigger a division by zero
	}
	else if(buf[0] == 'U' && buf[1] == 'D' && buf[2] == 'F')
	{
		__asm volatile("udf"); //this should trigger an undefined instruction exception
	}

	else if(buf[0] == 'U' && buf[1] == 'N' && buf[2] == 'A' )
	{
		arr32[0]= (uint32_t)buf[3];
		arr32[1]= (uint32_t)buf[4];
		localbuff = (uint8_t*)&arr32[0];
		localbuff += 3;
		ptr16 = (uint16_t *)localbuff;
		buf[0]= *ptr16; // unaligned access
	}


	 /**** ASAN specific ********/

    else if(buf[0] == 'U' && buf[1] == 'A' && buf[2] == 'F')
    {
    	localbuff =  malloc(32);
    	if(localbuff)
    	{
    		localbuff[0] = buf[0];
    		localbuff[1] = buf[0] + buf[2];
    		free(localbuff);
    		buf[0]=localbuff[1]; // use after free
    	}

    }
    else if(buf[0] == '2' && buf[1] == 'F' && buf[2] == 'R')
    {

    		localbuff =  malloc(32);
    		if(localbuff)
    		{
    			localbuff[0] = buf[0];
    			localbuff[1] = buf[0] + buf[2];
    			free(localbuff);
    		}
    		free(localbuff); //double free

    }

    else if(buf[0] == 'I' && buf[1] == 'F' && buf[2] == 'R')
    {

    	localbuff =  malloc(32);
    	if(localbuff)
    	{
    		localbuff[0] = buf[0];
    		localbuff[1] = buf[0] + buf[2];
    	}
    	localbuff+=10;
    	free(localbuff); //invalid free

    }

    else if(buf[0] == 'O' && buf[1] == 'F' && buf[2] == 'S') //overflow in stack
    {

    	buf[0] = arr32[buf[4]];

    }
    else if(buf[0] == 'O' && buf[1] == 'F' && buf[2] == 'H') //overflow in heap
    {
    	localbuff =  malloc(8);
    	if(localbuff)
    	{
    		localbuff[9]=10;//overflow in heap
    		free(localbuff);
    	}

    }

	return FAULT_NONE_RTOS; //normal execution does not trigger any bug


}
