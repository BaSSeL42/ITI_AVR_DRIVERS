/*
 * lcd_src.c
 *
 *  Created on: Dec 17, 2022
 *      Author: hp
 */


/**************************************************************************************************
 * library includes
 *************************************************************************************************/
#include <stdlib.h>
#include "../../MCAL/DIO/dio_v2.h"
#include "util/delay.h"
//#include "lcd_int.h"
#include "lcd_cfg.h"
#include "string.h"
/**************************************************************************************************
 * macros
 *************************************************************************************************/
#define LCD_FUNC_SET_CMD				0b00111000
#define LCD_DSP_ON_OFF_CTRL_CMD 		0b00001110
#define LCD_DSP_CLEAR_CMD		 		0b00000001
#define LCD_ENTRY_MOD_SET_CMD		 	0b00000110
#define LCD_CURSOR_DSP_SHFT_CMD			0b00011000
#define LCD_RETURN_HOME_CMD				0b00000010
#define LCD_SET_CGRAM_ADDR_CMD			0x40


#define index		5
/**************************************************************************************************
 * functions prototypes
 *************************************************************************************************/
void LCD_vidWritecmd(Uint8_t u8commandCopy);




/**************************************************************************************************
 * functions implementation v1
 *************************************************************************************************/
//void LCD_vidInit(void)
//{
//	DIO_u8SetPortDir(LCD_DATA_PORT, FULL_OUTPUT);
//	DIO_u8SetPinDir(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
//	DIO_u8SetPinDir(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
//	DIO_u8SetPinDir(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);
//	_delay_ms(40);
//
//	LCD_vidWritecmd(LCD_FUNC_SET_CMD);
//	_delay_ms(1);
//
//	LCD_vidWritecmd(LCD_DSP_ON_OFF_CTRL_CMD);
//	_delay_ms(1);
//
//	LCD_vidWritecmd(LCD_DSP_CLEAR_CMD);
//	_delay_ms(4);
//
//	LCD_vidWritecmd(LCD_ENTRY_MOD_SET_CMD);
//}
//
//
//void LCD_vidWritecmd(Uint8_t u8commandCopy)
//{
//	DIO_u8SetPinVal(LCD_RW_PORT, LCD_RW_PIN, LOW); // WRITE
//	DIO_u8SetPinVal(LCD_RS_PORT, LCD_RS_PIN, LOW); // CMD
//	DIO_u8SetPortVal(LCD_DATA_PORT, u8commandCopy);
//
//	DIO_u8SetPinVal(LCD_EN_PORT, LCD_EN_PIN, HIGH); //ENABLE high
//	_delay_ms(2);
//	DIO_u8SetPinVal(LCD_EN_PORT, LCD_EN_PIN, LOW); //ENABLE low
//}
//
//
//void LCD_vidWriteChar(Uint8_t u8CharCopy)
//{
//	DIO_u8SetPinVal(LCD_RW_PORT, LCD_RW_PIN, LOW); // WRITE
//	DIO_u8SetPinVal(LCD_RS_PORT, LCD_RS_PIN, HIGH); // DATA
//	DIO_u8SetPortVal(LCD_DATA_PORT, u8CharCopy);
//
//	DIO_u8SetPinVal(LCD_EN_PORT, LCD_EN_PIN, HIGH); //ENABLE high
//	_delay_ms(2);
//	DIO_u8SetPinVal(LCD_EN_PORT, LCD_EN_PIN, LOW); //ENABLE low
//
//}




/**************************************************************************************************
 * functions implementation v2
 *************************************************************************************************/
void LCD_vidInit(void)
{
	DIO_s8SETPortDir(LCD_DATA_PORT,OUTPUT);
	DIO_s8SETPinDir(LCD_RS_PORT_PIN,OUTPUT);
	DIO_s8SETPinDir(LCD_RW_PORT_PIN,OUTPUT);
	DIO_s8SETPinDir(LCD_EN_PORT_PIN,OUTPUT);

	_delay_ms(40);

	LCD_vidWritecmd(LCD_FUNC_SET_CMD);
	_delay_ms(1);

	LCD_vidWritecmd(LCD_DSP_ON_OFF_CTRL_CMD);
	_delay_ms(1);

	LCD_vidWritecmd(LCD_DSP_CLEAR_CMD);
	_delay_ms(4);

	LCD_vidWritecmd(LCD_ENTRY_MOD_SET_CMD);




}




void LCD_vidWritecmd(Uint8_t u8commandCopy)
{
	DIO_s8SETPinVal(LCD_RW_PORT_PIN, LOW); // WRITE
	DIO_s8SETPinVal(LCD_RS_PORT_PIN, LOW); // CMD
	DIO_s8SETPortVal(LCD_DATA_PORT, u8commandCopy);

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(2);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low
}




void LCD_vidWriteChar(Uint8_t u8CharCopy)
{
	DIO_s8SETPinVal(LCD_RW_PORT_PIN, LOW); // WRITE
	DIO_s8SETPinVal(LCD_RS_PORT_PIN, HIGH); // DATA
	DIO_s8SETPortVal(LCD_DATA_PORT, u8CharCopy);

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(2);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low

}



void LCD_ClrDisplay(void)
{
	LCD_vidWritecmd(LCD_DSP_CLEAR_CMD);
	_delay_ms(4);
	LCD_vidWritecmd(LCD_RETURN_HOME_CMD);
	_delay_ms(4);

}




void LCD_ShiftLeft(void)
{
	LCD_vidWritecmd(LCD_CURSOR_DSP_SHFT_CMD);
	_delay_ms(1);

}





void LCD_gotoXY(Uint8_t row, Uint8_t pos)
{
	if (row==0 && pos < 16)
	{
		LCD_vidWritecmd((pos & 0x0F)| 0x80);
	}
	else if (row==1 && pos < 16)
	{
		LCD_vidWritecmd((pos & 0x0F)| 0xC0);
	}
}





void LCD_WriteString(Uint8_t* str)
{
	Uint16_t count = 0;
	Uint8_t string = str[count];
	while(string)
	{
		LCD_vidWriteChar(string);
		string = str[++count];
	}
}




void LCD_WriteInt(Uint32_t number)
{
	Uint8_t STR[index];
//	sprintf(STR, "%u", number);
	itoa(number, STR, 10);
	LCD_WriteString(STR);
//	Uint8_t ones = (Uint8_t) number % 10 + '0';
//	Uint8_t tens = (Uint8_t) number / 10 + '0';
//	//Uint8_t Char= (Uint8_t)number + '0';
//	if (tens != '0')
//		LCD_vidWriteChar(tens);
//	LCD_vidWriteChar(ones);
}



void LCD_WriteArabic(Uint8_t u8ArCharCopy)
{
	LCD_vidWritecmd(0x04);
	LCD_vidWriteChar(u8ArCharCopy);
}




void LCD_vidCreatCustomChar(Uint8_t* pu8custom, Uint8_t u8Location)
{
	if (u8Location < 8)  // CGRAM only store 8 characters
	{
		LCD_vidWritecmd(LCD_SET_CGRAM_ADDR_CMD + (u8Location*8));
		_delay_ms(1);
		for (Uint8_t i = 0; i < 8 ; i++)
		{
			LCD_vidWriteChar(pu8custom[i]);
		}
	}
}



