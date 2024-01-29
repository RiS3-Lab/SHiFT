/*
 * ring.c
 *
 *  Created on: Sep 10, 2021
 *      Author: alejandro
 */

#include "ring.h"
#include "string.h"


/* Ring Buffer functions */
// This function must be called only after disabling USART RX interrupt or inside of the RX interrupt
void RingAdd(RingBuffer_t *xRingBuffer, uint8_t u8Val)
{

	xRingBuffer->uxBuffer[xRingBuffer->u32end] = u8Val;
	xRingBuffer->u32end = (xRingBuffer->u32end + 1) % MAX_BUFFER_INPUT;
	if (xRingBuffer->u32available == MAX_BUFFER_INPUT)
	{
		xRingBuffer->overflow = true;
		xRingBuffer->u32start = (xRingBuffer->u32start + 1) % MAX_BUFFER_INPUT;
	}
	else
	{
		xRingBuffer->overflow = false;
		xRingBuffer->u32available++;
	}

}



/* Ring Buffer functions */

void RingCopy(RingBuffer_t *xRingBuffer, uint8_t* u8Buff, uint32_t len)
{
	uint32_t u32Free=0;


	u32Free = MAX_BUFFER_INPUT - xRingBuffer->u32end;

	if(u32Free > len)
	{
		memcpy( &xRingBuffer->uxBuffer[xRingBuffer->u32end], u8Buff, len );
		xRingBuffer->u32end = (xRingBuffer->u32end + len);
		xRingBuffer->u32available += len;

	}
	else
	{
		memcpy( &xRingBuffer->uxBuffer[xRingBuffer->u32end], u8Buff, u32Free);
		xRingBuffer->u32end = (xRingBuffer->u32end + u32Free);
		xRingBuffer->u32available += u32Free;
	}

	xRingBuffer->overflow = false;

}




// This function must be called only after disabling USART RX interrupt
uint32_t RingGetAllBytes(RingBuffer_t *xRingBuffer, uint8_t *buffer)
{
	return RingGetNBytes(xRingBuffer, buffer, xRingBuffer->u32available);
}

// This function must be called only after disabling USART RX interrupt
uint32_t RingGetNBytes(RingBuffer_t *xRingBuffer, uint8_t *buffer, uint32_t uNumber)
{
	uint8_t uCounter;
	if(xRingBuffer->u32available == 0  || uNumber == 0 ) return 0;
	if(uNumber > MAX_BUFFER_INPUT) return 0;

	for(uCounter = 0; uCounter < uNumber && uCounter< xRingBuffer->u32available ; uCounter++)
	{
		buffer[uCounter] = xRingBuffer->uxBuffer[xRingBuffer->u32start];
		xRingBuffer->u32start = (xRingBuffer->u32start + 1) % MAX_BUFFER_INPUT;
	}
	xRingBuffer->u32available = xRingBuffer->u32available - uCounter;
	xRingBuffer->overflow = false;
	RingClear(xRingBuffer);

	return uCounter;
}

uint32_t RingCountBytes(RingBuffer_t *xRingBuffer)
{
return xRingBuffer->u32available;
}

void RingClear(RingBuffer_t *xRingBuffer)
{
xRingBuffer->u32start = 0;
xRingBuffer->u32end = 0;
xRingBuffer->u32available = 0;
xRingBuffer->u32availablenopad = 0;
xRingBuffer->overflow = false;
}


void RingZeroes(RingBuffer_t *xRingBuffer)
{
	RingClear(xRingBuffer);
	/*
	for (uint32_t i=0; i<MAX_BUFFER_INPUT; i++)
	{
		xRingBuffer->uxBuffer[i]=0;
	}
*/

}

/* End of Ring Buffer functions */

