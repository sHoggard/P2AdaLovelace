/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
 
#include <asf.h>
#include "config/conf_AdaLovelace.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"
#include "Movement/Movement.h"
#include "TimeTick/time_tick.h"
#include "Utilities/ConsoleFunctions/consoleFunctions.h"
#include "Com/Com.h"
#include "Com/KOM_NAV.h"

#include "Movement/__vars.h"

char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

void test_driveAccuracy(void);
void test_track(bool);
void test_TWI(void);
void test_comFunctions(void);
void test_commandParser(void);
void test_allocatedAddresses(void);
void test_pickupObject(int);
void test_dropOffObject(void);
void test_regulatedDrive(uint16_t, uint32_t, bool);
void test_regulatedRotate(uint16_t, uint16_t, bool);
void test_regulatedComControl(void);

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	configureConsole();

	// Insert application code here, after the board has been initialized.
	
	membag_init();			// move to initCom()?
	initMovement();
	initCom();
	time_tick_init();
	
	//// testing new wheelcounter strategy
	//while (true)
	//{
		//printf("counterLeft: %i\ncounterRight: %i\n\n", (int)counterLeft, (int)counterRight);
		//delay_ms(2000);
	//}
	
	//drive(50, 0);
	
	// test TWI
	//test_TWI();
	
	//test_pickupObject(3);
	
	// movement functions
	test_track(1);				//initMovement()
	
	//test_commandParser();
	
	//test_bufferFunctions()	//membag_init(), initCom()
	
	//char buffer[20];
	
	int speed = 100;
	
	// test actual speed
	scanf("%i", &speed);
	printf("speed: %i\n\n", speed);
	//setMotorSpeed(MOTOR_BRAKE + speed, MOTOR_BRAKE + speed);
	
	int counter = 0;
	
	while (1)
	{
		if (time_tick_get()%100 == 0)
		{
			//fputs(clrCom, stdout);
			//puts(itoa(counterLeft, buffer, 10));
			//puts(itoa(counterRight, buffer, 10));
			//puts(itoa(orientation(), buffer, 10));
			//puts(itoa(regulated_speed.left, buffer, 10));
			//puts(itoa(regulated_speed.right, buffer, 10));
			//puts(itoa(regulated_speed.target, buffer, 10));
			////drive(speed, 0);
			//test_movement();
			//if (speed < 500)
			//{
				//speed++;
			//}
			printf("%i: \n", counter++);
			test_movement();
			printf("\n");
			delay_ms(1);
		}
	}
	
	// test accuracy of distance measurement
	test_driveAccuracy();
}

void test_driveAccuracy()
{
	uint32_t start = time_tick_get();
	int speed = 100;
	scanf("%i", &speed);
	printf("speed: %i\n\n", speed);
	drive(speed, 5000);
	if (time_tick_get() > start + 10000)
		{
			printf("distance travelled after 10 seconds: %i\n", (int)(distanceLeft + distanceRight)/2);
			drive(0, 0);
			test_movement();
			delay_ms(5000);
		}
}

void test_track(bool f_TWI)
{
	test_comFunctions();
	delay_ms(1000);
	test_comFunctions();
	delay_ms(1000);
	test_comFunctions();
	printf("First leg\n");
	test_regulatedDrive(300, 3500, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	printf("Second leg\n");
	test_regulatedRotate(100, 270, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	test_regulatedDrive(200, 2000, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	printf("Third leg\n");
	test_regulatedRotate(100, 180, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	test_regulatedDrive(400, 1500, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	printf("Orientate towards object\n");
	test_regulatedRotate(100, data_extension.bearing_object + 180, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	test_pickupObject(data_extension.type_object);
	test_regulatedRotate(100, 180, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	printf("Fourth leg\n");
	test_regulatedRotate(100, 135, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	test_regulatedDrive(300, 2828, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	test_regulatedRotate(100, data_extension.bearing_dropzone + 0, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	if (data_extension.type_object != 0)
	{
		test_dropOffObject();
	}
	printf("Reset\n");
	test_regulatedRotate(100, 0, f_TWI);
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	while(1)
	{
		printf("Test drive done\n");
		delay_ms(500);
	}
}

void test_TWI()
{
	printf("Starting to read TWI\n");
	while (1)
	{
		if (time_tick_get()%100 == 0)
		{
			task_regulate();
			task_movement();
			delay_ms(1);
		}
		if (time_tick_get()%2000 == 0)
		{
			test_comFunctions();
		}
	}
}

void test_comFunctions()
{
	task_com();
	printf("Extension ID: 0x%x\n", data_extension.ID);
	printf("Object distance: %i\n", data_extension.distance_object);
	printf("Object bearing: %i\n", data_extension.bearing_object);
	printf("Dropzone distance: %i\n", data_extension.distance_dropzone);
	printf("Dropzone bearing: %i\n", data_extension.bearing_dropzone);
	printf("Maximum speed: %i\n", data_extension.max_speed);
	printf("Object type: %i\n", data_extension.type_object);
	printf("x_koord_Box: %i\n", (int)x_koord_Box);
	printf("y_koord_Box: %i\n", (int)y_koord_Box);
	printf("x_koord_Kub: %i\n", (int)x_koord_Kub);
	printf("y_koord_Kub: %i\n", (int)y_koord_Kub);
	printf("x_koord_Kula: %i\n", (int)x_koord_Kula);
	printf("y_koord_Kula: %i\n", (int)y_koord_Kula);
	printf("x_koord_Vinglas: %i\n", (int)x_koord_Vinglas);
	printf("y_koord_Vinglas: %i\n", (int)y_koord_Vinglas);
	printf("x_koord_Robot: %i\n", (int)x_koord_Robot);
	printf("y_koord_Robot: %i\n", (int)y_koord_Robot);
}

void test_commandParser()
{
	char tempCommand = 's';
	int tempSpeed = 0;
	int tempDistance = 0;
	
	printf("setup\n");
	
	while (1)
	{
		if (time_tick_get()%20 == 0)
		{
			if (time_tick_get()%100 == 0)
			{
				task_regulate();
				delay_ms(1);
			}
			task_movement();
		}
		
		//tempCommand = getchar();
		//if (!feof(stdin))
		//if (ftell(stdin) != 0)
		//if (tempCommand != EOF)
		if (isDone())
		{
			task_regulate();		// get rid of straggling values
			task_regulate();
			delay_ms(200);
			printf("Reading... ");
			scanf("%c", &tempCommand);
			printf("%c\n", tempCommand);
			switch (tempCommand)
			{
				case 'd':
					scanf("%i%i", &tempSpeed, &tempDistance);
					printf("%i\n", tempSpeed);
					printf("%i\n", tempDistance);
					drive(tempSpeed, tempDistance);
					break;
				case 'r':
					scanf("%i%i", &tempSpeed, &tempDistance);
					printf("%i\n", tempSpeed);
					printf("%i\n", tempDistance);
					rotate(tempSpeed, tempDistance);
					break;
				case 'o':
					printf("Current orientation: %i\n", getOrientation());
					break;
				case 'c':
					clearCounters();
					break;
				case 'p':
					break;
				case 's':
					stop();
					break;
			}
			//while((tempCommand = getchar()) != '\n' && tempCommand != EOF);
			//fseek(stdin, 0, SEEK_END);
		}
		delay_ms(1);
	}
}

void test_allocatedAddresses()
{
	initCom();
	delay_ms(1000);
	initCom();
	delay_ms(1000);
	initCom();
}

void test_pickupObject(int object)
{
	task_com();
	switch (object)
	{
		case 0:
			printf("No object to pick up\n");
			break;
		case BALL:
			printf("Picking up ball\n");
			state_com = 0;
			sendToSlave(extension, 0x21);
			delay_ms(500);
			while (state_com != 0x14 && state_com != 0x15)
			{
				test_regulatedComControl();
			}
			break;
		case GLASS:
			printf("Picking up glass\n");
			state_com = 0;
			sendToSlave(extension, 0x23);
			delay_ms(500);
			while (state_com != 0x14 && state_com != 0x15)
			{
				test_regulatedComControl();
			}
			break;
	}
}

void test_dropOffObject()
{
	printf("Dropping off object\n");
	state_com = 0;
	sendToSlave(extension, 0x25);
	delay_ms(500);
	while (state_com != 0x16 && state_com != 0x17)
	{
		test_regulatedComControl();
	}
}

void test_regulatedDrive(uint16_t speed, uint32_t distance, bool f_TWI)
{
	drive(speed, distance);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_regulate();
			task_movement();
			delay_ms(1);
		}
		if (f_TWI && time_tick_get()%2000 == 60)
		{
			test_comFunctions();
		}
	}
}

void test_regulatedRotate(uint16_t speed, uint16_t orientation, bool f_TWI)
{
	rotate(speed, orientation);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_regulate();
			task_movement();
			delay_ms(1);
		}
		if (f_TWI && time_tick_get()%2000 == 60)
		{
			test_comFunctions();
		}
	}
}

void test_regulatedComControl()
{
	while(1)
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%500 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%500 == 0)
		{
			task_regulate();
			task_movement();
			task_com();
			delay_ms(1);
			return;
		}
	}
}
