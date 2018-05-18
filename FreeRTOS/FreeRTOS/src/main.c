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
	
	//// testing new wheelcounter strategy
	//while (true)
	//{
		//printf("counterLeft: %i\ncounterRight: %i\n\n", (int)counterLeft, (int)counterRight);
		//delay_ms(2000);
	//}
	
	time_tick_init();
	
	//// test TWI
	//printf("Starting to read TWI\n");
	//while (1)
	//{
		//if (time_tick_get()%5000 == 0)
		//{
			//task_com();
		//}
	//}
	
	
	//// movement functions
	//drive(300, 4000);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//rotate(20, 270);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//drive(200, 2000);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//rotate(20, 180);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//drive(400, 2000);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//rotate(20, 135);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//drive(300, 2828);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//rotate(20, 360);
	//while(!isDone())
	//{
		//if (time_tick_get()%25 == 0 && time_tick_get()%100 != 0)
		//{
			//task_movement();		// takes more than 1 ms
		//}
		//if (time_tick_get()%100 == 0)
		//{
			//task_movement();
			//task_regulate();
		//}
	//}
	//while(1)
	//{
		//printf("Test drive done\n");
	//}
	
	//// test_bufferFunctions()
	//while(1)
	//{
		//if (time_tick_get()%100 == 0)
		//{
			//task_com();
		//}
	//}
	
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
	
	initCom();
	delay_ms(1000);
	initCom();
	delay_ms(1000);
	initCom();
	
	char buffer[20];
	
	int speed = 100;
	
	scanf("%i", &speed);
	
	// test actual speed
	uint32_t start = time_tick_get();
	
	drive(speed, 5000);
	
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
	
		// test accuracy of distance measurement
		//if (time_tick_get() > start + 10000)
		//{
			//printf("distance travelled after 10 seconds: %i\n", (int)(distanceLeft + distanceRight)/2);
			//drive(0, 0);
			//test_movement();
			//delay_ms(5000);
		//}
	}
}
