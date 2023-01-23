/*
 * timer_int.h
 *
 *  Created on: Jan 14, 2023
 *      Author: hp
 */

#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#include "../../commons/std_types.h"


/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/
/* TCCRO REG */
#define CS00		0
#define CS01		1
#define CS02		2
#define WGM01		3
#define COM00		4
#define COM01		5
#define WGM00		6
#define FOC0		7

/* TIMSK REG */
#define TOIE0		0
#define OCIE0		1
#define TOIE1		2
#define OCIE1A		3
#define OCIE1B		4
#define TICIE1		5
#define TOIE2		6
#define OCIE2		7

/* TIFR REG */
#define TOV0		0
#define OCF0		1
#define TOV1		2
#define OCF1A		3
#define OCF1B		4
#define ICF1		5
#define TOV2		6
#define OCF2		7


/* TCCR1A REG */
#define WGM10		0
#define WGM11		1
#define FOC1B		2
#define FOC1A		3
#define COM1B0		4
#define COM1B1		5
#define COM1A0		6
#define COM1A1		7

/* TCCR1B REG */
#define CS10		0
#define CS11		1
#define CS12		2
#define WGM12		3
#define WGM13		4
#define ICES1		6
#define ICNC1		7

/* SREG REG */
#define timer_I		7

/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
typedef enum
{
	TIMER_OK,
	TIMER_NOK,

}enu_timerStatus_t;


/********************************/
/*	 TIMER 0 & TIMER 2			*/
/********************************/
typedef enum
{
	OVF_MODE,
	PHASE_CORRECT_PWM_MODE,
	CTC_MODE,
	FAST_PWM_MODE,

	TIMER_MODE_INVALID,

}enu_timerMode_t;



typedef enum
{
	TIMER_NO_CLK_SRC,
	TIMER_PRE_1,
	TIMER_PRE_8,
	TIMER_PRE_64,
	TIMER_PRE_128,
	TIMER_PRE_256,
	TIMER_PRE_1024,
	TIMER_EXT_CLK_FALLING,
	TIMER_EXT_CLK_RISING,

	TIMER_PRESCALR_INVALID,


}enu_timerPrescalar_t;



typedef enum
{
	CTC_NORMAL=0,
	CTC_TOGGLE_ON_CMP,
	CTC_CLR_ON_CMP,
	CTC_SET_ON_CMP,
	CTC_INVALID,

}enu_ctcMode_t;

typedef enum
{
	PWM_NORMAL=0,
	PWM_CLR_ON_CMP,
	PWM_SET_ON_CMP,
	PWM_INVALID,

}enu_pwmMode_t;


/********************************/
/*	 TIMER 1			*/
/********************************/

typedef enum
{
	T1_NORMAL_0xFFFF,

	T1_PWM_PHASE_CORRECT_8_0x00FF,
	T1_PWM_PHASE_CORRECT_9_0x01FF,
	T1_PWM_PHASE_CORRECT_10_0x03FF,

	T1_CTC_OCR1A,

	T1_FAST_PWM_8_0x00FF,
	T1_FAST_PWM_9_0x01FF,
	T1_FAST_PWM_10_0x03FF,

	T1_PWM_PHASE_FREQ_CORRECT_ICR1,
	T1_PWM_PHASE_FREQ_CORRECT_OCR1A,

	T1_PWM_PHASE_CORRECT_ICR1,
	T1_PWM_PHASE_CORRECT_OCR1A,

	T1_CTC_ICR1,

	T1_FAST_PWM_ICR1,
	T1_FAST_PWM_OCR1A,

	T1_MODE_INVALID,


}enu_timer1Mode_t;


typedef enum
{
	T1_PWM_NORMAL=0,
	T1_PWM_TOGGLE_ON_CMP,
	T1_PWM_CLR_ON_CMP,
	T1_PWM_SET_ON_CMP,
	T1_PWM_INVALID,

}enu_pwm1Mode_t;


typedef enum
{
	ICR_FALLING_EDGE,
	ICR_RISING_EDGE,
	ICR_INVALID,

}enu_icrMode_t;

typedef void (*ptrFunc)(void);



/************************************************************************************************/
/*									FUNCTIONS PROTOTYPE											*/
/************************************************************************************************/
enu_timerStatus_t timer_0_init (enu_timerMode_t);
enu_timerStatus_t timer_2_init (enu_timerMode_t , enu_timerPrescalar_t );


void set_ovf_timer0_ms(Uint32_t, enu_timerPrescalar_t);
enu_timerStatus_t set_ctc_timer0_ms(enu_ctcMode_t , Uint32_t ,enu_timerPrescalar_t );

enu_timerStatus_t enu_FastPWM0_init(enu_pwmMode_t ,enu_timerPrescalar_t );
void vid_PWM0_Generate(Uint8_t);
void set_phase_correct_pwm_timer0(enu_pwmMode_t);

/***********************************************************************/


//void setTimerCMP0 (Uint32_t );
//void setTimerCMP0(Uint32_t timeVal)
//{
//	// Ftimer = 8000000 / 1024 = 7812.5 HZ
//	// 1 / 7812.5 = 128 us
//	// 2^8 = 256  ----> 0~255
//	// 128 us * 256 = 32768 us
//	//
//	Float32_t noOfOVF = (Float32_t)(timeVal * 1000000) / 25000; // 40
//	OVFNo = 25000 / 128;
//
//	TCNT0 = 0;
//	OCR0 = OVFNo;
//
//	SetBit(TIMSK, OCIE0);
//	SetBit(SREG, 7);
//}

/***********************************************************************/


/***********************/
/*TIMER 1*/
/**********************/
enu_timerStatus_t timer_1_init (enu_timer1Mode_t );
enu_timerStatus_t enu_ovf1_delay_ms(enu_timerPrescalar_t , Uint32_t);

enu_timerStatus_t enu_icrInit(enu_timerPrescalar_t, enu_icrMode_t);
void vid_icrGetVal(Uint16_t*);

enu_timerStatus_t enu_FastPWM1_init(enu_pwm1Mode_t ,enu_timerPrescalar_t );
enu_timerStatus_t enu_generateCustome_PWM(enu_timerPrescalar_t, enu_pwm1Mode_t, Uint16_t );
void vid_PWM1_Generate(Uint16_t);



/***********************************************************************/
/*
 * call back function
 */
void TimCallBackFunc(ptrFunc );

#endif /* MCAL_TIMER_TIMER_INT_H_ */
