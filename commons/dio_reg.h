/*
 * dio_reg.h
 *
 *  Created on: Dec 16, 2022
 *      Author: hp
 */

#ifndef COMMONS_DIO_REG_H_
#define COMMONS_DIO_REG_H_

#define PORTA_REG	((volatile Uint8_t*)(0x3B))
#define DDRA_REG	((volatile Uint8_t*)(0x3A))
#define PINA_REG	((volatile Uint8_t*)(0x39))

#define PORTB_REG	((volatile Uint8_t*)(0x38))
#define DDRB_REG	((volatile Uint8_t*)(0x37))
#define PINB_REG	((volatile Uint8_t*)(0x36))

#define PORTC_REG	((volatile Uint8_t*)(0x35))
#define DDRC_REG	((volatile Uint8_t*)(0x34))
#define PINC_REG	((volatile Uint8_t*)(0x33))

#define PORTD_REG	((volatile Uint8_t*)(0x32))
#define DDRD_REG	((volatile Uint8_t*)(0x31))
#define PIND_REG	((volatile Uint8_t*)(0x30))


#endif /* COMMONS_DIO_REG_H_ */
