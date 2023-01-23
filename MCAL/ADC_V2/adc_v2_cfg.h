/*
 * adc_v2_cfg.h
 *
 *  Created on: Jan 12, 2023
 *      Author: hp
 */

#ifndef MCAL_ADC_V2_ADC_V2_CFG_H_
#define MCAL_ADC_V2_ADC_V2_CFG_H_

/*
 * configure reference voltage
 */
#define ADC_VREF_5_V			0
#define ADC_VREF_2.32_V			1
#define ADC_VREF_AREF			2
#define ADC_VREF				ADC_VREF_5_V


/*
 * configuring ADC data
 */
#define ADC_DATA_RIGHT_ADJUSTMENT		4
#define ADC_DATA_LEFT_ADJUSTMENT		5
#define ADC_DATA						ADC_DATA_LEFT_ADJUSTMENT

/*
 * Set Interrupt
 */
#define ENABLE_INTERRUPT			0
#define DISABLE_INTERRUPT			1
#define INTERRUPT					DISABLE_INTERRUPT

#endif /* MCAL_ADC_V2_ADC_V2_CFG_H_ */
