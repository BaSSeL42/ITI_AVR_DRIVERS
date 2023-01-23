/*
 * adc_v2.h
 *
 *  Created on: Jan 12, 2023
 *      Author: hp
 */

#ifndef MCAL_ADC_V2_ADC_V2_H_
#define MCAL_ADC_V2_ADC_V2_H_

/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/

#include "../../commons/std_types.h"

/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/

/* ADMUX reg */
#define MUX0		0
#define MUX1		1
#define MUX2		2
#define MUX3		3
#define MUX4		4
#define ADLAR		5
#define REFS0		6
#define REFS1		7

/* ADCSRA reg */
#define ADPS0		0
#define ADPS1		1
#define ADPS2		2
#define ADIE		3
#define ADIF		4
#define ADATE		5
#define ADSC		6
#define ADEN		7

/* SFIOR reg */
#define ADTS0		5
#define ADTS1		6
#define ADTS2		7

/* SREG reg */
#define I		7

/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/

typedef enum
{
	ADC_0=0,
	ADC_1,
	ADC_2,
	ADC_3,
	ADC_4,
	ADC_5,
	ADC_6,
	ADC_7,

	DIFF_ADC0_ADC0_10x,
	DIFF_ADC1_ADC0_10x,
	DIFF_ADC0_ADC0_200x,
	DIFF_ADC1_ADC0_200x,
	DIFF_ADC2_ADC2_10x,
	DIFF_ADC3_ADC2_10x,
	DIFF_ADC2_ADC2_200x,
	DIFF_ADC3_ADC2_200x,

	DIFF_ADC0_ADC1_1x,
	DIFF_ADC1_ADC1_1x,
	DIFF_ADC2_ADC1_1x,
	DIFF_ADC3_ADC1_1x,
	DIFF_ADC4_ADC1_1x,
	DIFF_ADC5_ADC1_1x,
	DIFF_ADC6_ADC1_1x,
	DIFF_ADC7_ADC1_1x,
	DIFF_ADC0_ADC2_1x,
	DIFF_ADC1_ADC2_1x,
	DIFF_ADC2_ADC2_1x,
	DIFF_ADC3_ADC2_1x,
	DIFF_ADC4_ADC2_1x,
	DIFF_ADC5_ADC2_1x,

	ADC_INVALID,

}enu_adcx_t;



typedef enum
{
	ADC_PRE_1=0,
	ADC_PRE_2,
	ADC_PRE_4,
	ADC_PRE_8,
	ADC_PRE_16,
	ADC_PRE_32,
	ADC_PRE_64,
	ADC_PRE_128,

	ADC_PRE_INVALID,

}enu_prescalar_t;


typedef enum
{
	ADC_OK=0,
	ADC_NOK

}enu_err_status_t;


typedef enum
{
	FREE_RUNNING=0,
	ANALOG_COMPARATOR,
	EXT_INTERRUPT_REQ_0,
	TIMER_0_CMP_MATCH,
	TIMER_0_OVF,
	TIMER_1_CMP_MATCH,
	TIMER_1_OVF,
	TIMER_1_CAPT_EVENT,

	TRIG_INVALID,

}enu_SFIOR_auto_trig_t;


typedef void(*ptr_func)(void);

/************************************************************************************************/
/*									FUNCTIONS PROTOTYPE											*/
/************************************************************************************************/

enu_err_status_t ADC_enuInit(enu_prescalar_t );

enu_err_status_t ADC_u8Read(enu_adcx_t, Uint16_t* );

enu_err_status_t ADC_u8AutoTrigRead(enu_adcx_t, enu_SFIOR_auto_trig_t ,Uint16_t* );

void vid_CallBackFunc(ptr_func);


#endif /* MCAL_ADC_V2_ADC_V2_H_ */
