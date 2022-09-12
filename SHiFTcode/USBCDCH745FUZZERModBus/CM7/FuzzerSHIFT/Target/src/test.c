/*
 * TestModbus.c
 *
 *  Created on: Sep 17, 2021
 *      Author: alejandro
 */


#include "test.h"
#include "stdbool.h"
#include "stdio.h"
#include "main.h"
#include "afl.h"
#include <McuASAN.h>

uint8_t ModbusH_Region[next_power_of_2(modbusHandle_size) ] __attribute__( ( aligned( next_power_of_2(modbusHandle_size) ) ) );
//uint8_t Dummy_Region[16 * 1024] __attribute__( ( aligned( next_power_of_2(16 * 1024) ) ) );
uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );

typedef union {
	uint8_t  u8[4];
	uint16_t u16[2];
	uint32_t u32;
} bytesFields ;



/**
 * @struct modbus_t
 * @brief
 * Master query structure:
 * This includes all the necessary fields to make the Master generate a Modbus query.
 * A Master may keep several of these structures and send them cyclically or
 * use them according to program needs.
 */

enum
{
    RESPONSE_SIZE = 6,
    EXCEPTION_SIZE = 3,
    CHECKSUM_SIZE = 2
};



/**
 * @enum MESSAGE
 * @brief
 * Indexes to telegram frame positions
 */
enum MESSAGE
{
    ID                             = 0, //!< ID field
    FUNC, //!< Function code position
    ADD_HI, //!< Address high byte
    ADD_LO, //!< Address low byte
    NB_HI, //!< Number of coils or registers high byte
    NB_LO, //!< Number of coils or registers low byte
    BYTE_CNT  //!< byte counter
};

/**
 * @enum MB_FC
 * @brief
 * Modbus function codes summary.
 * These are the implement function codes either for Master or for Slave.
 *
 * @see also fctsupported
 * @see also modbus_t
 */
enum MB_FC
{
    MB_FC_NONE                     = 0,   /*!< null operator */
    MB_FC_READ_COILS               = 1,	/*!< FCT=1 -> read coils or digital outputs */
    MB_FC_READ_DISCRETE_INPUT      = 2,	/*!< FCT=2 -> read digital inputs */
    MB_FC_READ_REGISTERS           = 3,	/*!< FCT=3 -> read registers or analog outputs */
    MB_FC_READ_INPUT_REGISTER      = 4,	/*!< FCT=4 -> read analog inputs */
    MB_FC_WRITE_COIL               = 5,	/*!< FCT=5 -> write single coil or output */
    MB_FC_WRITE_REGISTER           = 6,	/*!< FCT=6 -> write single register */
    // the payload of these two cmd can be as long as 255 bytes(259B in total)
    MB_FC_WRITE_MULTIPLE_COILS     = 15,	/*!< FCT=15 -> write multiple coils or outputs */
    MB_FC_WRITE_MULTIPLE_REGISTERS = 16	/*!< FCT=16 -> write multiple registers */
};


enum COM_STATES
{
    COM_IDLE                     = 0,
    COM_WAITING                  = 1

};

enum ERR_LIST
{
    ERR_NOT_MASTER                = -1,
    ERR_POLLING                   = -2,
    ERR_BUFF_OVERFLOW             = -3,
    ERR_BAD_CRC                   = -4,
    ERR_EXCEPTION                 = -5
};

enum
{
    NO_REPLY = 255,
    EXC_FUNC_CODE = 1,
    EXC_ADDR_RANGE = 2,
    EXC_REGS_QUANT = 3,
    EXC_EXECUTE = 4
};






//extern UART_HandleTypeDef huart3;

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

#define lowByte(w) ((w) & 0xff)
#define highByte(w) ((w) >> 8)






 int8_t getRxBuffer(uint8_t *au8BufferIn, uint8_t bufferlen );
 uint16_t calcCRC(uint8_t u8length);
 uint8_t validateAnswer();
 uint8_t validateRequest();
 void get_FC1();
 void get_FC3();
 int8_t process_FC1( uint16_t *regs, uint8_t u8size );
 int8_t process_FC3( uint16_t *regs, uint8_t u8size );
 int8_t process_FC5( uint16_t *regs, uint8_t u8size );
 int8_t process_FC6( uint16_t *regs, uint8_t u8size );
 int8_t process_FC15( uint16_t *regs, uint8_t u8size );
 int8_t process_FC16( uint16_t *regs, uint8_t u8size );
 void buildException( uint8_t u8exception ); // build exception message
 uint16_t word(uint8_t H, uint8_t L);


 ;


 uint16_t word(uint8_t H, uint8_t L)
 {
 	bytesFields W;
 	W.u8[0] = L;
 	W.u8[1] = H;

 	return W.u16[0];
 }



 void sendTxBuffer()
 {

	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     // append CRC to message
     uint16_t u16crc = calcCRC( ModbusH->u8BufferSize );
     ModbusH->au8Buffer[ ModbusH->u8BufferSize ] = u16crc >> 8;
     ModbusH->u8BufferSize++;
     ModbusH->au8Buffer[ ModbusH->u8BufferSize ] = u16crc & 0x00ff;
     ModbusH->u8BufferSize++;


     //port->write( au8Buffer, u8BufferSize );
     //HAL_UART_Transmit(&huart3, ModbusH->au8Buffer, ModbusH->u8BufferSize, 100);

     ModbusH->u8BufferSize = 0;

     // set time-out for master
     //u32timeOut = millis() + (unsigned long) u16timeOut;

     // increase message counter
     ModbusH->u16OutCnt++;
 }




 int8_t getRxBuffer(uint8_t *au8BufferIn, uint8_t bufferlen )
 {

	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     if (bufferlen >= MAX_BUFFER)
     {

    	 ModbusH->u16errCnt++;
         return ERR_BUFF_OVERFLOW;
     }



     for (ModbusH->u8BufferSize = 0; ModbusH->u8BufferSize < bufferlen; ModbusH->u8BufferSize++)
     {
    	 ModbusH->au8Buffer[ ModbusH->u8BufferSize ] = au8BufferIn[ModbusH->u8BufferSize];

     }

     ModbusH->u16InCnt++;


     return ModbusH->u8BufferSize;
 }


 void buildException( uint8_t u8exception )
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t *)ModbusH_Region;
     uint8_t u8func = ModbusH->au8Buffer[ FUNC ];  // get the original FUNC code

     ModbusH->au8Buffer[ ID ]      = ModbusH->u8id;
     ModbusH->au8Buffer[ FUNC ]    = u8func + 0x80;
     ModbusH->au8Buffer[ 2 ]       = u8exception;
     ModbusH->u8BufferSize         = EXCEPTION_SIZE;
 }


 uint16_t calcCRC(uint8_t u8length)
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     unsigned int temp, temp2, flag;
     temp = 0xFFFF;
     for (unsigned char i = 0; i < u8length; i++)
     {
         temp = temp ^ ModbusH->au8Buffer[i];
         for (unsigned char j = 1; j <= 8; j++)
         {
             flag = temp & 0x0001;
             temp >>=1;
             if (flag)
                 temp ^= 0xA001;
         }
     }
     // Reverse byte order.
     temp2 = temp >> 8;
     temp = (temp << 8) | temp2;
     temp &= 0xFFFF;
     // the returned value is already swapped
     // crcLo byte is first & crcHi byte is last
     return temp;
 }


 uint8_t validateRequest()
 {
     // check message crc vs calculated crc
     // The assumption that last 2 bytes in the frame are CRC doesn't hold during fuzzing
	 modbusHandler_t* ModbusH = (modbusHandler_t *)ModbusH_Region;
     uint16_t u16MsgCRC =
         ((ModbusH->au8Buffer[ModbusH->u8BufferSize - 2] << 8)
          | ModbusH->au8Buffer[ModbusH->u8BufferSize - 1]); // combine the crc Low & High bytes

     //if ( calcCRC( ModbusH->u8BufferSize-2 ) != u16MsgCRC ) // the fuzzer will not past this control
     //{
     //  ModbusH->u16errCnt ++;
         //return NO_REPLY; // we dont't return even if CRC fails to help the fuzzer
     //}


     // check fct code
     bool isSupported = false;
     for (uint8_t i = 0; i< sizeof( ModbusH->fctsupported ); i++)
     {
         if (ModbusH->fctsupported[i] == ModbusH->au8Buffer[FUNC])
         {
             isSupported = 1;
             break;
         }
     }
     if (!isSupported)
     {
    	 ModbusH->u16errCnt ++;
         //printf("Wrong function Code!\n");
         return EXC_FUNC_CODE;
     }

     // check start address & nb range
     uint16_t u16regs = 0;
     uint8_t u8regs;
     switch ( ModbusH->au8Buffer[ FUNC ] )
     {
     case MB_FC_READ_COILS:
     case MB_FC_READ_DISCRETE_INPUT:
     case MB_FC_WRITE_MULTIPLE_COILS:
         u16regs = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ]) / 16;
         u16regs += word( ModbusH->au8Buffer[ NB_HI ], ModbusH->au8Buffer[ NB_LO ]) /16;
         u8regs = (uint8_t) u16regs;
         if (u8regs > ModbusH->u8regsize)
         {
        	 //printf("EXC_ADDR_RANGE!\n");
        	 return EXC_ADDR_RANGE;
         }

         break;
     case MB_FC_WRITE_COIL:
         u16regs = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ]) / 16;
         u8regs = (uint8_t) u16regs;
         if (u8regs > ModbusH->u8regsize)
         {
        	 //printf("EXC_ADDR_RANGE!\n");
        	 return EXC_ADDR_RANGE;
         }
         break;
     case MB_FC_WRITE_REGISTER :
         u16regs = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ]);
         u8regs = (uint8_t) u16regs;
         if (u8regs > ModbusH->u8regsize)
         {
           	 //printf("EXC_ADDR_RANGE!\n");
           	 return EXC_ADDR_RANGE;
         }
         break;
     case MB_FC_READ_REGISTERS :
     case MB_FC_READ_INPUT_REGISTER :
     case MB_FC_WRITE_MULTIPLE_REGISTERS :
         u16regs = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ]);
         u16regs += word( ModbusH->au8Buffer[ NB_HI ], ModbusH->au8Buffer[ NB_LO ]);
         u8regs = (uint8_t) u16regs;
         if (u8regs > ModbusH->u8regsize)
         {
           	 //printf("EXC_ADDR_RANGE!\n");
           	 return EXC_ADDR_RANGE;
         }
         break;
     }
     return 0; // OK, no exception code thrown
 }




 /**
  * @brief
  * This method processes functions 1 & 2
  * This method reads a bit array and transfers it to the master
  *
  * @return u8BufferSize Response to master length
  * @ingroup discrete
  */
 int8_t process_FC1( uint16_t *regs, uint8_t u8size )
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     uint8_t u8currentRegister, u8currentBit, u8bytesno, u8bitsno;
     //uint8_t u8CopyBufferSize;
     uint16_t u16currentCoil, u16coil;

     // get the first and last coil from the message
     uint16_t u16StartCoil = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ] );
     uint16_t u16Coilno = word( ModbusH->au8Buffer[ NB_HI ], ModbusH->au8Buffer[ NB_LO ] );

     // put the number of bytes in the outcoming message
     u8bytesno = (uint8_t) (u16Coilno / 8);
     if (u16Coilno % 8 != 0) u8bytesno ++;
     ModbusH->au8Buffer[ ADD_HI ]  = u8bytesno;
     ModbusH->u8BufferSize         = ADD_LO;

     // read each coil from the register map and put its value inside the outcoming message
     u8bitsno = 0;

     for (u16currentCoil = 0; u16currentCoil < u16Coilno; u16currentCoil++)
     {
         u16coil = u16StartCoil + u16currentCoil;
         // 16 bits per register
         u8currentRegister = (uint8_t) (u16coil / 16);
         u8currentBit = (uint8_t) (u16coil % 16);

         bitWrite(
        	 ModbusH->au8Buffer[ ModbusH->u8BufferSize ],
             u8bitsno,
             // out of bound read can happen here
             bitRead( regs[ u8currentRegister ], u8currentBit ) );
         u8bitsno ++;

         if (u8bitsno > 7)
         {
             u8bitsno = 0;
             ModbusH->u8BufferSize++;
         }
     }

     // send outcoming message
     // TODO seems not necessary, verify it!
     if (u16Coilno % 8 != 0) ModbusH->u8BufferSize ++;
     //u8CopyBufferSize = u8BufferSize +2;
     //printf("%s\n",__func__);
     sendTxBuffer();
     return FAULT_NONE;
 }

 /**
  * @brief
  * This method processes functions 3 & 4
  * This method reads a word array and transfers it to the master
  *
  * @return u8BufferSize Response to master length
  * @ingroup register
  */
 int8_t process_FC3( uint16_t *regs, uint8_t u8size )
 {

	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     uint8_t u8StartAdd = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ] );
     uint8_t u8regsno = word( ModbusH->au8Buffer[ NB_HI ], ModbusH->au8Buffer[ NB_LO ] );
     //uint8_t u8CopyBufferSize;
     uint8_t i;

     ModbusH->au8Buffer[ 2 ]       = u8regsno * 2;
     ModbusH->u8BufferSize         = 3;

     for (i = u8StartAdd; i < u8StartAdd + u8regsno; i++)
     {
    	 ModbusH->au8Buffer[ ModbusH->u8BufferSize ] = highByte(regs[i]);
    	 ModbusH->u8BufferSize++;
         ModbusH->au8Buffer[ ModbusH->u8BufferSize ] = lowByte(regs[i]);
         ModbusH->u8BufferSize++;
     }
     //u8CopyBufferSize = u8BufferSize +2;

     //printf("%s\n",__func__);
     sendTxBuffer();

     return FAULT_NONE;
 }

 /**
  * @brief
  * This method processes function 5
  * This method writes a value assigned by the master to a single bit
  *
  * @return u8BufferSize Response to master length
  * @ingroup discrete
  */
 int8_t process_FC5( uint16_t *regs, uint8_t u8size )
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     uint8_t u8currentRegister, u8currentBit;
     //uint8_t u8CopyBufferSize;
     uint16_t u16coil = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ] );

     // point to the register and its bit
     u8currentRegister = (uint8_t) (u16coil / 16);
     u8currentBit = (uint8_t) (u16coil % 16);

     // write to coil
     bitWrite(
         regs[ u8currentRegister ],
         u8currentBit,
		 ModbusH->au8Buffer[ NB_HI ] == 0xff );

     // send answer to master
     ModbusH->u8BufferSize = 6;
     //u8CopyBufferSize = u8BufferSize +2;

     //printf("%s\n",__func__);
     sendTxBuffer();

     return FAULT_NONE;
 }

 /**
  * @brief
  * This method processes function 6
  * This method writes a value assigned by the master to a single word
  *
  * @return u8BufferSize Response to master length
  * @ingroup register
  */
 int8_t process_FC6( uint16_t *regs, uint8_t u8size )
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     uint8_t u8add = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ] );
     //uint8_t u8CopyBufferSize;
     uint16_t u16val = word( ModbusH->au8Buffer[ NB_HI ], ModbusH->au8Buffer[ NB_LO ] );

     regs[ u8add ] = u16val;

     // keep the same header
     ModbusH->u8BufferSize         = RESPONSE_SIZE;
     //u8CopyBufferSize = u8BufferSize +2;
     //printf("%s\n",__func__);
     sendTxBuffer();
     return FAULT_NONE;
 }

 /**
  * @brief
  * This method processes function 15
  * This method writes a bit array assigned by the master
  *
  * @return u8BufferSize Response to master length
  * @ingroup discrete
  */
 int8_t process_FC15( uint16_t *regs, uint8_t u8size )
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     uint8_t u8currentRegister, u8currentBit, u8frameByte, u8bitsno;
     //uint8_t u8CopyBufferSize;
     uint16_t u16currentCoil, u16coil;
     bool bTemp;

     // get the first and last coil from the message
     uint16_t u16StartCoil = word( ModbusH->au8Buffer[ ADD_HI ], ModbusH->au8Buffer[ ADD_LO ] );
     uint16_t u16Coilno = word( ModbusH->au8Buffer[ NB_HI ], ModbusH->au8Buffer[ NB_LO ] );


     // read each coil from the register map and put its value inside the outcoming message
     u8bitsno = 0;
     u8frameByte = 7;
     for (u16currentCoil = 0; u16currentCoil < u16Coilno; u16currentCoil++)
     {

         u16coil = u16StartCoil + u16currentCoil;
         u8currentRegister = (uint8_t) (u16coil / 16);
         u8currentBit = (uint8_t) (u16coil % 16);

         bTemp = bitRead(
        		 ModbusH->au8Buffer[ u8frameByte ],
                     u8bitsno );

         bitWrite(
             regs[ u8currentRegister ],
             u8currentBit,
             bTemp );

         u8bitsno ++;

         if (u8bitsno > 7)
         {
             u8bitsno = 0;
             u8frameByte++;
         }
     }

     // send outcoming message
     // it's just a copy of the incomping frame until 6th byte
     ModbusH->u8BufferSize         = 6;
     //u8CopyBufferSize = u8BufferSize +2;
     //printf("%s\n",__func__);
     sendTxBuffer();
     return FAULT_NONE;
 }

 /**
  * @brief
  * This method processes function 16
  * This method writes a word array assigned by the master
  *
  * @return u8BufferSize Response to master length
  * @ingroup register
  */
 int8_t process_FC16( uint16_t *regs, uint8_t u8size )
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;
     //uint8_t u8func = ModbusH->au8Buffer[ FUNC ];  // get the original FUNC code
     uint8_t u8StartAdd = ModbusH->au8Buffer[ ADD_HI ] << 8 | ModbusH->au8Buffer[ ADD_LO ];
     uint8_t u8regsno = ModbusH->au8Buffer[ NB_HI ] << 8 | ModbusH->au8Buffer[ NB_LO ];
     //uint8_t u8CopyBufferSize;
     uint8_t i;
     uint16_t temp;

     // build header
     ModbusH->au8Buffer[ NB_HI ]   = 0;
     ModbusH->au8Buffer[ NB_LO ]   = u8regsno;
     ModbusH->u8BufferSize         = RESPONSE_SIZE;

     // write registers
     for (i = 0; i < u8regsno; i++)
     {
         temp = word(
        		 ModbusH->au8Buffer[ (BYTE_CNT + 1) + i * 2 ],
				 ModbusH->au8Buffer[ (BYTE_CNT + 2) + i * 2 ]);

         regs[ u8StartAdd + i ] = temp;
     }
    // u8CopyBufferSize = u8BufferSize +2;

     //printf("%s\n",__func__);
     sendTxBuffer();

     return FAULT_NONE;
 }



 uint32_t modbusparsing(uint8_t *Buffer, uint8_t u8size )
 {
	 modbusHandler_t* ModbusH = (modbusHandler_t*)ModbusH_Region;

	 ModbusH->fctsupported[0] = MB_FC_READ_COILS;
	 ModbusH->fctsupported[1] = MB_FC_READ_DISCRETE_INPUT;
	 ModbusH->fctsupported[2] = MB_FC_READ_REGISTERS;
	 ModbusH->fctsupported[3] = MB_FC_READ_INPUT_REGISTER;
	 ModbusH->fctsupported[4] = MB_FC_WRITE_COIL;
	 ModbusH->fctsupported[5] = MB_FC_WRITE_REGISTER;
	 ModbusH->fctsupported[6] = MB_FC_WRITE_MULTIPLE_COILS;
	 ModbusH->fctsupported[7] = MB_FC_WRITE_MULTIPLE_REGISTERS;

	 int8_t i8state;
	 int8_t u8current;
	 u8current= u8size; // this is hacky way to update this variable
	 uint16_t *regs = ModbusH->u16regs;


	 if (u8current >= 8) {
         i8state = getRxBuffer(Buffer,  u8size);
         ModbusH->u8lastError = i8state;
         if(i8state == ERR_BUFF_OVERFLOW)
         {
        	 //printf("size too large!\n");
        	 return FAULT_NONE_RTOS;
         }
     } else {

    	 //printf("size too small!\n");
         return FAULT_NONE_RTOS;
     }

     // check slave id, omit bytes if doesn't match
     if (ModbusH->au8Buffer[ ID ] != ModbusH->u8id)
     {
    	 //printf("Wrong ID!\n");
    	 return FAULT_NONE_RTOS;
     }


     // validate message: CRC, FCT, address and size
     uint8_t u8exception = validateRequest();
     if (u8exception > 0)
     {
         if (u8exception != NO_REPLY)
         {
             buildException( u8exception );
             sendTxBuffer();
         }
         ModbusH->u8lastError = u8exception;
         //printf("Fail validation ID!\n");
         return FAULT_NONE_RTOS;
     }

     // this value is not used by slave
     //u32timeOut = millis() + long(u16timeOut);
     ModbusH->u8lastError = 0;

     // process message
     switch( ModbusH->au8Buffer[ FUNC ] )
     {
     case MB_FC_READ_COILS:
     case MB_FC_READ_DISCRETE_INPUT:
         return process_FC1( regs, u8size );
         break;
     case MB_FC_READ_INPUT_REGISTER:
     case MB_FC_READ_REGISTERS :
         return process_FC3( regs, u8size );
         break;
     case MB_FC_WRITE_COIL:
         return process_FC5( regs, u8size );
         break;
     case MB_FC_WRITE_REGISTER :
         return process_FC6( regs, u8size );
         break;
     case MB_FC_WRITE_MULTIPLE_COILS:
         return process_FC15( regs, u8size );
         break;
     case MB_FC_WRITE_MULTIPLE_REGISTERS :
         return process_FC16( regs, u8size );
         break;
     default:
         break;
     }
     return FAULT_NONE_RTOS;
 }

