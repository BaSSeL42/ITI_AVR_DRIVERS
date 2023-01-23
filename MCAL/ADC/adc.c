/*
 * adc.c
 *
 *  Created on: Jan 6, 2023
 *      Author: hp
 */

#include "../../commons/Bit_Math.h"
#include "adc.h"
#include "avr/io.h"

#define CLR_MASK		0b11100000

void ADC_init(void)
{
	/*
	 * Enable ADC
	 */

	SetBit(ADCSRA, ADEN);

	/*
	 * Select pre_scalar = 64 --> 125kHZ
	 */
	ClrBit(ADCSRA, ADPS0);
	SetBit(ADCSRA, ADPS1);
	SetBit(ADCSRA, ADPS2);

	/*
	 * select vref  as AVCC
	 */
	SetBit(ADMUX, REFS0);
	ClrBit(ADMUX, REFS1);

	/*
	 * select resolution
	 */

	ClrBit(ADMUX, ADLAR);


}

Uint16_t ADC_read(Uint8_t channel)
{
	Uint16_t local_u16ADCValue;
	/*
	 * Select channel
	 */
	ADMUX &= CLR_MASK;  // clear mask
	ADMUX |= channel;	  // set mask
	/*
	 * start single conversion
	 */

	SetBit(ADCSRA, ADSC);  // single conversion

	/*
	 * wait till the conversion complete
	 */
	while(!GetBit(ADCSRA, ADIF));

	/*
	 * clear the ADIF
	 */
	SetBit(ADCSRA, ADIF);

	/*
	 * read ADC o/p value
	 */
	local_u16ADCValue = (ADCH << 8) | ADCL; // *((volatile uint16* )0x24) if ADCL & ADCH under each other on memory

	return local_u16ADCValue;
}

