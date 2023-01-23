/*
 * adc_v2_src.c
 *
 *  Created on: Jan 12, 2023
 *      Author: hp
 */

#include <avr/interrupt.h>
#include "../../commons/Bit_Math.h"
#include "../../commons/MCU_ATMEGA32.h"
#include "adc_v2.h"
#include "adc_v2_cfg.h"

#define nullPtr 	(void*)0

ptr_func callBackFunc = nullPtr;

enu_err_status_t ADC_enuInit(enu_prescalar_t enu_prescalar)
{
	enu_err_status_t error_status = ADC_OK;

	if (enu_prescalar < ADC_PRE_INVALID)
	{
		SetBit(ADCSRA, ADEN);

		switch (enu_prescalar)
		{
			case ADC_PRE_1	: ClrBit(ADCSRA, ADPS0); ClrBit(ADCSRA, ADPS1); ClrBit(ADCSRA, ADPS2); break;
			case ADC_PRE_2	: SetBit(ADCSRA, ADPS0); ClrBit(ADCSRA, ADPS1); ClrBit(ADCSRA, ADPS2); break;
			case ADC_PRE_4	: ClrBit(ADCSRA, ADPS0); SetBit(ADCSRA, ADPS1); ClrBit(ADCSRA, ADPS2); break;
			case ADC_PRE_8	: SetBit(ADCSRA, ADPS0); SetBit(ADCSRA, ADPS1); ClrBit(ADCSRA, ADPS2); break;
			case ADC_PRE_16	: ClrBit(ADCSRA, ADPS0); ClrBit(ADCSRA, ADPS1); SetBit(ADCSRA, ADPS2); break;
			case ADC_PRE_32	: SetBit(ADCSRA, ADPS0); ClrBit(ADCSRA, ADPS1); SetBit(ADCSRA, ADPS2); break;
			case ADC_PRE_64	: ClrBit(ADCSRA, ADPS0); SetBit(ADCSRA, ADPS1); SetBit(ADCSRA, ADPS2); break;
			case ADC_PRE_128: SetBit(ADCSRA, ADPS0); SetBit(ADCSRA, ADPS1); SetBit(ADCSRA, ADPS2); break;
		}

#if ADC_VREF == ADC_VREF_5_V

		SetBit(ADMUX, REFS0);
		ClrBit(ADMUX, REFS1);

#elif ADC_VREF == ADC_VREF_2.32_V

		SetBit(ADMUX, REFS0);
		SetBit(ADMUX, REFS1);

#elif ADC_VREF == ADC_VREF_AREF

		ClrBit(ADMUX, REFS0);
		ClrBit(ADMUX, REFS1);
#else
#error "please enter valid ADC reference voltage"

#endif


#if ADC_DATA == ADC_DATA_LEFT_ADJUSTMENT

		ClrBit(ADMUX, ADLAR);

#elif ADC_DATA == ADC_DATA_RIGHT_ADJUSTMENT

		SetBit(ADMUX, ADLAR);

#else
#error "ADDATA adjustment is invalid"

#endif

	}
	else
	{
		error_status = ADC_NOK;
	}





	return error_status;

}




enu_err_status_t ADC_u8Read(enu_adcx_t enu_adcType, Uint16_t* pu16_adcVal)
{
	enu_err_status_t error_status = ADC_OK;

//	Uint16_t adc_u16Val;

	if (enu_adcType < ADC_INVALID && pu16_adcVal != nullPtr)
	{
		ADMUX &= 0b11100000;
		ADMUX |= enu_adcType;

		SetBit(ADCSRA, ADSC);  // single conversion

#if INTERRUPT == DISABLE_INTERRUPT

		/*
		 * wait till the conversion complete
		 */
		while(!GetBit(ADCSRA, ADIF));

		/*
		 * clear the ADIF
		 */
		ClrBit(ADCSRA, ADIF);

#elif INTERRUPT == ENABLE_INTERRUPT

		SetBit(ADCSRA, ADIE);
		SetBit(SREG, I);

#else

#warning "Invalid Interrupt"

#endif

#if ADC_DATA == ADC_DATA_LEFT_ADJUSTMENT

		*pu16_adcVal = (ADCH<<8) | ADCL;

#elif ADC_DATA == ADC_DATA_RIGHT_ADJUSTMENT

		*pu16_adcVal = ADCH | (ADCL >> 8);

#endif
	}
	else
	{
		error_status = ADC_NOK;
	}



	return error_status;
}




enu_err_status_t ADC_u8AutoTrigRead(enu_adcx_t enu_adcType, enu_SFIOR_auto_trig_t enu_autoTrig ,Uint16_t* pu16_adcVal)
{
	enu_err_status_t error_status = ADC_OK;

	if (enu_adcType < ADC_INVALID && enu_autoTrig < TRIG_INVALID && pu16_adcVal != nullPtr)
	{
		/*
		 * choosing ADC type (single mode or differential mode)
		 */
		ADMUX &= 0b11100000;
		ADMUX |= enu_adcType;

		/**
		 * enable auto trigger
		 */
		SetBit(ADCSRA, ADATE);
		/*
		 * set ADC Auto Trigger Source
		 */
		SFIOR &= 0b00011111;
		SFIOR |= (enu_autoTrig << 5);

#if INTERRUPT == DISABLE_INTERRUPT

		/*
		 * wait till the conversion complete
		 */
		while(!GetBit(ADCSRA, ADIF));

		/*
		 * clear the ADIF
		 */
		ClrBit(ADCSRA, ADIE);

#elif INTERRUPT == ENABLE_INTERRUPT

		SetBit(ADCSRA, ADIE);
		SetBit(SREG, I);

#else

#warning "Invalid Interrupt"

#endif

#if ADC_DATA == ADC_DATA_LEFT_ADJUSTMENT

		*pu16_adcVal = (ADCH<<8) | ADCL;

#elif ADC_DATA == ADC_DATA_RIGHT_ADJUSTMENT

		*pu16_adcVal = (ADCH<<8) | ADCL;

#endif
	}
	else
	{
		error_status = ADC_NOK;
	}




	return error_status;
}





void vid_CallBackFunc(ptr_func ptrFunc)
{
	callBackFunc = ptrFunc;
}


ISR(ADC_vect)
{
	callBackFunc();
}
