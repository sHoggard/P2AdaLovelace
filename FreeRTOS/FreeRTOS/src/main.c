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

#include "Movement/__vars.h"

char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	configureConsole();

	// Insert application code here, after the board has been initialized.
	
	initMovement();
	
	// testing new wheelcounter strategy
	//while (true)
	//{
		//printf("counterLeft: %i\ncounterRight: %i\n\n", (int)counterLeft, (int)counterRight);
		//delay_ms(2000);
	//}
	
	time_tick_init();
	
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
