/*
 * ext_int_cfg.h
 *
 *  Created on: Dec 30, 2022
 *      Author: hp
 */

#ifndef MCAL_EXT_INT_EXT_INT_CFG_H_
#define MCAL_EXT_INT_EXT_INT_CFG_H_


/************************************************************************************************/
/*									MACROS									*/
/************************************************************************************************/

/***************  To CHOOSE TYPE OF INTERRUPTS FOR CALLING ISR  ***************/
#define INTERRUPT_0		0
#define INTERRUPT_1		1
#define INTERRUPT_2		2
#define MY_CHOICE		INTERRUPT_0


/****************  To CHOOSE WHICH PINS FOR INT0, INT1 & INT2---> EXTERNAL_INTERRUPTS  ****************/
#define EXT_INT0		DIO_PIND_2
#define EXT_INT1		DIO_PIND_3
#define EXT_INT2		DIO_PINB_2




#endif /* MCAL_EXT_INT_EXT_INT_CFG_H_ */
