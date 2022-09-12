/*
 * test.c
 *
 *  Created on: Sep 3, 2021
 *      Author: alejandro
 */

#include "test2.h"
#include "stdio.h"
#include "afl.h"

int test2(uint8_t *buf)
{


	if(buf[7] == 0xff)
	{
		//printf("\n Ouch time out!\n");
		return FAULT_TMOUT;
	}
	else if (buf[0] == 0)
	{
	    //printf("\n Looks like a zero to me!\n");
	}
	else if(buf[0] == 'B' && buf[1] == 'U' && buf[2] == 'G' )
	{
		//printf("\n You find me!!, I am a bug\n");
		return FAULT_CRASH;
	}
	else
	{
	    //printf("\n A non-zero value? How quaint!\n");
	    if(buf[3] == 'D' && buf[4] == 'E' && buf[5] == 'A' && buf[6] == 'D')
	    {
	    	//printf("\n I am a dead bug =)\n");
	    	return FAULT_CRASH;
	    }
	}

	return FAULT_NONE;

}

