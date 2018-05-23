/*
 * TWI_data.h
 *
 * Created: 2018-05-20 15:43:17
 *  Author: Sebastian Hoggard
 */ 


#ifndef TWI_DATA_H_
#define TWI_DATA_H_

#include <asf.h>

#define ADDRESS_POSITION 0x10
#define ADDRESS_EXTENSION 0x08

#define PACKET_SIZE 10

#define SPEED 100000										/* Default I2C transfer speed = 100.000 */
#define PORT TWI1											/* Use SDA 20 and SCL 21 on Arduino Due */

uint8_t data_position[PACKET_SIZE];
uint8_t data_extension[PACKET_SIZE];

twi_package_t packet_position;

twi_package_t packet_extension;

uint8_t initTwi(void);

#endif /* TWI_DATA_H_ */