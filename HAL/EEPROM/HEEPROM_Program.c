/*
 * HEEPROM_Program.c
 *
 *  Created on: Feb 3, 2023
 *      Author: hp
 */

#include "../../MCAL/I2C/I2C.h"
#include "../../commons/std_types.h"
#include "../../commons/Bit_Math.h"
#include "HEEPROM_Interface.h"

#define EEPROM_ADDRESS		0b0101000



void eeprom_init(void)
{
	i2c_init_master();
}


void eeprom_write_byte(Uint16_t address, Uint8_t data)  // address is 10 bit
{
	Uint8_t deviceAddress;
	Uint8_t dataAddress;

	deviceAddress = EEPROM_ADDRESS | ((address >> 8) & 0x0003);
//	dataAddress = (address & 0b0011111111);

	/* Send start condition */
	i2c_start();
	/* Send slave address */
	i2c_send_slave_address_with_write_req(deviceAddress);     // i2c_write_byte(0x50 | (address >> 8) & 0x00000111 );
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  // 520 = 0b 01010 0  0  1   1 01110 11
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  //                A2 P1 P2  B7      B0
	/* Send data location */
	i2c_write_byte((Uint8_t) address); // or i2c_write_byte(dataAddress);
	/* Send data */
	i2c_write_byte(data);
	/* Send Stop Condition */
	i2c_stop();

}


Uint8_t eeprom_read_byte(Uint16_t address)
{
	Uint8_t deviceAddress;
	Uint8_t dataAddress;
	Uint8_t data;
	deviceAddress = EEPROM_ADDRESS | ((address >> 8) & 0x0003);

	/* Send start condition */
	i2c_start();
	/* Send slave address with write request*/
	i2c_send_slave_address_with_write_req(deviceAddress);
	/* Send Data location*/
	i2c_write_byte((Uint8_t) address);
	/* Send Repeated Start Condition*/
	i2c_repeated_start();
	/* Send slave address with read request*/
	i2c_send_slave_address_with_read_req(deviceAddress);
	/*Read Received Byte*/
	data = i2c_read_byte();
	/* Send Stop Condition */
	i2c_stop();

	return data;


}
