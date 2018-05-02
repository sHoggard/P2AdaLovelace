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

char clrCom[] = {27, '[', '2', 'J', '\0'};

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	configureConsole();

	// Insert application code here, after the board has been initialized.
	
	initMotors();
	initSensors();
	
	time_tick_init();
	
	char buffer[20];
	
	int speed = 80;
	
	while (1)
	{
		if (time_tick_get()%500 == 0)
		{
			puts(clrCom);
			puts(itoa(counterLeft, buffer, 10));
			puts(itoa(counterRight, buffer, 10));
			puts(itoa(orientation(), buffer, 10));
			puts(itoa(speed, buffer, 10));
			drive(speed, 0);
			test_movement();
			if (speed < 500)
			{
				speed++;
			}
			puts("\n");
			delay_ms(1);
		}
	}
}
