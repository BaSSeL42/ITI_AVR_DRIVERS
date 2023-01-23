#ifndef MCU_H_
#define MCU_H_

/********************************* DIO REGISTERS ******************************************/

#define PORTA	(*(volatile Uint8_t*)(0x3B))
#define DDRA	(*(volatile Uint8_t*)(0x3A))
#define PINA	(*(volatile Uint8_t*)(0x39))

#define PORTB	(*(volatile Uint8_t*)(0x38))
#define DDRB	(*(volatile Uint8_t*)(0x37))
#define PINB	(*(volatile Uint8_t*)(0x36))

#define PORTC	(*(volatile Uint8_t*)(0x35))
#define DDRC	(*(volatile Uint8_t*)(0x34))
#define PINC	(*(volatile Uint8_t*)(0x33))

#define PORTD	(*(volatile Uint8_t*)(0x32))
#define DDRD	(*(volatile Uint8_t*)(0x31))
#define PIND	(*(volatile Uint8_t*)(0x30))

/********************************* EXTERNAL INTERRUPTS REGISTERS ******************************************/

#define MCUCR	(*(volatile Uint8_t*)(0x55))
#define MCUCSR	(*(volatile Uint8_t*)(0x54))
#define GICR	(*(volatile Uint8_t*)(0x5B))
#define GIFR	(*(volatile Uint8_t*)(0x5A))

#define SREG 	(*(volatile Uint8_t*)(0x5A)) // for global interrupt

/********************************* ADC REGISTERS ******************************************/

#define SFIOR	(*(volatile Uint8_t*)(0x50)) // for auto triggering ADC
#define ADMUX 	(*(volatile Uint8_t*)(0x27))
#define ADCSRA 	(*(volatile Uint8_t*)(0x26))
#define ADCH 	(*(volatile Uint8_t*)(0x25))
#define ADCL 	(*(volatile Uint8_t*)(0x24))


/********************************* TIMER0 REGISTERS ******************************************/
#define TCCR0 	(*(volatile Uint8_t*)(0x53))
#define TCNT0 	(*(volatile Uint8_t*)(0x52))
#define OCR0 	(*(volatile Uint8_t*)(0x5C))

/********************************* TIMER1 REGISTERS ******************************************/
#define TCCR1A 	(*(volatile Uint8_t*)(0x4F))
#define TCCR1B 	(*(volatile Uint8_t*)(0x4E))
#define TCNT1H 	(*(volatile Uint8_t*)(0x4D))
#define TCNT1L 	(*(volatile Uint8_t*)(0x4C))
#define TCNT1 	(*(volatile Uint16_t*)(0x4C))
#define OCR1AH 	(*(volatile Uint8_t*)(0x4B))
#define OCR1AL 	(*(volatile Uint8_t*)(0x4A))
#define OCR1A 	(*(volatile Uint16_t*)(0x4A))

#define OCR1BH 	(*(volatile Uint8_t*)(0x49))
#define OCR1BL 	(*(volatile Uint8_t*)(0x48))
#define ICR1H 	(*(volatile Uint8_t*)(0x47))
#define ICR1L 	(*(volatile Uint8_t*)(0x46))
#define ICR1 	(*(volatile Uint16_t*)(0x46))

/********************************* TIMER2 REGISTERS ******************************************/
#define TCCR2 	(*(volatile Uint8_t*)(0x45))
#define TCNT2 	(*(volatile Uint8_t*)(0x44))
#define OCR2 	(*(volatile Uint8_t*)(0x43))

/********************************* TIMER_ALL REGISTERS ******************************************/
#define TIFR 	(*(volatile Uint8_t*)(0x58))
#define TIMSK 	(*(volatile Uint8_t*)(0x59))

/********************************* WATCHDOG_TIMER REGISTERS ******************************************/
#define WDTCR 	(*(volatile Uint8_t*)(0x41))
#endif /*MCU_H_*/
