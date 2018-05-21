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

#include "Movement/__vars.h"

char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

void test_driveAccuracy(void);
void test_track(void);
void test_TWI(void);
void test_comFunctions(void);
void test_commandParser(void);
void test_allocatedAddresses(void);

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	configureConsole();

	// Insert application code here, after the board has been initialized.
	
	//membag_init();			// move to initCom()?
	initMovement();
	//initCom();
	time_tick_init();
	
	//// testing new wheelcounter strategy
	//while (true)
	//{
		//printf("counterLeft: %i\ncounterRight: %i\n\n", (int)counterLeft, (int)counterRight);
		//delay_ms(2000);
	//}
	
	// test TWI
	//test_TWI();
	
	// movement functions
	test_track();				//initMovement()
	
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

void test_track()
{
	drive(300, 4000);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	rotate(50, 270);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	drive(200, 2000);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	rotate(50, 180);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	drive(400, 2000);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	rotate(50, 135);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	drive(300, 2828);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	rotate(50, 0);
	while(!isDone())
	{
		if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		{
			task_movement();		// takes more than 1 ms
		}
		if (time_tick_get()%100 == 0)
		{
			task_movement();
			task_regulate();
		}
	}
	task_regulate();				// get rid of straggling values
	task_regulate();
	delay_ms(200);
	while(1)
	{
		printf("Test drive done\n");
	}
}

void test_TWI()
{
	printf("Starting to read TWI\n");
	while (1)
	{
		if (time_tick_get()%5000 == 0)
		{
			task_com();
		}
	}
}

void test_comFunctions()
{
	while(1)
	{
		if (time_tick_get()%100 == 0)
		{
			task_com();
		}
	}
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
