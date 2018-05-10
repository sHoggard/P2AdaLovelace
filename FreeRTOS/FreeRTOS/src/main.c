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
#include "Navigering/angleCalculation.h"

int i = 0;

float goalAngle = 0.0;
float oldAngle = 0.0;
float newAngle = 0.0;
float angle = 0.0;


int main (void)
{
	i++;
	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	
	delayInit();
	//initMotors();
	
	//char buffer [34];
	//itoa(sysclk_get_cpu_hz(), buffer, 10);
	//puts(buffer);
	
	/* Configure the console uart for debug information */
	configureConsole();
	
	
	int test = 1;
	while(test == 1){
	/* -----------------------------------------------------------------------------------
				NAVIGERING - TEST	
	--------------------------------------------------------------------------------------*/
	
	//----------Test för att kontrollera så att grad-beräkning från radianer funkar----------
	/*float degrees = 0.0;
	float radians [] = {(PI/6), (PI/4), (PI/3), (PI/2), (PI), ((3*PI)/2), (2*PI)};
	char rads [7][9] = {"PI/6 = ", "PI/4 = ", "PI/3 = ", "PI/2 = ", "PI = ", "3PI/2 = ", "2PI = "};
	for (int i=0; i < 7; i++){
		degrees = rad2deg(radians[i]);
		printf(rads[i]);
		printInt(degrees);
	}*/
	
	
	//----------Test för avståndsberäkningar----------
	/*float distance = 0.0;
	distance = distanceCalculation(2,2,2,5); //3 längdenheter
	printf("Roboten i (2,5) har följande avstånd till objektet i (2,2) : ");
	printInt(distance);
	distance = distanceCalculation(2,4,2,2); //2 längdenheter
	printf("\nRoboten i (4,2) har följande avstånd till objektet i (2,2) : ");
	printInt(distance);
	distance = distanceCalculation(2,2,2,2); //0 längdenheter
	printf("\nRoboten i (2,2) har följande avstånd till objektet i (2,2) : ");
	printInt(distance);
	distance = distanceCalculation(2,10,2,2); //8 längdenheter
	printf("\nRoboten i (10,2) har följande avstånd till objektet i (2,2) : ");
	printInt(distance);*/
	
	
	//----------Test för 1a kvadranten----------
	/*goalAngle = degreeCalculation(2,1,2,2); //0 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,1,2,1);	//45 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,5,1);	//90 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,0,2,1);	//26grader
	printInt(goalAngle);*/
	
	
	//----------Test för 2a kvadranten----------
	/*goalAngle = degreeCalculation(2,4,2,2);	//180 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,3,2,1);	//135 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,5,1);	//90 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,6,2,0);	//116 grader
	printInt(goalAngle);*/
	
	
	//----------Test för 3e kvadranten----------
	/*goalAngle = degreeCalculation(2,4,2,3);	//243 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,2,5);	//270 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,3,1,5);	//194 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,5,2,5);	//225 grader
	printInt(goalAngle);*/
	
	
	//----------Test för 4e kvadranten----------
	/*goalAngle = degreeCalculation(2,1,1,3);	//296 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,2,5);	//270 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,0,1,6);	//291 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(8,2,6,7);	//350 grader
	printInt(goalAngle);*/
	
	
	//----------Test för beräkning av korrigeringsvinkel----------
	/*printf("\n----- TEST: ROTERA TILL 180 -----\n");
	newAngle = correctionAngleCalculation(2,4,2,2,oldAngle);
	angle = oldAngle + newAngle;
	printf("Current angle: ");
	printInt(oldAngle);
	printf("\nGoal angle: ");
	goalAngle = degreeCalculation(2,4,2,2);
	printInt(goalAngle);	
	printf("\nCorrection angle: ");
	printInt(newAngle);
	printf("\n--------------------------------\n");
	oldAngle = angle;
	
	printf("\n----- TEST: ROTERA TILL 45 -----\n");
	newAngle = correctionAngleCalculation(2,1,2,1,oldAngle);
	angle = oldAngle + newAngle;
	printf("Current angle: ");
	printInt(oldAngle);
	printf("\nGoal angle: ");
	goalAngle = degreeCalculation(2,1,2,1);
	printInt(goalAngle);
	printf("\nCorrection angle: ");
	printInt(newAngle);
	printf("\n--------------------------------\n");
	oldAngle = angle;
	
	printf("\n----- TEST: ROTERA TILL 0 -----\n");
	newAngle = correctionAngleCalculation(2,1,2,2,oldAngle);
	angle = oldAngle + newAngle;
	printf("Current angle: ");
	printInt(oldAngle);
	printf("\nGoal angle: ");
	goalAngle = degreeCalculation(2,1,2,2);
	printInt(goalAngle);	
	printf("\nCorrection angle: ");
	printInt(newAngle);
	printf("\n--------------------------------\n");
	oldAngle = angle;
	
		printf("\n----- TEST: ROTERA TILL 225 -----\n");
	newAngle = correctionAngleCalculation(2,5,2,5,oldAngle);
	angle = oldAngle + newAngle;
	printf("Current angle: ");
	printInt(oldAngle);
	printf("\nGoal angle: ");
	goalAngle = degreeCalculation(2,5,2,5);
	printInt(goalAngle);
	printf("\nCorrection angle: ");
	printInt(newAngle);
	printf("\n--------------------------------\n");
	oldAngle = angle;
	
	printf("\n----- TEST: ROTERA TILL 225 -----\n");
	newAngle = correctionAngleCalculation(2,5,2,5,oldAngle);
	angle = oldAngle + newAngle;
	printf("Current angle: ");
	printInt(oldAngle);
	printf("\nGoal angle: ");
	goalAngle = degreeCalculation(2,5,2,5);
	printInt(goalAngle);
	printf("\nCorrection angle: ");
	printInt(newAngle);
	printf("\n--------------------------------\n");
	oldAngle = angle;*/
	
		
	test = 0;
	}
	
	/* Infinite loop */
	while (1) 
	{

	}
}



