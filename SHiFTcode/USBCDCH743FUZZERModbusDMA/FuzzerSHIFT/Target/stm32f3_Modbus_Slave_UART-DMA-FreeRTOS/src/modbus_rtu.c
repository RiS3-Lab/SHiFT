
#include "modbus_rtu.h"
#include "modbus_rtu_conf.h"
#include "string.h"
#include "afl.h"
#include "fuzzing.h"

/*
-fsanitize-coverage=trace-pc
-fsanitize=address
-fno-common
*/


//#define MODBUS_INTERRUPT_PRIORITY configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2




extern uint16_t modbusMemory[MODBUS_SLAVE_REGISTERS_NUM];
extern uint8_t modbusRxTxBuffer[MODBUS_MAX_FRAME_SIZE];
extern modbus_t  modbusVars __attribute__( ( aligned( next_power_of_2(sizeof(modbus_t)) ) ) );
//extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart4 __attribute__( ( aligned( next_power_of_2(sizeof(modbus_t)) ) ) );;

#if DUALCOREFUZZ == 0
uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
#endif



//volatile uint16_t modbusRxCount = 0;
//volatile uint8_t modbusSlaveFrameReadyFlag = 0;
//static xSemaphoreHandle xFrameReadySemaphore;
//static xTaskHandle xModbusSlaveTask;

#define modbusRxCount modbusVars.modbusRxCountV
#define modbusSlaveFrameReadyFlag modbusVars.modbusSlaveFrameReadyFlagV
#define xFrameReadySemaphore modbusVars.xFrameReadySemaphoreV
#define xModbusSlaveTask modbusVars.xModbusSlaveTaskV




void modbusSlaveHandler();
uint8_t modbusSlaveHardwareInit(void);
void modbusSlaveStartTransmitting(uint16_t bytesNum);
void modbusSlaveStartReceiving(void);

static uint8_t modbusSlaveCheckFrameSize(void);
static uint8_t modbusSlaveCheckID(void);
static uint8_t modbusSlaveCheckCRC(void);
static uint16_t modbusSlaveGetCRC(uint8_t * buffer, uint16_t len);
static uint16_t modbusSlaveErrorSet(uint8_t error);
static uint16_t modbusSlaveParseFrame(void);

void modbusSlaveStartTread(void)
{
    xTaskCreate(modbusSlaveHandler, "MBHandler", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xModbusSlaveTask);
}

xTaskHandle modbusSlaveGetTaskHandke(void)
{
    return xModbusSlaveTask;
}

void * modbusSlaveGetGata(uint16_t address)
{
    return (void*)&modbusMemory[address];
}

void modbusSlavePutData(uint16_t address, void * value, uint16_t len)
{
    memcpy(&modbusMemory[address], value, len);
}


void modbusSlaveHandler()
{
/*
   Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
   //Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;


   SytemCall_1(); //modbusSlaveHardwareInit();  // this only starts receiving data, the HW is initialized in

   // uint8_t firstRun=1;
   //cleanInitShadow();
   xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,2,1,eSetValueWithOverwrite); //notify the fuzzer task the target is ready
*/

 //  while(1)
  // {



       //ulTaskNotifyTake(pdTRUE, portMAX_DELAY); //wait for data coming from USART


       if(!modbusSlaveCheckFrameSize())
       {
           modbusSlaveStartReceiving();
           //continue;
           return;
       }
       if(!modbusSlaveCheckID())
       {
           modbusSlaveStartReceiving();
           //continue;
           return;
       }
       if(!modbusSlaveCheckCRC())
       {
           modbusSlaveStartReceiving();
           //continue;
           return;
       }
       //uint16_t answerLen =
       modbusSlaveParseFrame();
       modbusSlaveStartReceiving();

       //modbusSlaveStartTransmitting(answerLen);
    //}
}





void SytemCall_1_code()
{
	modbusSlaveHardwareInit();
}

uint8_t modbusSlaveHardwareInit(void)
{

	uint8_t status = 0;
	modbusRxCount = 0;

	HAL_UART_Abort(&huart4);
	HAL_UART_DeInit(&huart4);
	HAL_UART_Init(&huart4);


	while(HAL_UARTEx_ReceiveToIdle_DMA(&huart4, modbusRxTxBuffer, MODBUS_MAX_FRAME_SIZE) != HAL_OK)
	{
		  HAL_UART_DMAStop(&huart4);
	}

    status = 1;
    return status;
}


void SytemCall_2_code()
{
	while(HAL_UARTEx_ReceiveToIdle_DMA(&huart4, modbusRxTxBuffer, MODBUS_MAX_FRAME_SIZE) != HAL_OK)
	{
	 					HAL_UART_DMAStop(&huart4);
	}
}




void modbusSlaveStartReceiving(void)
{
	/*
     DMA1_Channel5->CNDTR = MODBUS_MAX_FRAME_SIZE;
     DMA1_Channel5->CCR |= DMA_CCR_EN;
     MODBUS_SLAVE_USART->CR1 |= USART_CR1_RTOIE;
     */


     SytemCall_2(); // configures serial por to recive data

     modbusRxCount = 0;


}




void modbusSlaveStartTransmitting(uint16_t bytesNum)
{
    /*
	DMA1_Channel4->CNDTR = bytesNum;
    DMA1_Channel4->CCR |= DMA_CCR_EN;
    */
	HAL_UART_Transmit_DMA(&huart4, modbusRxTxBuffer, bytesNum);
}

uint8_t modbusSlaveCheckFrameSize(void)
{
    if(modbusRxCount > MODBUS_MIN_FRAME_SIZE)
        return 1;
    return 0;
}

uint8_t modbusSlaveCheckID(void)
{
    if(modbusRxTxBuffer[0] == MODBUS_SLAVE_ADDRESS)
        return 1;
    return 0;
}

uint8_t modbusSlaveCheckCRC(void)
{
    uint16_t recievedCRC = modbusRxTxBuffer[modbusRxCount - 1] << 8 | modbusRxTxBuffer[modbusRxCount - 2];
    uint16_t calculatedCRC = modbusSlaveGetCRC(modbusRxTxBuffer, modbusRxCount - 2);
    if(recievedCRC == calculatedCRC)
        return 1;
    return 1;
}

uint16_t modbusSlaveGetCRC(uint8_t * buffer, uint16_t len)
{
	uint16_t crc = 0xFFFF;
	/*
	for (uint16_t pos = 0; pos < len; pos++)
	{
		crc ^= (uint16_t)buffer[pos];

		for (int i = 8; i != 0; i--)
		{
			if ((crc & 0x0001) != 0)
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else
				crc >>= 1;
		}
	}*/
	return crc;
}

uint16_t modbusSlaveErrorSet(uint8_t error)
{
    modbusRxTxBuffer[1] |= 0x80;
    modbusRxTxBuffer[2] = error;
    return MODBUS_MIN_FRAME_SIZE;
}

uint16_t modbusSlaveParseFrame(void)
{
    uint8_t command = modbusRxTxBuffer[1];
    uint16_t answerLen = 0;
    if(command == 0x03)
    {
        uint16_t startAddr = modbusRxTxBuffer[2] << 8 | modbusRxTxBuffer[3];
        uint16_t regNum = modbusRxTxBuffer[4] << 8 | modbusRxTxBuffer[5];
        if(((startAddr + regNum) > MODBUS_SLAVE_REGISTERS_NUM) || (regNum > 126))
            answerLen = modbusSlaveErrorSet(0x02);
        else
        {
            for(uint16_t reg = 0; reg < regNum; reg++)
            {
                modbusRxTxBuffer[3 + (reg << 1)] = (uint8_t)(modbusMemory[startAddr + reg] >> 8);
                modbusRxTxBuffer[4 + (reg << 1)] = (uint8_t)(modbusMemory[startAddr + reg]);
            }
            modbusRxTxBuffer[2] = regNum << 1;
            answerLen =  MODBUS_MIN_FRAME_SIZE + modbusRxTxBuffer[2];
        }
    }
    else if (command == 0x06)
    {
        uint16_t startAddr = modbusRxTxBuffer[2] << 8 | modbusRxTxBuffer[3];
        if(startAddr > MODBUS_SLAVE_REGISTERS_NUM)
            answerLen = modbusSlaveErrorSet(0x02);
        else
        {
            modbusMemory[startAddr] = modbusRxTxBuffer[4] << 8 | modbusRxTxBuffer[5];
            answerLen = modbusRxCount;
        }
    }
    else if(command == 0x10)
    {
        uint16_t startAddr = modbusRxTxBuffer[2] << 8 | modbusRxTxBuffer[3];
        uint16_t regNum = modbusRxTxBuffer[4] << 8 | modbusRxTxBuffer[5];
        if(((startAddr + regNum) > MODBUS_SLAVE_REGISTERS_NUM) || (regNum > 126))
            answerLen = modbusSlaveErrorSet(0x02);
        else
        {
            for(uint16_t reg = 0; reg < regNum; reg++)
            {
                modbusMemory[startAddr + reg] = modbusRxTxBuffer[7 + (reg << 1)] << 8 | modbusRxTxBuffer[8 + (reg << 1)];
            }
            answerLen = 8;
        }
    }
    else
    {
        answerLen = modbusSlaveErrorSet(0x01);
    }
    uint16_t crc = modbusSlaveGetCRC(modbusRxTxBuffer, answerLen - 2);
    modbusRxTxBuffer[answerLen - 2] = crc;
    modbusRxTxBuffer[answerLen - 1] = crc >> 8;
    return answerLen;
}





