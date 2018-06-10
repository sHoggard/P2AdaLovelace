/*
 * 
 * TWI_Handler.c
 * 
 * 
 * Author: Björn Berggren
 *
 */

#include <asf.h>
#include "TWI_Handler.h"


/*-------------- Definitions ---------------*/
#define TWI_SPEED					100000					/* Default I2C transfer speed = 100.000 */						
#define TWI_SLAVE_MEM_ADDR			0x00					
#define TWI_PORT					TWI1					/* Use SDA 20 and SCL 21 on Arduino Due */ 
		

/*-------------- Packet related ------------*/
uint8_t transmit_data_pabyggnad[TRANSMIT_LENGTH_PABYGGNAD]= {};		/* stores the data which will be sent to UNO */
uint8_t transmit_data_positionering[TRANSMIT_LENGTH_POSITIONERING]= {};		/* stores the data which will be sent to MEGA */
uint8_t receive_data_pabyggnad[RECEIVE_LENGTH_PABYGGNAD]= {};		/* stores the data which will be received from UNO */
uint8_t receive_data_positionering[RECEIVE_LENGTH_POSITIONERING]= {};		/* stores the data which will be received from MEGA */



	/* ---------- Packets to send ---------- */
	twi_package_t packet_pab = {
		.addr[0]		= TWI_SLAVE_MEM_ADDR,				/* TWI slave memory address data (Most significant bit) */
		.addr[1]		= 0,								/* Least significant bit */
		.addr_length	= 0,								/* Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size) */
		.chip			= SLAVE_ADDRESS_PABYGGNAD,				/* TWI chip address to communicate with (TWI slave bus address) */
		.buffer			= (void *) transmit_data_pabyggnad,			/* transfer data source buffer (pointer on the data to write to slave) */
		.length			= TRANSMIT_LENGTH_PABYGGNAD			/* How many bytes do we want to transfer (bytes) */
	};

	twi_package_t packet_pos = {
		.addr[0]		= TWI_SLAVE_MEM_ADDR,					
		.addr[1]		= 0,									
		.addr_length	= 0,									
		.chip			= SLAVE_ADDRESS_POSITIONERING,					
		.buffer			= (void *) transmit_data_positionering,				
		.length			= TRANSMIT_LENGTH_POSITIONERING				
	};
	/* ------------------------------------ */

	/* ---------- Packets to receive ---------- */
	twi_package_t packet_rec_pab = {
		.addr[0]		= TWI_SLAVE_MEM_ADDR,
		.addr[1]		= 0,
		.addr_length	= 0,
		.chip			= SLAVE_ADDRESS_PABYGGNAD,
		.buffer			= (void *) receive_data_pabyggnad,
		.length			= RECEIVE_LENGTH_PABYGGNAD
	};
	
	twi_package_t packet_rec_pos = 
	{
		.addr[0]		= TWI_SLAVE_MEM_ADDR,
		.addr[1]		= 0,
		.addr_length	= 0,
		.chip			= SLAVE_ADDRESS_POSITIONERING,
		.buffer			= (void *) receive_data_positionering,
		.length			= RECEIVE_LENGTH_POSITIONERING
	};
	/* ------------------------------------ */

/* ------------------------------------ */


/*
 *	Setup due as the master
 */
uint8_t init_twi(void)
{
	twi_master_options_t opt;
	opt.speed = TWI_SPEED;
	if(twi_master_setup(TWI_PORT, &opt) == TWI_SUCCESS) 
	{
		printf("MASTER SETUP OK\n");
		return 1;
	}
	else
	{
		printf("MASTER SETUP NOT OK\n");
		return 0;
	}
		
}

/*
 *	Sends a packet (1 byte) to the slave (uno or mega)
 */
uint8_t transmit_package(uint8_t data, uint8_t slave)
{
		
	/* Send to Påbyggnadsenhet (UNO) */
	if(SLAVE_ADDRESS_PABYGGNAD == slave)
		return twi_send(transmit_data_pabyggnad, data, packet_pab, SLAVE_ADDRESS_PABYGGNAD);
		
	/* Send to Positioneringsenhet (MEGA) */
	else if(SLAVE_ADDRESS_POSITIONERING == slave)
		return twi_send(transmit_data_positionering, data, packet_pos, SLAVE_ADDRESS_POSITIONERING);
		
	else
		return !TWI_SUCCESS;
		
}

/*
 *  The function "twi_master_write" will NOT return until all data has been written or error occurred.
 *  It will return TWI_SUCCESS if all bytes were written, error code otherwise.
 */
uint8_t twi_send(uint8_t data_arr[], uint8_t data, twi_packet_t packet, uint8_t slave) 
{
	data_arr[0] = data;
	packet.chip = slave;
	packet.buffer = (void *)data_arr;
	if(twi_master_write(TWI_PORT, &packet) == TWI_SUCCESS)
		return DATA_SENT;
	else
		return DATA_NOT_SENT;
}


uint8_t receive_package(uint8_t slave)
{
	if (slave == SLAVE_ADDRESS_PABYGGNAD)
		return twi_read(receive_data_pabyggnad, RECEIVE_LENGTH_PABYGGNAD, packet_rec_pab);
	else if (slave == SLAVE_ADDRESS_POSITIONERING)
		return twi_read(receive_data_positionering, RECEIVE_LENGTH_POSITIONERING, packet_rec_pos);
	else
		return !TWI_SUCCESS;
}

uint8_t twi_read(uint8_t rec_data[], uint8_t data_length, twi_packet_t packet_rec)
{
	printf("reading...\n");
	if(twi_master_read(TWI_PORT, &packet_rec) == TWI_SUCCESS)
	{
		printf("reading IF STATE...\n");
		for(int i = 0; i < data_length; i++)
		return DATA_READ;
	}
	else
		return DATA_NOT_READ;
}

uint8_t console_init(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	
	printf("Console ready\n");
	printf("=============\n");
	return 0;
}
	

	
