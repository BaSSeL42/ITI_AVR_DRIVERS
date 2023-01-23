///*
// * servo.c
// *
// *  Created on: Jan 20, 2023
// *      Author: hp
// */
//
//
//#include"../../commons/std_types.h"
#include "../../MCAL/TIMER/timer_int.h"
#include "servo.h"

#define Y 180

void servo_init(void)
{
	timer_1_init(T1_FAST_PWM_ICR1);
	enu_generateCustome_PWM(TIMER_PRE_8, T1_PWM_CLR_ON_CMP, 50);
}

void set_angle(Uint16_t angle){
//	Uint16_t u16_cmpVal = ((Y + angle)*100)/18;
	vid_PWM1_Generate(angle);

}
