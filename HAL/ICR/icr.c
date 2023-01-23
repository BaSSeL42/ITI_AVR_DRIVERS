///*
// * icr.c
// *
// *  Created on: Jan 20, 2023
// *      Author: hp
// */
//
//
//
//#include <avr/io.h>
//#include"../../commons/Bit_Math.h"
//#include"../../commons/std_types.h"
//#include "icr.h"
//#include <avr/interrupt.h>
//
//volatile Uint16_t cap1,cap2;
//volatile Uint32_t ovf_num = 0;
//volatile Uint8_t mask = 0;
//
//void icrInit(void)
//{
//	sei(); // clear all global interrupt
//
//	SetBit(DDRD, 6);
//	TCNT1 = 0;
//	TCCR1A |= 0; // normal mode
//
//	SetBit(TCCR1B, ICES1); // icr sense rising edge
//	SetBit(TCCR1B, CS10); // prescalar is set to one
//
//
//	SetBit(TIMSK, TOIE1); 	// enable overflow interrupt
//	SetBit(TIMSK, TICIE1); 	// enable icr interrupt
//
//	SetBit(SREG, 7); // enable global interrupt
//
//}
//
//
//
//Uint32_t valueInICR(void)
//{
//	Uint32_t value;
//
//	if (mask == 2)
//	{
//		mask = 0;
//
//		value = (Uint32_t)(cap2 + (65536*ovf_num) - cap1);
//		ovf_num = 0;
//	}
//
//
//	return value;
//}
//
//
//
//ISR(TIMER1_OVF_vect)
//{
//	ovf_num++;
//}
//
//
//ISR(TIMER1_CAPT_vect)
//{
//	if (mask == 0)
//	{
//		ICR1= 0;
////		cap1 = ICR1;
//		ClrBit(TCCR1B, ICES1); // icr sense falling edge
//		ovf_num = 0;
//
//	}
//	else if(mask == 1)
//	{
//		cap2 = ICR1;
////		ClrBit(TIMSK, TOIE1); // disable
////		ClrBit(TIMSK, TICIE1);
//
//	}
//	mask++;
//}
