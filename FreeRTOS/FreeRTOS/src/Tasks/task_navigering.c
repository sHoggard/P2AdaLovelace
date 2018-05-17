/*
 * task_player1.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 */ 

#include "task_navigering.h"
#include "Movement/Movement.h"

#define xBlockTime 5000


void task_navigering(void *pvParamters)
{
	printf("task_navigering\n");
	//int work = 500000;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	while(1){
		vTaskDelay(xBlockTime);
		printf("Navigering\n");
		xLastWakeTime = xTaskGetTickCount();
		
		float distance = 0.0;
		float goalAngle = 0.0;
	
	if(check_Dist == 1){
		vTaskSuspend(NULL);
	}
		if(check_PDMM == 1){
			distance = distanceCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot); 
			printf("Roboten har följande avstånd till stålkulan : ");
			printInt(distance);
			if(distance <= 50){
				//sätt navigering i vila och kör sensorer
				check_Dist = 1;
			}
			goalAngle = degreeCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot);
			printf("Roboten ska rotera till följande vinkel : ");
			printInt(goalAngle);
			rotation_angle = goalAngle;
			
			//Till styrning
			rotate(200, rotation_angle);
			
			
		}
	
		if(check_PDMM == 0){
			distance = distanceCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot);
			printf("Roboten har följande avstånd till viglaset : ");
			printInt(distance);
			if(distance <= 50){
				//sätt navigering i vila och kör sensorer
				check_Dist = 1;
				
			}
			goalAngle = degreeCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot);
			printf("Roboten ska rotera till följande vinkel : ");
			printInt(goalAngle);
			rotation_angle = goalAngle;
		}

	ioport_set_pin_level(PIO_PA15_IDX, LOW);		//what is this?
	
	printf("\nNavigering out");
	xSemaphoreGive(xSemaphoreNavigering);
	//vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	vTaskSuspend(NULL);
	}
}
