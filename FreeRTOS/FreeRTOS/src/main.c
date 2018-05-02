/**
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 *
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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <inttypes.h>
#include <stdio_serial.h>
//Tasks
#include "Tasks/task_player1.h"
#include "Tasks/task_player2.h"
#include "Tasks/task_control.h"
//Delay
#include "Utilities/DelayFunctions/delayFunctions.h"
//Console Data Visualizer
#include "Utilities/ConsoleFunctions/consoleFunctions.h"
//FreeRTOS
#include "FreeRTOS.h"
//Semaphores
#include "semphr.h"
//Struct
#include "xHandlerParameters.h"
// From module: TC - Timer Counter
#include "Utilities/TimerCounter/TimerCounter.h"
#include "Utilities/PioInterrupt/PioInterrupt.h"

#include "conf_board.h"
#include "conf_clock.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"

int i = 0;

int main (void)
{
	i++;
	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	init_timer();
	delayInit();
	//initMotors();
	
	//char buffer [34];
	//itoa(sysclk_get_cpu_hz(), buffer, 10);
	//puts(buffer);
	
	/* Configure the console uart for debug information */
	configureConsole();

	initMotors();
	initSensors();
	
	/* Infinite loop */
	while (1) 
	{
		printf("hejsan");
		//char c = (char) i;
		//printf((int)i);
		printf("\n");
		delayMicroseconds(100000);
			//char buffer [34];
			
			//itoa(i, buffer, 10); 
			// sysclk_get_cpu_hz() ger klockfrekvensen
			i++;
			printInt(i);
		delayMicroseconds(100000);
	}
}



