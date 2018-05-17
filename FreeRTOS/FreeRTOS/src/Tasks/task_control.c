/*
* task_control.c
*
* Created: 2018-02-01 11:25:38
*  Author: George Albert Florea
*  Author: Benjamin Sejdic
*/

#include <asf.h>
#include "task_control.h"
#include "FreeRTOS.h"
#include "task.h"
#include "xHandlerParameters.h"
#include "semphr.h"


#define xBlockTime 5000	//5ticks
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
		if(xSemaphoreTake(xSemaphoreKommunikation, 0) == pdTRUE){
			printf("-\n");
			printf("- xSemaphoreKommunikation\n");
			vTaskResume(*(taskHandler->taskNavigering));
			printf("- - - -\n");
		}
		if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
			printf("-\n");
			printf("- xSemaphoreNavigering\n");	
			vTaskResume(*(taskHandler->taskSensor));		
			printf("- - - -\n");					
		}
		if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
			printf("-\n");
			printf("- xSemaphoreSensor\n");
			vTaskResume(*(taskHandler->taskStyrning));
			printf("- - - -\n");
		}
		if(xSemaphoreTake(xSemaphoreStyrning, 0) == pdTRUE){
			printf("- -\n");
			printf("- xSemaphoreStyrning\n");
			vTaskResume(*(taskHandler->taskKommunikation));	
			printf("- - - -\n");		
		}

		//printf("end task_control\n");
		vTaskDelay(xBlockTime);	
	}
}