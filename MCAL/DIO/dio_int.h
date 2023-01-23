/*
 * dio_int.h
 *
 *  Created on: Dec 16, 2022
 *      Author: Bassel Yasser
 */

#ifndef MCAL_DIO_INT_H_
#define MCAL_DIO_INT_H_
/*---------------------------------------------------------------MACROS----------------------------------------------------------------*/
/*
 * user macros used in 	DIO_u8SetPortDir
 * 						DIO_u8SetPortVal
 * */
#include "../../commons/std_types.h"

#define PORT_A	0
#define PORT_B	1
#define PORT_C	2
#define PORT_D	3

#define PIN_0	0
#define PIN_1	1
#define PIN_2	2
#define PIN_3	3
#define PIN_4	4
#define PIN_5	5
#define PIN_6	6
#define PIN_7	7

#define INPUT	0
#define OUTPUT	1

#define FULL_INPUT	0x00
#define FULL_OUTPUT	0xff

#define LOW		0
#define HIGH	1

#define PUE		1	// pull up enable

#define E_OK	0
#define E_NOK	1
/*-------------------------------------Macros end--------------------------------*/
/*-------------------------------------types-------------------------------------*/



/*----------------------------------functions prototype-----------------------------*/

/*
 * function:	 DIO_u8SetPortDir
 * description : func to set the full port direction
 * input param :
 * 					u8PortIdCopy -> port ID from(PORT_A : PORT_D)
 * 					u8DirCopy	 -> the full port direction ex: 0xff "full o/p"
 * return:
 * 			E_OK  -> function has been executed successfully
 * 			E_NOK -> invalid input param
 * */
Uint8_t DIO_u8SetPortDir(Uint8_t u8PortIdCopy, Uint8_t u8DirCopy);
/*-------------------------------------------------------------------------------*/



/*
 * function:	 DIO_u8SetPortVal
 * description : func to set the full port value
 * input param :
 * 					u8PortIdCopy -> port ID from(PORT_A : PORT_D)
 * 					u8ValCopy	 -> the full port value (all ports are high or all ports are low) (LOW : HIGH)
 * return:
 * 			E_OK  -> function has been executed successfully
 * 			E_NOK -> invalid input param
 * */
Uint8_t DIO_u8SetPortVal(Uint8_t u8PortIdCopy, Uint8_t u8ValCopy);
/*-------------------------------------------------------------------------------*/




/*
 * function:	 DIO_u8GetPortVal
 * description : func to get the full port value
 * input param :
 * 					u8PortIdCopy -> port ID from(PORT_A : PORT_D)
 * 					u8pValRef	 -> to store the port value on it
 * return:
 * 			E_OK  -> function has been executed successfully
 * 			E_NOK -> invalid input param
 * */
Uint8_t DIO_u8GetPortVal(Uint8_t u8PortIdCopy, Uint8_t* u8pValRef);
/*-------------------------------------------------------------------------------*/




/*
 * function:	 DIO_u8SetPinDir
 * description : func to set Pin direction
 * input param :
 * 					u8PortIdCopy -> port ID from(PORT_A : PORT_D)
 * 					u8PinIdCopy	 -> Pin ID from (PIN_0 : PIN_7)
 * 					u8DirCopy    -> set pin direction (INPUT or OUTPUT)
 * return:
 * 			E_OK  -> function has been executed successfully
 * 			E_NOK -> invalid input param
 * */
Uint8_t DIO_u8SetPinDir(Uint8_t u8PortIdCopy, Uint8_t u8PinIdCopy ,Uint8_t u8DirCopy);
/*-------------------------------------------------------------------------------*/





/*
 * function:	 DIO_u8SetPinVal
 * description : func to set pin value
 * input param :
 * 					u8PortIdCopy -> port ID from(PORT_A : PORT_D)
 * 					u8PinIdCopy	 -> Pin ID from (PIN_0 : PIN_7)
 * 					u8ValCopy    -> set pin value (HIGH or LOW)
 * return:
 * 			E_OK  -> function has been executed successfully
 * 			E_NOK -> invalid input param
 * */
Uint8_t DIO_u8SetPinVal(Uint8_t u8PortIdCopy, Uint8_t u8PinIdCopy ,Uint8_t u8ValCopy);
/*-------------------------------------------------------------------------------*/




/*
 * function:	 DIO_u8GetPinVal
 * description : func to get Pin value
 * input param :
 * 					u8PortIdCopy -> port ID from(PORT_A : PORT_D)
 * 					u8PinIdCopy	 -> Pin ID from (PIN_0 : PIN_7)
 * 					u8pValRef    -> to store the pin value in it
 * return:
 * 			E_OK  -> function has been executed successfully
 * 			E_NOK -> invalid input param
 * */
Uint8_t DIO_u8GetPinVal(Uint8_t u8PortIdCopy, Uint8_t u8PinIdCopy ,Uint8_t* u8pValRef);
/*-------------------------------------------------------------------------------*/





#endif /* MCAL_DIO_INT_H_ */
