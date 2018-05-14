/*
 * task_player1.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 */ 

#include "task_player1.h"

#define xBlockTime 1


void task_player1(void *pvParamters)
{
	printf("P1\n");
	//int work = 500000;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	while(1){
		vTaskDelay(xBlockTime);
	printf("P1\n");
	xLastWakeTime = xTaskGetTickCount();
	//task_player1

	int i = 0;

	float goalAngle = 0.0;
	float oldAngle = 0.0;
	float newAngle = 0.0;
	float angle = 0.0;

	i++;
	
	int test = 1;
	while(test == 1){
	/* -----------------------------------------------------------------------------------
				NAVIGERING - TEST	
	--------------------------------------------------------------------------------------*/
	
	//----------Test f?r att kontrollera s? att grad-ber?kning fr?n radianer funkar----------
	float degrees = 0.0;
	float radians [] = {(PI/6), (PI/4), (PI/3), (PI/2), (PI), ((3*PI)/2), (2*PI)};
	char rads [7][9] = {"PI/6 = ", "PI/4 = ", "PI/3 = ", "PI/2 = ", "PI = ", "3PI/2 = ", "2PI = "};
	for (int i=0; i < 7; i++){
		degrees = rad2deg(radians[i]);
		printf(rads[i]);
		printInt(degrees);
	}
	
	
	//----------Test f?r avst?ndsber?kningar----------
	float distance = 0.0;
	distance = distanceCalculation(2,2,2,5); //3 l?ngdenheter
	printf("Roboten i (2,5) har f?ljande avst?nd till objektet i (2,2) : ");
	printInt(distance);
	distance = distanceCalculation(2,4,2,2); //2 l?ngdenheter
	printf("\nRoboten i (4,2) har f?ljande avst?nd till objektet i (2,2) : ");
	printInt(distance);
	distance = distanceCalculation(2,2,2,2); //0 l?ngdenheter
	printf("\nRoboten i (2,2) har f?ljande avst?nd till objektet i (2,2) : ");
	printInt(distance);
	distance = distanceCalculation(2,10,2,2); //8 l?ngdenheter
	printf("\nRoboten i (10,2) har f?ljande avst?nd till objektet i (2,2) : ");
	printInt(distance);
	
	
	//----------Test f?r 1a kvadranten----------
	goalAngle = degreeCalculation(2,1,2,2); //0 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,1,2,1);	//45 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,5,1);	//90 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,0,2,1);	//26grader
	printInt(goalAngle);
	
	
	//----------Test f?r 2a kvadranten----------
	goalAngle = degreeCalculation(2,4,2,2);	//180 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,3,2,1);	//135 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,5,1);	//90 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,6,2,0);	//116 grader
	printInt(goalAngle);
	
	
	//----------Test f?r 3e kvadranten----------
	goalAngle = degreeCalculation(2,4,2,3);	//243 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,2,5);	//270 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,3,1,5);	//194 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,5,2,5);	//225 grader
	printInt(goalAngle);
	
	
	//----------Test f?r 4e kvadranten----------
	goalAngle = degreeCalculation(2,1,1,3);	//296 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,2,2,5);	//270 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(2,0,1,6);	//291 grader
	printInt(goalAngle);
	goalAngle = degreeCalculation(8,2,6,7);	//350 grader
	printInt(goalAngle);
	
	
	//----------Test f?r ber?kning av korrigeringsvinkel----------
	printf("\n----- TEST: ROTERA TILL 180 -----\n");
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
	oldAngle = angle;
	
		
	test = 0;
	}

	ioport_set_pin_level(PIO_PA15_IDX, LOW);
	printf("give1\n");
	xSemaphoreGive(xSemaphorePlayer1);
	//vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	vTaskSuspend(NULL);
	}
}
