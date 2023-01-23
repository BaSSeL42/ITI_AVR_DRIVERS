/*
 * ext_int.c
 *
 *  Created on: Dec 30, 2022
 *      Author: hp
 */

/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#include "../../MCAL/EXT_INT/ext_int.h"

#include <avr/interrupt.h>
#include "../../commons/MCU_ATMEGA32.h"
#include "../../commons/Bit_Math.h"

#include "../../MCAL/DIO/dio_v2.h"
#include "../../MCAL/EXT_INT/ext_int_cfg.h"

/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/
#define nullPtr		(void*)0

/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
ptr_func callBack = nullPtr;

/************************************************************************************************/
/*									FUNCTION_IMPLEMENTATION										*/
/************************************************************************************************/
Uint8_t vidExtInt_init(enu_int_type_t enIntType, enu_sns_ctrl_t enSensControl)
{
	Uint8_t err_status = E_INT_OK;
	if(enIntType < INT_TYPE_INVALID && enSensControl < SENS_CONTROL_INVALID)
	{
		if (enIntType == INT_0)
		{
			DIO_s8SETPinVal(EXT_INT0, HIGH);
			switch (enSensControl)
			{
				case LOW_LEVEL 	: ClrBit(MCUCR, ISC00); ClrBit(MCUCR, ISC01); break;
				case ANY_LOGICAL: SetBit(MCUCR, ISC00); ClrBit(MCUCR, ISC01); break;
				case FALL_EDGE 	: ClrBit(MCUCR, ISC00); SetBit(MCUCR, ISC01); break;
				case RISE_EDGE 	: SetBit(MCUCR, ISC00); SetBit(MCUCR, ISC01); break;
				default : err_status = E_INT_NOK; break;
			}

			SetBit(GICR, INT0);
			SetBit(GIFR, INTF0);	// to clear flag for Interrupt 0
		}
		else if (enIntType == INT_1)
		{
			DIO_s8SETPinVal(EXT_INT1, HIGH);
			switch (enSensControl)
			{
				case LOW_LEVEL 	: ClrBit(MCUCR, ISC10); ClrBit(MCUCR, ISC11); break;
				case ANY_LOGICAL: SetBit(MCUCR, ISC10); ClrBit(MCUCR, ISC11); break;
				case FALL_EDGE 	: ClrBit(MCUCR, ISC10); SetBit(MCUCR, ISC11); break;
				case RISE_EDGE 	: SetBit(MCUCR, ISC10); SetBit(MCUCR, ISC11); break;
				default : err_status = E_INT_NOK; break;
			}
			SetBit(GICR, INT1);
			SetBit(GIFR, INTF1);	// to clear flag for Interrupt 1
		}
		else if (enIntType == INT_2)
		{
			DIO_s8SETPinVal(EXT_INT2, HIGH);
			switch (enSensControl)
			{
				case FALL_EDGE 	: ClrBit(MCUCSR, ISC2);  break;
				case RISE_EDGE 	: SetBit(MCUCSR, ISC2);  break;
				default : err_status = E_INT_NOK; break;
			}
			SetBit(GICR, INT2);
			SetBit(GIFR, INTF2);  // to clear flag for Interrupt 2
		}
	}
	else
	{
		err_status = E_INT_NOK;
	}

	SetBit(SREG, I); // enable global interrupt


	return err_status;
}



void vidCallBackFunc(ptr_func funcCopy)
{
	callBack = funcCopy;
}




//void add()
//{
//
//}
//
//void sum()
//{
//
//}
//
//extern void vector_1 (void);
//void _vector_1()
//{
//
//}

/************************************************************************************************/
/*									CALLING_ISR													*/
/************************************************************************************************/
#if (MY_CHOICE == INTERRUPT_0)

//void(*ptrFunc[3])(void) = {
//		_vector_1,
//		sum,
//};

//void vector_1 (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__;
//void vector_1 (void)
ISR(INT0_vect)
{
	callBack();
}

#elif (MY_CHOICE == INTERRUPT_1)

ISR(INT1_vect)
{
	callBack();
}

#elif (MY_CHOICE == INTERRUPT_2)

ISR(INT2_vect)
{
	callBack();
}


#else

#error "choose valid interrupt 0 or 1 or 2"


#endif

