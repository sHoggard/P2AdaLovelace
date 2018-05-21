/*
 * TWI_Handler.h
 *
 * Author: Björn Berggren
 *  
 */ 

#ifndef TWI_HANDLER_H_
#define TWI_HANDLER_H_

#define SLAVE_ADDRESS_PABYGGNAD 8
#define SLAVE_ADDRESS_POSITIONERING 0x10

/* Commands to send to the slave */
#define LED_ON					1
#define LED_OFF					2
#define SERVO_CLOCKWISE			3
#define SERVO_ANTI_CLOCKWISE	4
#define SERVO_STOP				5
/*-------------------------------*/

#define DATA_SENT     1
#define DATA_READ     1

#define DATA_NOT_SENT 0
#define DATA_NOT_READ 0

#define TRANSMIT_LENGTH_PABYGGNAD		1						/* The length of the package that is sent to PAB */
#define TRANSMIT_LENGTH_POSITIONERING	1						/* The length of the package that is sent to POS */
#define RECEIVE_LENGTH_PABYGGNAD		10	
#define RECEIVE_LENGTH_POSITIONERING		10

uint8_t receive_data_pabyggnad[RECEIVE_LENGTH_PABYGGNAD];
uint8_t receive_data_positionering[RECEIVE_LENGTH_POSITIONERING];



uint8_t init_twi(void);
uint8_t transmit_package(uint8_t data, uint8_t slave);
uint8_t receive_package(uint8_t slave);
uint8_t twi_send(uint8_t data_arr[], uint8_t data, twi_packet_t packet, uint8_t slave);
uint8_t twi_read(uint8_t rec_data[], uint8_t data_length, twi_packet_t packet_rec);
uint8_t communicationManager (uint8_t value);
uint8_t console_init(void);

#endif /* I2CFUNCTIONS_H_ */