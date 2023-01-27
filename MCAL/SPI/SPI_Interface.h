/*
 * SPI_Interface.h
 *
 *  Created on: Jan 27, 2023
 *      Author: hp
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

/*************************************************************************
 * 					USER DEFINED DATA_TYPE
 ************************************************************************/
typedef enum
{
	SPI_OK=0,
	SPI_NOK,

}enu_status_t;

typedef enum    // compiler
{
	SPI_PRE_4=0,
	SPI_PRE_16,
	SPI_PRE_64,
	SPI_PRE_128,
	SPI_PREx2_2,
	SPI_PREx2_8,
	SPI_PREx2_32,
	SPI_PREx2_64,
	SPI_PRE_INVALID,

}enu_spiPrescalar_t;


/*************************************************************************
 * 					FUNCTION PROTOTYPES
 ************************************************************************/

#if SPI_TYPE == SPI_MASTER
enu_status_t MSPI_enuInit(enu_spiPrescalar_t copy_enPrecalar);
#elif SPI_TYPE == SPI_SLAVE
enu_status_t MSPI_enuInit(void);
#endif

enu_status_t MSPI_Transciever(Uint8_t, Uint8_t*);





#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
