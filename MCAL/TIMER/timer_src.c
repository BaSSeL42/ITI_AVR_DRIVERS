/*
 * timer_src.c
 *
 *  Created on: Jan 14, 2023
 *      Author: hp
 */

/****************************************************************************************************************/
/*									INCLUDES															*/
/****************************************************************************************************************/
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../../commons/MCU_ATMEGA32.h"
#include "../../commons/Bit_Math.h"
#include "../DIO/dio_v2.h"
#include "timer_int.h"
/****************************************************************************************************************/
/*									MACROS																*/
/****************************************************************************************************************/
#define FCPU		8000000UL
#define RESOLUTION	256
#define NULL (void*)0
/****************************************************************************************************************/
/*									GLOBAL_VARIALES																*/
/****************************************************************************************************************/
/* Variables for TIMER 0 */
ptrFunc Timer0_callBack = NULL;
//static Uint32_t staticGlobal_timerPrescalar;
Uint32_t gu32_number_of_ovf;
Uint32_t gu32_preload ;

/* Variables for TIMER 1 */
Uint32_t gu32_T1_number_of_ovf;
Uint32_t gu32_T1_preload ;
enu_timer1Mode_t gen_PwmMode = T1_MODE_INVALID;

 /* Variables for ISR */
volatile Uint16_t cap1, cap2,cap3;
volatile Uint32_t ovf_num = 0;
volatile Uint8_t mask = 0;


/****************************************************************************************************************/
/*									TIMER_0	 FUNCTION_IMPLEMENTATION											*/
/****************************************************************************************************************/
enu_timerStatus_t timer_0_init (enu_timerMode_t enuTimerMode)
{
	enu_timerStatus_t errorState = TIMER_OK;

	if (enuTimerMode < TIMER_MODE_INVALID )
	{
		switch (enuTimerMode)
		{
			case OVF_MODE 				:ClrBit(TCCR0, WGM01);ClrBit(TCCR0, WGM00); break;
			case PHASE_CORRECT_PWM_MODE :ClrBit(TCCR0, WGM01);SetBit(TCCR0, WGM00); break;
			case CTC_MODE 				:SetBit(TCCR0, WGM01);ClrBit(TCCR0, WGM00); break;
			case FAST_PWM_MODE 			:SetBit(TCCR0, WGM01);SetBit(TCCR0, WGM00); break;
			default 					: errorState = TIMER_NOK; break;
		}

		/* enable global interrupt */
//		SetBit(SREG, timer_I);
	}
	else
	{
		errorState = TIMER_NOK;
	}
	return errorState;
}




void set_ovf_timer0_ms(Uint32_t u32_delay_ms, enu_timerPrescalar_t enuTimerPre)
{
	Uint32_t local_timerPrescalar;
	if(enuTimerPre < TIMER_PRESCALR_INVALID)
	{
		switch (enuTimerPre)
		{
			case TIMER_NO_CLK_SRC			: ClrBit(TCCR0, CS02);ClrBit(TCCR0, CS01); ClrBit(TCCR0, CS00);break;
			case TIMER_PRE_1				: ClrBit(TCCR0, CS02);ClrBit(TCCR0, CS01); SetBit(TCCR0, CS00); local_timerPrescalar = 1; 		break;
			case TIMER_PRE_8				: ClrBit(TCCR0, CS02);SetBit(TCCR0, CS01); ClrBit(TCCR0, CS00); local_timerPrescalar = 8; 		break;
			case TIMER_PRE_64				: ClrBit(TCCR0, CS02);SetBit(TCCR0, CS01); SetBit(TCCR0, CS00); local_timerPrescalar = 64; 		break;
			case TIMER_PRE_256				: SetBit(TCCR0, CS02);ClrBit(TCCR0, CS01); ClrBit(TCCR0, CS00);	local_timerPrescalar = 256; 		break;
			case TIMER_PRE_1024				: SetBit(TCCR0, CS02);ClrBit(TCCR0, CS01); SetBit(TCCR0, CS00);	local_timerPrescalar = 1024; 	break;
			case TIMER_EXT_CLK_FALLING		: SetBit(TCCR0, CS02);SetBit(TCCR0, CS01); ClrBit(TCCR0, CS00);break;
			case TIMER_EXT_CLK_RISING		: SetBit(TCCR0, CS02);SetBit(TCCR0, CS01); SetBit(TCCR0, CS00);break;
			default 						:  break;
		}
			Uint8_t u8_tick_Time;
			Uint32_t u32_total_ticks;
			/* time on one tick */
			u8_tick_Time = (local_timerPrescalar * 1000000) / FCPU;  // 1024*1000000 / 8000000 = 128 us

			u32_total_ticks = (u32_delay_ms * 1000) / u8_tick_Time;

			gu32_number_of_ovf = u32_total_ticks / 256;

			gu32_preload = 256 - (u32_total_ticks % 256);

			TCNT0 = gu32_preload;

			gu32_number_of_ovf++;

			/*set interrupt*/
			SetBit(TIMSK, TOIE0);
			SetBit(SREG, timer_I);

		}else{
			/*
			 * do nothing
			 */
		}

	return ;
}



enu_timerStatus_t set_ctc_timer0_ms(enu_ctcMode_t en_ctcMode, Uint32_t u32_delay_ms,enu_timerPrescalar_t enuTimerPre)
{
	enu_timerStatus_t errStat = TIMER_OK;
	Uint8_t u8_tick_Time;
	Uint32_t local_timerPrescalar;
//	Uint32_t u32_total_tick;

	if(en_ctcMode < CTC_INVALID && enuTimerPre < TIMER_PRESCALR_INVALID)
	{
		switch (en_ctcMode)
		{
			case CTC_NORMAL			: ClrBit(TCCR0, COM01);ClrBit(TCCR0, COM00);   break;
			case CTC_TOGGLE_ON_CMP	: ClrBit(TCCR0, COM01);SetBit(TCCR0, COM00);   break;
			case CTC_CLR_ON_CMP		: SetBit(TCCR0, COM01);ClrBit(TCCR0, COM00);   break;
			case CTC_SET_ON_CMP		: SetBit(TCCR0, COM01);SetBit(TCCR0, COM00);   break;
			default: errStat = TIMER_NOK; break;
		}
		switch (enuTimerPre)
		{
			case TIMER_NO_CLK_SRC			: ClrBit(TCCR0, CS02);ClrBit(TCCR0, CS01); ClrBit(TCCR0, CS00);break;
			case TIMER_PRE_1				: ClrBit(TCCR0, CS02);ClrBit(TCCR0, CS01); SetBit(TCCR0, CS00); local_timerPrescalar = 1; 		break;
			case TIMER_PRE_8				: ClrBit(TCCR0, CS02);SetBit(TCCR0, CS01); ClrBit(TCCR0, CS00); local_timerPrescalar = 8; 		break;
			case TIMER_PRE_64				: ClrBit(TCCR0, CS02);SetBit(TCCR0, CS01); SetBit(TCCR0, CS00); local_timerPrescalar = 64; 		break;
			case TIMER_PRE_256				: SetBit(TCCR0, CS02);ClrBit(TCCR0, CS01); ClrBit(TCCR0, CS00);	local_timerPrescalar = 256; 		break;
			case TIMER_PRE_1024				: SetBit(TCCR0, CS02);ClrBit(TCCR0, CS01); SetBit(TCCR0, CS00);	local_timerPrescalar = 1024; 	break;
			case TIMER_EXT_CLK_FALLING		: SetBit(TCCR0, CS02);SetBit(TCCR0, CS01); ClrBit(TCCR0, CS00);break;
			case TIMER_EXT_CLK_RISING		: SetBit(TCCR0, CS02);SetBit(TCCR0, CS01); SetBit(TCCR0, CS00);break;
			default 						:  break;
		}

//		u8_tick_Time = (local_timerPrescalar * 1000000) / FCPU; // tick time on us
//		u32_total_tick = ();



		SetBit(TIMSK, OCIE0);
		SetBit(SREG, timer_I);
	}else
	{
		errStat = TIMER_NOK;
	}


	return errStat;

}





enu_timerStatus_t enu_FastPWM0_init(enu_pwmMode_t enPwmMode,enu_timerPrescalar_t enuTimerPre)
{
	enu_timerStatus_t errStatus = TIMER_OK;
	if(enPwmMode < PWM_INVALID && enuTimerPre < TIMER_PRESCALR_INVALID)
	{
		timer_0_init(FAST_PWM_MODE);
		TCNT0 = 0;
		DIO_s8SETPinDir(DIO_PINB_3, OUTPUT); // set portB pin 3 as output
		switch (enPwmMode)
		{
			case PWM_NORMAL		: ClrBit(TCCR0, COM01);ClrBit(TCCR0, COM00);   break;
			case PWM_CLR_ON_CMP	: SetBit(TCCR0, COM01);ClrBit(TCCR0, COM00);   break;
			case PWM_SET_ON_CMP	: SetBit(TCCR0, COM01);SetBit(TCCR0, COM00);   break;
			default: errStatus = TIMER_NOK;break;
		}
		switch (enuTimerPre)
		{
			case TIMER_NO_CLK_SRC			: ClrBit(TCCR0, CS02);ClrBit(TCCR0, CS01); ClrBit(TCCR0, CS00);break;
			case TIMER_PRE_1				: ClrBit(TCCR0, CS02);ClrBit(TCCR0, CS01); SetBit(TCCR0, CS00); 		break;
			case TIMER_PRE_8				: ClrBit(TCCR0, CS02);SetBit(TCCR0, CS01); ClrBit(TCCR0, CS00); 		break;
			case TIMER_PRE_64				: ClrBit(TCCR0, CS02);SetBit(TCCR0, CS01); SetBit(TCCR0, CS00); 		break;
			case TIMER_PRE_256				: SetBit(TCCR0, CS02);ClrBit(TCCR0, CS01); ClrBit(TCCR0, CS00); 		break;
			case TIMER_PRE_1024				: SetBit(TCCR0, CS02);ClrBit(TCCR0, CS01); SetBit(TCCR0, CS00); 	break;
			case TIMER_EXT_CLK_FALLING		: SetBit(TCCR0, CS02);SetBit(TCCR0, CS01); ClrBit(TCCR0, CS00);break;
			case TIMER_EXT_CLK_RISING		: SetBit(TCCR0, CS02);SetBit(TCCR0, CS01); SetBit(TCCR0, CS00);break;
			default 						:  break;
		}
	}
	else
	{
		errStatus = TIMER_NOK;
	}
	return errStatus;
}

void vid_PWM0_Generate(Uint8_t u8_DutyCycleVal)
{
	OCR0 = ((u8_DutyCycleVal * 256)/100)-1 ;
//	OCR0 = u8_DutyCycleVal;
}

void TimCallBackFunc(ptrFunc PtrFuncVal)
{
	Timer0_callBack = PtrFuncVal;
}

/****************************************************************************************************************/
/*									TIMER_1	 FUNCTION_IMPLEMENTATION											*/
/****************************************************************************************************************/
enu_timerStatus_t timer_1_init (enu_timer1Mode_t enTimMode)
{
	enu_timerStatus_t errState = TIMER_OK;
	if (enTimMode < T1_MODE_INVALID)
	{
		switch (enTimMode)
		{
			case T1_NORMAL_0xFFFF				: ClrBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); ClrBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); break;
			case T1_PWM_PHASE_CORRECT_8_0x00FF	: ClrBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); ClrBit(TCCR1A, WGM11); SetBit(TCCR1A, WGM10); break;
			case T1_PWM_PHASE_CORRECT_9_0x01FF	: ClrBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); break;
			case T1_PWM_PHASE_CORRECT_10_0x03FF	: ClrBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); SetBit(TCCR1A, WGM10); break;
			case T1_CTC_OCR1A					: ClrBit(TCCR1B, WGM13); SetBit(TCCR1B, WGM12); ClrBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); break;
			case T1_FAST_PWM_8_0x00FF			: ClrBit(TCCR1B, WGM13); SetBit(TCCR1B, WGM12); ClrBit(TCCR1A, WGM11); SetBit(TCCR1A, WGM10); gen_PwmMode =T1_FAST_PWM_8_0x00FF;  break;
			case T1_FAST_PWM_9_0x01FF			: ClrBit(TCCR1B, WGM13); SetBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); gen_PwmMode =T1_FAST_PWM_9_0x01FF;  break;
			case T1_FAST_PWM_10_0x03FF			: ClrBit(TCCR1B, WGM13); SetBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); SetBit(TCCR1A, WGM10); gen_PwmMode =T1_FAST_PWM_10_0x03FF; break;
			case T1_PWM_PHASE_FREQ_CORRECT_ICR1	: SetBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); ClrBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); break;
			case T1_PWM_PHASE_FREQ_CORRECT_OCR1A: SetBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); ClrBit(TCCR1A, WGM11); SetBit(TCCR1A, WGM10); break;
			case T1_PWM_PHASE_CORRECT_ICR1		: SetBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); break;
			case T1_PWM_PHASE_CORRECT_OCR1A		: SetBit(TCCR1B, WGM13); ClrBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); SetBit(TCCR1A, WGM10); break;
			case T1_CTC_ICR1					: SetBit(TCCR1B, WGM13); SetBit(TCCR1B, WGM12); ClrBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); break;
			case T1_FAST_PWM_ICR1				: SetBit(TCCR1B, WGM13); SetBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); ClrBit(TCCR1A, WGM10); gen_PwmMode =T1_FAST_PWM_ICR1;  break;
			case T1_FAST_PWM_OCR1A				: SetBit(TCCR1B, WGM13); SetBit(TCCR1B, WGM12); SetBit(TCCR1A, WGM11); SetBit(TCCR1A, WGM10); break;
			default: break;
		}
	}else
	{
		errState =TIMER_NOK;
	}
	return errState;
}



enu_timerStatus_t enu_ovf1_delay_ms(enu_timerPrescalar_t en_T1Prescalar, Uint32_t u32_delay_ms)
{
	enu_timerStatus_t errState = TIMER_OK;
	Uint32_t local_timer1Prescalar;
	Uint8_t u8_tick_Time;
	Uint32_t u32_total_ticks;

	if (en_T1Prescalar < TIMER_PRESCALR_INVALID)
	{
		switch (en_T1Prescalar)
		{
			case TIMER_NO_CLK_SRC			: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_PRE_1				: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10); local_timer1Prescalar = 1   ;break;
			case TIMER_PRE_8				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10); local_timer1Prescalar = 8   ;break;
			case TIMER_PRE_64				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10); local_timer1Prescalar = 64  ;break;
			case TIMER_PRE_256				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10); local_timer1Prescalar = 256 ;break;
			case TIMER_PRE_1024				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10); local_timer1Prescalar = 1024;break;
			case TIMER_EXT_CLK_FALLING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_EXT_CLK_RISING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			default 						:  break;
		}
		/* time on one tick */
		u8_tick_Time = (Uint8_t)((local_timer1Prescalar * 1000000) / FCPU);  // 1024*1000000 / 8000000 = 128 us
		u32_total_ticks = (u32_delay_ms * 1000) / u8_tick_Time;
		gu32_T1_number_of_ovf = u32_total_ticks / 65536;
		gu32_T1_preload = 65536 - (u32_total_ticks % 65536);
		TCNT1 = (Uint16_t)gu32_preload;

		gu32_T1_number_of_ovf++;

		/*set interrupt*/
		SetBit(TIMSK, TOIE1);
		SetBit(SREG, timer_I);
	}else {
		errState = TIMER_NOK;
	}
	return errState;
}



enu_timerStatus_t enu_icrInit(enu_timerPrescalar_t en_T1Prescalar, enu_icrMode_t en_icr_mode)
{
	enu_timerStatus_t errState = TIMER_OK;
//	if (en_T1Prescalar < TIMER_PRESCALR_INVALID && en_icr_mode < ICR_INVALID)
//	{
		cli();
		DIO_s8SETPinDir(DIO_PIND_6, INPUT); // set ICR pin as input
		timer_1_init(T1_NORMAL_0xFFFF);
		TCNT1 = 0;
		switch (en_T1Prescalar)
		{
			case TIMER_NO_CLK_SRC			: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_PRE_1				: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			case TIMER_PRE_8				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_PRE_64				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			case TIMER_PRE_256				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_PRE_1024				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			case TIMER_EXT_CLK_FALLING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_EXT_CLK_RISING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			default 						:  break;
		}
		switch (en_icr_mode)
		{
				case ICR_FALLING_EDGE	: ClrBit(TCCR1B, ICES1); break;
				case ICR_RISING_EDGE	: SetBit(TCCR1B, ICES1); break;
			default: break;
		}
		/*set interrupt*/
		SetBit(TIMSK, TOIE0) ;
		SetBit(TIMSK, TICIE1);
		SetBit(SREG, timer_I);
//		sei();
//	}else {
//		errState = TIMER_NOK;
//	}
	return errState;
}


void vid_icrGetVal(Uint16_t* pu16_valAddr)
{
//	sei();
	if(pu16_valAddr != NULL)
	{
		if(mask == 1)
		{
			mask = 0;

			*pu16_valAddr = 2008;
			mask = 0;

			ovf_num=0;

			SetBit(TIMSK, TOIE0); // enable ovf0 interrupt
			SetBit(TIMSK, TICIE1); // enable ICR interrupt

			SetBit(TCCR1B, ICES1); // set to rising edge

		}
	}

}



enu_timerStatus_t enu_FastPWM1_init(enu_pwm1Mode_t en_pwmMode,enu_timerPrescalar_t en_T1Prescalar)
{
	enu_timerStatus_t errState = TIMER_OK;
	if (en_pwmMode < T1_PWM_INVALID && en_T1Prescalar < TIMER_PRESCALR_INVALID)
	{
		TCNT1 = 0;
		DIO_s8SETPinDir(DIO_PIND_5, OUTPUT); // set portB pin 3 as output
		switch (en_pwmMode)
		{
			case T1_PWM_NORMAL				: ClrBit(TCCR1A, COM1A1);ClrBit(TCCR1A, COM1A0);   break;
			case T1_PWM_TOGGLE_ON_CMP		: ClrBit(TCCR1A, COM1A1);SetBit(TCCR1A, COM1A0);   break;
			case T1_PWM_CLR_ON_CMP			: SetBit(TCCR1A, COM1A1);ClrBit(TCCR1A, COM1A0);   break;
			case T1_PWM_SET_ON_CMP			: SetBit(TCCR1A, COM1A1);SetBit(TCCR1A, COM1A0);   break;
			default:break;
		}
		switch (en_T1Prescalar)
		{
			case TIMER_NO_CLK_SRC			: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_PRE_1				: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			case TIMER_PRE_8				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_PRE_64				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			case TIMER_PRE_256				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_PRE_1024				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			case TIMER_EXT_CLK_FALLING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
			case TIMER_EXT_CLK_RISING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
			default 						:  break;
		}
	}else{
		 errState = TIMER_NOK;
	}

	return errState;
}




enu_timerStatus_t enu_generateCustome_PWM(enu_timerPrescalar_t en_T1Prescalar, enu_pwm1Mode_t en_pwmMode, Uint16_t u16_custFreq)
{
	enu_timerStatus_t errState = TIMER_OK;
	Uint16_t local_u16Prescalar , local_u16TopVal;

	if (gen_PwmMode == T1_FAST_PWM_ICR1)
	{
		if (en_pwmMode < T1_PWM_INVALID && en_T1Prescalar < TIMER_PRESCALR_INVALID)
		{
			TCNT1 = 0;
			DIO_s8SETPinDir(DIO_PIND_5, OUTPUT); // set portB pin 3 as output
			switch (en_pwmMode)
			{
				case T1_PWM_NORMAL				: ClrBit(TCCR1A, COM1A1);ClrBit(TCCR1A, COM1A0);   break;
				case T1_PWM_TOGGLE_ON_CMP		: ClrBit(TCCR1A, COM1A1);SetBit(TCCR1A, COM1A0);   break;
				case T1_PWM_CLR_ON_CMP			: SetBit(TCCR1A, COM1A1);ClrBit(TCCR1A, COM1A0);   break;
				case T1_PWM_SET_ON_CMP			: SetBit(TCCR1A, COM1A1);SetBit(TCCR1A, COM1A0);   break;
				default:break;
			}
			switch (en_T1Prescalar)
			{
				case TIMER_NO_CLK_SRC			: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
				case TIMER_PRE_1				: ClrBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10); local_u16Prescalar = 1; break;
				case TIMER_PRE_8				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10); local_u16Prescalar = 8; break;
				case TIMER_PRE_64				: ClrBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10); local_u16Prescalar = 64; break;
				case TIMER_PRE_256				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10); local_u16Prescalar = 256; break;
				case TIMER_PRE_1024				: SetBit(TCCR1B, CS12);ClrBit(TCCR1B, CS11); SetBit(TCCR1B, CS10); local_u16Prescalar = 1024; break;
				case TIMER_EXT_CLK_FALLING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); ClrBit(TCCR1B, CS10);break;
				case TIMER_EXT_CLK_RISING		: SetBit(TCCR1B, CS12);SetBit(TCCR1B, CS11); SetBit(TCCR1B, CS10);break;
				default 						:  break;
			}

			local_u16TopVal = ( FCPU/(local_u16Prescalar * u16_custFreq)) - 1;
			ICR1 = local_u16TopVal;
		}else{
			 errState = TIMER_NOK;
		}
	}

	return errState;

}



void vid_PWM1_Generate(Uint16_t u16_duty)
{

	if(gen_PwmMode == T1_FAST_PWM_8_0x00FF)
	{
		OCR1A = ((u16_duty * 256)/100)-1 ;
	}
	else if(gen_PwmMode == T1_FAST_PWM_9_0x01FF)
	{
		OCR1A = ((u16_duty * 512)/100)-1 ;
	}
	else if(gen_PwmMode == T1_FAST_PWM_10_0x03FF)
	{
		OCR1A = ((u16_duty * 1024)/100)-1 ;
	}
	else if (gen_PwmMode == T1_FAST_PWM_ICR1)
	{
		OCR1A = u16_duty;
	}
	else
	{
		/*
			 * do nothing
		 */
	}
}
/***********************************************************************/













/***********************************************************************************************************************************/
/*		INTERRUPT SERVICE ROUTINE		*/
/***********************************************************************************************************************************/

//ISR (TIMER0_OVF_vect)
//{
//	static Uint32_t counter = 0;
//	counter ++;
//
//	if (counter == gu32_number_of_ovf)
//	{
//		TCNT0 = gu32_preload;
//		counter = 0;
//		Timer0_callBack();
//	}
//}

//ISR (TIMER0_OVF_vect)
//{
//	ovf_num++;
//}



//ISR (TIMER0_COMP_vect)
//{
//	static Uint32_t counter = 0;
//	counter++;
//	if(counter == 40)
//	{
//
//		Timer0_callBack();
//		counter = 0;
//	}
//
//}


ISR(TIMER1_OVF_vect)
{
	ovf_num++;
}


ISR(TIMER1_CAPT_vect)
{
	if (mask == 0)
	{
		cap1 = ICR1;
		ovf_num = 0;
		ClrBit(TCCR1B, ICES1); // icr sense falling edge
	}
	else if(mask == 1)
	{
		cap2 = ICR1 + (65536*ovf_num) - cap1;  // value of T_on
		SetBit(TCCR1B, ICES1);		//// icr sense rising edge
//		ovf_num = 0;
	}
	else if(mask == 2)
	{
		cap3 = ICR1 + (65536*ovf_num) - cap1;

		ClrBit(TIMSK, TOIE1); // disable
		ClrBit(TIMSK, TICIE1);
	}
	mask++;
}








//void watchDog()
//{
//	DDRA = 0x01;
//	PORTA = 0x01;
//	_delay_ms(1000);
//	PORTA = 0x00;
//	/*
//	 * select WDT prescallar (time out = 2.1 sec)
//	 */
//	WDTCR |= (1<<0) | (1<<1) | (1<<2)
//
//		/*
//		 * enable WDE
//		 */
//	WDTCR |= (1<<WDE);
//
//	while(1)
//	{
////		__asm__("wdr"); // reset watchdog timer in assembly instruction by software instead of hardware
//
//		WDTCR |= (1<<WDTOE);
////		WDTCR &= ~(1<<WDE); // take more than 4 cycles
////		WDTCR = 0b00000111;
//		*((volatile char*)0x41) = 0b00000111;
//		WDTCR |= (1<<WDE) | (1<<0) | (1<<1) | (1<<2);
//
//		_delay_ms(3000); // set delay more than 2.1 sec
//	}
//}

