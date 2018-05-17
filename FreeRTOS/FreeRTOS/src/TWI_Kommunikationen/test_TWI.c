/*
* test.c
*
* Created: 2018-05-03 11:43:01
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


/************************************************************************/
/*							  TEST TVÅ SLAVAR                           */
/************************************************************************/
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
	transmit_package(SERVO_ROTATE_RIGHT, SLAVE_ADDRESS_PABYGGNAD)
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
	printf("Rotate to The Stop");
	transmit_package(SERVO_STOP, SLAVE_ADDRESS_PABYGGNAD);
	delay_ms(3000);
}

void test_fs_4()
{
	if(transmit_package(NULL,SLAVE_ADDRESS_POSITIONERING) == DATA_SENT)
		printf("test_fs_4() = PASSED");
	else
		printf("test_fs_4() = NOT PASSED");
}

void test_fs_5()
{
	if(transmit_package(LED_ON,SLAVE_ADDRESS_PABYGGNAD) == DATA_SENT)
		printf("test_fs_5() = NOT PASSED");
	else
		printf("test_fs_5() = PASSED");
}

void test_fs_6()
{
	if(transmit_package(LED_ON,SLAVE_ADDRESS_POSITIONERING) == DATA_SENT)
		printf("test_fs_6() = NOT PASSED");
	else
		printf("test_fs_6() = PASSED");
}

void test_fs_7()
{
	if(transmit_package(LED_ON,SLAVE_ADDRESS_POSITIONERING) == DATA_SENT)
		printf("test_fs_7() = PASSED");
	else
		printf("test_fs_7() = NOT PASSED");
}

void test_fs_8()
{
	if(transmit_package(LED_ON,SLAVE_ADDRESS_PABYGGNAD) == DATA_SENT)
		printf("test_fs_8() = PASSED");
	else
		printf("test_fs_8() = NOT PASSED");
}

void test_fs_9()
{
	if (receive_package(SLAVE_ADDRESS_PABYGGNAD) && receive_package(SLAVE_ADDRESS_POSITIONERING))
		printf("test_fs_9() = PASSED");
	else
		printf("test_fs_8() = NOT PASSED");
}

void test_fs_10(){
	uint8_t counter =0;
	while(counter<20)
	{
		transmit_package(data_01,SLAVE_ADDRESS_POSITIONERING);
		counter++;
	}
}


/************************************************************************/
/*							  TEST EN SLAV                              */
/************************************************************************/
void test_s_1()
{
	if (transmit_package(LED_ON,SLAVE_ADDRESS_PABYGGNAD))
	printf("test_fs_9() = PASSED");
	else
	printf("test_s_1() = NOT PASSED");
}

void test_s_2()
{
	uint8_t counter=0;
	while(counter<20)
	{
		transmit_package(LED_ON,SLAVE_ADDRESS_PABYGGNAD);
		delay_ms(3000);
		transmit_package(LED_OFF,SLAVE_ADDRESS_PABYGGNAD);
		delay_ms(3000);
	}
	printf("test_fs_9() = PASSED");
}

void test_s_3()
{
	if (transmit_package(SERVO_ROTATE_RIGHT,SLAVE_ADDRESS_PABYGGNAD)== DATA_SENT)
		printf("test_s_3() = PASSED");
	else
		printf("test_s_3() = NOT PASSED");
}

void test_s_4()
{
	if (transmit_package(SERVO_ROTATE_LEFT,SLAVE_ADDRESS_PABYGGNAD)== DATA_SENT)
		printf("%s", "test_s_4() = PASSED");
	else
		printf("test_s_4() = NOT PASSED");
}

void test_s_5()
{
	transmit_package(SERVO_ROTATE_RIGHT,SLAVE_ADDRESS_PABYGGNAD);
	delay_ms(3000);
	transmit_package(SERVO_STOP,SLAVE_ADDRESS_PABYGGNAD);
}

void test_s_6()
{
	if (receive_package(SLAVE_ADDRESS_PABYGGNAD)==DATA_READ)
		printf("test_s_6() = PASSED");
	else
		printf("test_s_6() = NOT PASSED");
}

void test_s_7()
{
	if (receive_package(SLAVE_ADDRESS_PABYGGNAD)==DATA_READ)
		printf("test_s_7() = PASSED");
	else
		printf("test_s_7() = NOT PASSED");
}

int console_init(void)
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