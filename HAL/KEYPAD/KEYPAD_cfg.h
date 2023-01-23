/*
 * KEYPAD_cfg.h
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */

#ifndef HAL_KEYPAD_KEYPAD_CFG_H_
#define HAL_KEYPAD_KEYPAD_CFG_H_

#define POLLING				1
#define PERIODIC			2


#define KEYPAD_PORT			PORT_D

#define KEYPAD_COL_START	PIN_0
#define KEYPAD_COL_END		PIN_3

#define KEYPAD_ROW_START	PIN_4
#define KEYPAD_ROW_END		PIN_7



#define KEYPAD_NO_COL		4
#define KEYPAD_NO_ROW		4

#define NO_KEY_PRESSED		0


#define KEYPAD_MODE			POLLING

extern Uint8_t KEYPAD_au8KeyVal[KEYPAD_NO_ROW][KEYPAD_NO_COL];





#endif /* HAL_KEYPAD_KEYPAD_CFG_H_ */
