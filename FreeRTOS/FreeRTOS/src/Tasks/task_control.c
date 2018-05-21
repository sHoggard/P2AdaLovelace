/*
* task_control.c
*
* Created: 2018-02-01 11:25:38
*  Author: George Albert Florea
*  
*/

#include <asf.h>
#include "task_control.h"
#include "FreeRTOS.h"
#include "task.h"
#include "xHandlerParameters.h"
#include "semphr.h"


#define xBlockTime 5	//5ticks
portTickType xTimeStampTicks;
portTickType timeStart;

void task_control(void *pvParamters)
{

	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	//portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	//task_control
	// PIO_PC1_IDX, = Digital Pin 33
	
	
	while(1)
	{	
		//printf("task_control\n");
		xLastWakeTime = xTaskGetTickCount();
		
		//if(xSemaphoreTake(xSemaphoreKommunikation, 0) == pdTRUE){
			//printf("-\n");
			//printf("- xSemaphoreKommunikation\n");
			//vTaskResume(*(taskHandler->taskNavigering));
			//printf("- - - -\n");
		//}
		if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
			printf("-\n");
			printf("- xSemaphoreNavigering\n");	
			vTaskResume(*(taskHandler->taskSensor)); //denna ska anv�ndas i slut�ndan
			//vTaskResume(*(taskHandler->taskStyrning));	//denna �r bara f�r nav-styr-test	
			//vTaskResume(*(taskHandler->taskKommunikation));	//denna �r bara f�r kom-nav-test
			printf("- - - -\n");					
		}
		if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
			printf("-\n");
			printf("- xSemaphoreSensor\n");
			//vTaskResume(*(taskHandler->taskStyrning));	//denna ska anv�ndas i slut�ndan
			vTaskResume(*(taskHandler->taskNavigering));	//denna �r bara f�r nav-sens-test
			printf("- - - -\n");
		}
		//if(xSemaphoreTake(xSemaphoreStyrning, 0) == pdTRUE){
			//printf("- -\n");
			//printf("- xSemaphoreStyrning\n");
			////vTaskResume(*(taskHandler->taskKommunikation));	//denna ska anv�ndas i slut�ndan
			//vTaskResume(*(taskHandler->taskNavigering));	//denna �r bara f�r nav-styr-test
			//printf("- - - -\n");		
		//}

		//printf("end task_control\n");
		vTaskDelay(xBlockTime);	
	}
}