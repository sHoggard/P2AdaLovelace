/*
 * TWI_data.c
 *
 * Created: 2018-05-20 16:04:05
 *  Author: Sebastian Hoggard
 */ 

#include "TWI_data.h"

twi_package_t packet_position = {
	.addr[0]		= 0,									/* TWI slave memory address data (Most significant bit) */
	.addr[1]		= 0,									/* Least significant bit */
	.addr_length	= 0,									/* Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size) */
	.chip			= ADDRESS_POSITION,						/* TWI chip address to communicate with (TWI slave bus address) */
	.buffer			= (void *) data_position,				/* transfer data source buffer (pointer on the data to write to slave) */
	.length			= PACKET_SIZE							/* How many bytes do we want to transfer (bytes) */
};

twi_package_t packet_extension = {
	.addr[0]		= 0,									/* TWI slave memory address data (Most significant bit) */
	.addr[1]		= 0,									/* Least significant bit */
	.addr_length	= 0,									/* Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size) */
	.chip			= ADDRESS_EXTENSION,					/* TWI chip address to communicate with (TWI slave bus address) */
	.buffer			= (void *) data_extension,				/* transfer data source buffer (pointer on the data to write to slave) */
	.length			= PACKET_SIZE							/* How many bytes do we want to transfer (bytes) */
};

/*
 *	Setup Due as the master
 */
uint8_t initTwi(void)
{
	twi_master_options_t opt;
	opt.speed = SPEED;
	if(twi_master_setup(PORT, &opt) == TWI_SUCCESS) 
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

//uint8_t twi_read(uint8_t rec_data[], uint8_t data_length, twi_packet_t packet_rec)
//{
	//printf("reading...\n");
	//if(twi_master_read(PORT, &packet_rec) == TWI_SUCCESS)
	//{
		//printf("reading IF STATE...\n");
		//for(int i = 0; i < data_length; i++)
		//printf("%i\n", receive_data_positionering[i]);
		//return DATA_READ;
	//}
	//else
	//return DATA_NOT_READ;
//}
//
//uint8_t twi_send(uint8_t data_arr[], uint8_t data, twi_packet_t packet, uint8_t slave)
//{
	//data_arr[0] = data;
	//packet.chip = slave;
	////packet.buffer = (void *)data_arr;
	//if(twi_master_write(PORT, &packet) == TWI_SUCCESS)
	//return DATA_SENT;
	//else
	//return DATA_NOT_SENT;
//}