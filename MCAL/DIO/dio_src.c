/*
 * dio_src.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Bassel Yasser
 */


#include "../../commons/Bit_Math.h"
#include "../../commons/MCU_ATMEGA32.h"
#include "dio_int.h"


Uint8_t DIO_u8SetPortDir(Uint8_t u8PortIdCopy, Uint8_t u8DirCopy)
{
	Uint8_t errStatus = E_OK;
	switch(u8PortIdCopy)
	{
		case PORT_A : PORTA = u8DirCopy; break;
		case PORT_B : PORTB = u8DirCopy; break;
		case PORT_C : PORTC = u8DirCopy; break;
		case PORT_D : PORTD = u8DirCopy; break;
		default: errStatus = E_NOK;
	}
	return errStatus;
}


Uint8_t DIO_u8SetPortVal(Uint8_t u8PortIdCopy, Uint8_t u8ValCopy)
{
	Uint8_t errStatus = E_OK;
	switch(u8PortIdCopy)
	{
		case PORT_A : PORTA = u8ValCopy; break;
		case PORT_B : PORTB = u8ValCopy; break;
		case PORT_C : PORTC = u8ValCopy; break;
		case PORT_D : PORTD = u8ValCopy; break;
		default: errStatus = E_NOK;
	}
	return errStatus;
}


Uint8_t DIO_u8GetPortVal(Uint8_t u8PortIdCopy, Uint8_t* u8pValRef)
{
	Uint8_t errStatus = E_OK;
	switch(u8PortIdCopy)
	{
		case PORT_A : *u8pValRef = PINA; break;
		case PORT_B : *u8pValRef = PINB; break;
		case PORT_C : *u8pValRef = PINC; break;
		case PORT_D : *u8pValRef = PIND; break;
		default: errStatus = E_NOK;
	}
	return errStatus;
}



Uint8_t DIO_u8SetPinDir(Uint8_t u8PortIdCopy, Uint8_t u8PinIdCopy ,Uint8_t u8DirCopy)
{
	Uint8_t errStatus = E_OK;
	if (u8PinIdCopy >= PIN_0 && u8PinIdCopy <= PIN_7)
	{
		if (u8DirCopy == INPUT)
		{
			switch(u8PortIdCopy)
			{
				case PORT_A : ClrBit(DDRA,u8PinIdCopy); break;
				case PORT_B : ClrBit(DDRB,u8PinIdCopy); break;
				case PORT_C : ClrBit(DDRC,u8PinIdCopy); break;
				case PORT_D : ClrBit(DDRD,u8PinIdCopy); break;
				default: errStatus = E_NOK;
			}
		}
		else if(u8DirCopy == OUTPUT)
		{
			switch(u8PortIdCopy)
			{
				case PORT_A : SetBit(DDRA,u8PinIdCopy); break;
				case PORT_B : SetBit(DDRB,u8PinIdCopy); break;
				case PORT_C : SetBit(DDRC,u8PinIdCopy); break;
				case PORT_D : SetBit(DDRD,u8PinIdCopy); break;
				default: errStatus = E_NOK;
			}
		}
		else
		{
			errStatus = E_NOK;
		}
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}


Uint8_t DIO_u8SetPinVal(Uint8_t u8PortIdCopy, Uint8_t u8PinIdCopy ,Uint8_t u8ValCopy)
{
	Uint8_t errStatus = E_OK;
	if (u8PinIdCopy >= PIN_0 && u8PinIdCopy <= PIN_7)
	{
		if (u8ValCopy == LOW)
		{
			switch(u8PortIdCopy)
			{
				case PORT_A : ClrBit(PORTA,u8PinIdCopy); break;
				case PORT_B : ClrBit(PORTB,u8PinIdCopy); break;
				case PORT_C : ClrBit(PORTC,u8PinIdCopy); break;
				case PORT_D : ClrBit(PORTD,u8PinIdCopy); break;
				default: errStatus = E_NOK;
			}
		}
		else if(u8ValCopy == HIGH)
		{
			switch(u8PortIdCopy)
			{
				case PORT_A : SetBit(PORTA,u8PinIdCopy); break;
				case PORT_B : SetBit(PORTB,u8PinIdCopy); break;
				case PORT_C : SetBit(PORTC,u8PinIdCopy); break;
				case PORT_D : SetBit(PORTD,u8PinIdCopy); break;
				default: errStatus = E_NOK;
			}
		}
		else
		{
			errStatus = E_NOK;
		}
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}




Uint8_t DIO_u8GetPinVal(Uint8_t u8PortIdCopy, Uint8_t u8PinIdCopy ,Uint8_t* u8pValRef)
{
	Uint8_t errStatus = E_OK;
	if (u8PinIdCopy >= PIN_0 && u8PinIdCopy <= PIN_7)
	{
		switch(u8PortIdCopy)
		{
			case PORT_A : *u8pValRef = GetBit(PINA,u8PinIdCopy); break;
			case PORT_B : *u8pValRef = GetBit(PINB,u8PinIdCopy); break;
			case PORT_C : *u8pValRef = GetBit(PINC,u8PinIdCopy); break;
			case PORT_D : *u8pValRef = GetBit(PIND,u8PinIdCopy); break;
			default: errStatus = E_NOK;
		}
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}

