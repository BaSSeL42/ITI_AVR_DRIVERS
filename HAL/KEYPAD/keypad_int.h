/*
 * keypad_int.h
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */

#ifndef HAL_KEYPAD_KEYPAD_INT_H_
#define HAL_KEYPAD_KEYPAD_INT_H_
#include "../../commons/std_types.h"
void KEYPAD_vidInit(void);
Uint8_t KEYPAD_u8GetPressed(void);

#endif /* HAL_KEYPAD_KEYPAD_INT_H_ */
