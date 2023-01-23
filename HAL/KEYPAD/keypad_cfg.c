/*
 * keypad_cfg.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */

#include "../../commons/std_types.h"
#include "../../MCAL/DIO/dio_int.h"
#include "KEYPAD_cfg.h"





typedef struct {
	Uint8_t port;
	Uint8_t pin;
}keypad_pin;





Uint8_t KEYPAD_au8KeyVal[KEYPAD_NO_ROW][KEYPAD_NO_COL] = {
		{
				1,  //ROW 0 COL 0
				2,	//ROW 0 COL 1
				3,  //ROW 0 COL 2
				4   //ROW 0 COL 3
		},
		{
				5,  //ROW 1 COL 0
				6,	//ROW 1 COL 1
				7,  //ROW 1 COL 2
				8   //ROW 1 COL 3
		},
		{
				9,   //ROW 2 COL 0
				10,	 //ROW 2 COL 1
				11,  //ROW 2 COL 2
				12   //ROW 2 COL 3
		},
		{
				13,  //ROW 3 COL 0
				14,	 //ROW 3 COL 1
				15,  //ROW 3 COL 2
				16   //ROW 3 COL 3
		}
};





keypad_pin KEYPAD_au8RowPins[KEYPAD_NO_ROW + KEYPAD_NO_COL] =
{
		{//R0
				PORT_D,
				PIN_4
		},
		{//R1
				PORT_D,
				PIN_5
		},
		{//R2
				PORT_D,
				PIN_6
		},
		{//R3
				PORT_D,
				PIN_7
		}
};


keypad_pin KEYPAD_au8ColPins[KEYPAD_NO_ROW + KEYPAD_NO_COL] =
{
		{//C0
				PORT_D,
				PIN_0
		},
		{//C1
				PORT_D,
				PIN_1
		},
		{//C2
				PORT_D,
				PIN_2
		},
		{//C3
				PORT_D,
				PIN_3
		}
};







