/*
 * adc.h
 *
 *  Created on: Jan 6, 2023
 *      Author: hp
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../commons/std_types.h"

void ADC_init(void);

Uint16_t ADC_read(Uint8_t channel);



#endif /* MCAL_ADC_ADC_H_ */
