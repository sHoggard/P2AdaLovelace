/*
 * TWI_Handler.h
 *
 * Created: 2018-05-01 16:16:01
 *  
 */ 

#ifndef TWI_HANDLER_H_
#define TWI_HANDLER_H_

#define SLAVE_ADDRESS_PABYGGNAD 8
#define SLAVE_ADDRESS_POSITIONERING 0x10


/* Commands to send to the slave */
#define data_01					10
#define data_02					20
#define data_03					30

/*-------------------------------*/

#define DATA_SENT     1
#define DATA_READ     1

#define DATA_NOT_SENT 0
#define DATA_NOT_READ 0
#define RECEIVE_LENGTH_POSITIONERING		10	
#define RECEIVE_LENGTH_PABYGGNAD			10

uint8_t receive_data_positionering[RECEIVE_LENGTH_POSITIONERING];
uint8_t receive_data_pabyggnad[RECEIVE_LENGTH_PABYGGNAD];	

uint8_t init_twi(void);
uint8_t transmit_package(uint8_t data, uint8_t slave);
uint8_t receive_package(uint8_t slave);
uint8_t twi_send(uint8_t data_arr[], uint8_t data, twi_packet_t packet, uint8_t slave);
uint8_t twi_read(uint8_t rec_data[], uint8_t data_length, twi_packet_t packet_rec);
uint8_t communicationManager (uint8_t value);
uint8_t console_init(void);

#endif /* TWI_HANDLER_H_ */