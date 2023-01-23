/*
 * keypad_src.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */
#include <util/delay.h>
#include "../../commons/Bit_Math.h"
#include "../../commons/std_types.h"
#include "../../MCAL/DIO/dio_int.h"

#include "KEYPAD_cfg.h"


void KEYPAD_vidInit(void)
{
	DIO_u8SetPortDir(KEYPAD_PORT,0b00001111);
	DIO_u8SetPortVal(KEYPAD_PORT,0b11111111);
}


Uint8_t KEYPAD_u8GetPressed(void)
{
	Uint8_t local_u8KeyPressed = NO_KEY_PRESSED; //---------------
	Uint8_t local_u8RowStatus;
	Uint8_t local_u8Row;
	Uint8_t local_u8Col;

	for(local_u8Col = KEYPAD_COL_START ;local_u8Col <= KEYPAD_COL_END ;local_u8Col++ ) //col
	{
		DIO_u8SetPinVal(KEYPAD_PORT,local_u8Col, LOW ); //activate col
		// DIO_u8SetPinVal(KEYPAD_au8ColPins[local_u8Col].port, KEYPAD_au8ColPins[local_u8Col].pin, LOW )

		for(local_u8Row = KEYPAD_ROW_START ;local_u8Row <= KEYPAD_ROW_END ;local_u8Row++) //row
		{
			// check status of current row
			// DIO_u8GetPinVal(KEYPAD_au8RowPins[local_u8Row].port, KEYPAD_au8RowPins[local_u8Row].pin, LOW )
			DIO_u8GetPinVal(KEYPAD_PORT, local_u8Row, &local_u8RowStatus);

			if (local_u8RowStatus == 0) // if pressed
			{
//				local_u8KeyPressed = ((local_u8Row- KEYPAD_ROW_START)*4) + local_u8Col; // (6-4)*4+1 = 9

				local_u8KeyPressed = KEYPAD_au8KeyVal[local_u8Row - KEYPAD_ROW_START][local_u8Col - KEYPAD_COL_START ];

				//wait until the key is released
#if KEYPAD_MODE == POLLING
				while(local_u8RowStatus == 0)
				{
					DIO_u8GetPinVal(KEYPAD_PORT, local_u8Row, &local_u8RowStatus);
				}
#elif KEYPAD_MODE == PERIODIC

				_delay_ms(20);
				DIO_u8GetPinVal(KEYPAD_PORT, local_u8Row, &local_u8RowStatus);
				if (local_u8RowStatus == 0)
				{
					local_u8KeyPressed = KEYPAD_au8KeyVal[local_u8Row - KEYPAD_ROW_START][local_u8Col - KEYPAD_COL_START ];
				}
#endif
				_delay_ms(20);
			}
		}
		DIO_u8SetPinVal(KEYPAD_PORT,local_u8Col, HIGH ); //deactivate col
	}

	return local_u8KeyPressed;
}
