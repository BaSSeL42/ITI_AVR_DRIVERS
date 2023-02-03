/*
 * I2C.c
 *
 *  Created on: Jan 28, 2023
 *      Author: hp
 */


#include "../../commons/std_types.h"
#include "../../commons/Bit_Math.h"

#include "I2C.h"

#define MASTER_ADDRESS		0xF2
#define SLAVE_ADDRESS		0x34

void i2c_init_master(void)
{
	// set prescalar to one
	ClrBit(TWSR,TWPS0);
	ClrBit(TWSR,TWPS1);
	// value on bitrate register to get 400 kHZ
	TWBR = 0x02;

	TWAR = (MASTER_ADDRESS << 1); // MASTER ADDRESS

	SetBit(TWCR, TWEN); // enable I2C
}


void i2c_start(void)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	SetBit(TWCR, TWSTA); // Enable start condition bit
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEN);

	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != START_ACK);
	ClrBit(TWCR, TWSTA);
}


void i2c_repeated_start(void)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	SetBit(TWCR, TWSTA); // Enable start condition bit
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEN);
	while (statusMask != REP_START_ACK);
	ClrBit(TWCR, TWSTA);
}

void i2c_send_slave_address_with_write_req(unsigned char slave_address)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	TWDR = (slave_address << 1);
	TWDR &= ~(1 << 0); // write
	SetBit(TWCR, TWINT);
//	SetBit(TWCR, TWEA);
	SetBit(TWCR, TWEN);

	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != SLAVE_ADD_AND_WR_ACK);
}


void i2c_send_slave_address_with_read_req(unsigned char slave_address)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	TWDR = (slave_address << 1);
	TWDR |= (1 << 0);   //read
	SetBit(TWCR, TWINT);
//	SetBit(TWCR, TWEA);
	SetBit(TWCR, TWEN);

	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != SLAVE_ADD_AND_RD_ACK);
}


void i2c_write_byte(unsigned char byte)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	TWDR = byte;
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEN);
	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != WR_BYTE_ACK);
}


unsigned char i2c_read_byte(void)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEN);
	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != RD_BYTE_WITH_NACK); //check for acknowldgement

	return TWDR;
}

void i2c_stop(void)
{

	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEN);
	SetBit(TWCR, TWSTO); // Enable stop condition bit
}


void i2c_init_slave (void)
{
	TWAR = (SLAVE_ADDRESS << 1); // MASTER ADDRESS

	SetBit(TWCR, TWEN); // enable I2C
}


void i2c_slave_check_slave_address_received_with_write_req(void)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEA);
	SetBit(TWCR, TWEN);
	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != SLAVE_ADD_RCVD_WR_REQ); //check for acknowldgement
}


void i2c_slave_check_slave_address_received_with_read_req(void)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEA);
	SetBit(TWCR, TWEN);
	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != SLAVE_ADD_RCVD_RD_REQ); //check for acknowldgement
}

unsigned char i2c_slave_read_byte(void)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEA); // enable Acknowledgment
	SetBit(TWCR, TWEN);
	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != SLAVE_DATA_RECEIVED); //check for acknowldgement

	return TWDR;
}
void i2c_slave_write_byte(unsigned char byte)
{
	Uint8_t statusMask = TWSR & 0b11111000;
	TWDR = byte;
	SetBit(TWCR, TWINT);
	SetBit(TWCR, TWEA);
	SetBit(TWCR, TWEN);
	while ( !(GetBit(TWCR, TWINT)) );
	while (statusMask != SLAVE_BYTE_TRANSMITTED);
}
