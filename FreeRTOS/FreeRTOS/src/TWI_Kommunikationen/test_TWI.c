/*
* test_TWI.c
* Author: Björn Berggren
* Created: 2018-05-04 12:43:01
*  
*/

#include <asf.h>
#include "test_TWI.h"
#include "TWI_Handler.h"

//uint8_t SLAVE_ADDRESS_POSITIONERING =0;

#define LED_ON					1
#define LED_OFF					2
#define SERVO_ROTATE_RIGHT		3
#define SERVO_ROTATE_LEFT		4
#define SERVO_STOP				5


// Påbyggnad

void test_Led_On(void)
{
	transmit_package(LED_ON, SLAVE_ADDRESS_PABYGGNAD);
	delay_ms(3000);
}

void test_Led_Off(void)
{
	transmit_package(LED_OFF, SLAVE_ADDRESS_PABYGGNAD);
	delay_ms(3000);
}

void test_Servo_Right(void)
{
	transmit_package(SERVO_ROTATE_RIGHT, SLAVE_ADDRESS_PABYGGNAD);
	delay_ms(3000);
}

void test_Servo_Left(void)
{
	printf("Rotate to The Left");
	transmit_package(SERVO_ROTATE_LEFT, SLAVE_ADDRESS_PABYGGNAD);
	delay_ms(3000);
}

void test_Servo_Stop()
{
	printf("The Stop");
	transmit_package(SERVO_STOP, SLAVE_ADDRESS_PABYGGNAD);
	delay_ms(3000);
}



