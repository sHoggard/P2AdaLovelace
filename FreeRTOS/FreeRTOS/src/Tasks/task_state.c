/*
* task_control.c
*
* Created: 2018-02-01 11:25:38
*  Author: George Albert Florea
*  
*/

#include <asf.h>
#include "task_state.h"
#include "FreeRTOS.h"
#include "task.h"
#include "xHandlerParameters.h"
#include "semphr.h"
#include "RunState.h"


#define xBlockTime 5	//5ticks
portTickType xTimeStampTicks;
portTickType timeStart;

void task_state(void *pvParamters)
{

	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	//portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	currentState = STARTUP;
	
	while(1)
	{	
		printf("task_state\n");
		xLastWakeTime = xTaskGetTickCount();
		switch(currentState)
		{
			case STARTUP: 
				if(xSemaphoreTake(xSemaphoreStyrning, 0) == pdTRUE){
					printf("- xSemaphoreStyrning\n");
					printf("- resume taskKommunikation\n");
					vTaskResume(*(taskHandler->taskKommunikation));
				}
				break;	
			case TOWARDS_OBJECT_0:
				if(xSemaphoreTake(xSemaphoreKommunikation, 0) == pdTRUE){
					printf("- xSemaphoreKommunikation\n");
					printf("- resume taskNavigering\n");
					vTaskResume(*(taskHandler->taskNavigering));
				}
				break;
			case TOWARDS_OBJECT_1:
				if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
					printf("- xSemaphoreNavigering\n");
					printf("- resume taskNavigering\n");
					vTaskResume(*(taskHandler->taskNavigering));
				}
				break;
			case SCAN_OBJECT:
				if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
					printf("- xSemaphoreNavigering\n");
					printf("- resume taskSensor\n");
					vTaskResume(*(taskHandler->taskSensor));
				}
				break;
			case CLOSE_OBJECT_0:
				if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
					printf("- xSemaphoreSensor\n");
					printf("- resume taskSensor\n");
					vTaskResume(*(taskHandler->taskSensor));
				}
				break;
			case CLOSE_OBJECT_1:
				if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
					printf("- xSemaphoreSensor\n");
					printf("- resume taskSensor\n");
					vTaskResume(*(taskHandler->taskSensor));
				}
				break;
			case PICKUP:
			if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
				printf("- xSemaphoreSensor\n");
				printf("- resume taskKommunikation\n");
				vTaskResume(*(taskHandler->taskKommunikation));
			}
			break;
			case TOWARDS_BOX_0:
				if(xSemaphoreTake(xSemaphoreKommunikation, 0) == pdTRUE){
					printf("- xSemaphoreKommunikation\n");
					printf("- resume taskNavigering\n");
					vTaskResume(*(taskHandler->taskNavigering));
				}
				break;
			case TOWARDS_BOX_1:
				if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
					printf("- xSemaphoreNavigering\n");
					printf("- resume taskNavigering\n");
					vTaskResume(*(taskHandler->taskNavigering));
				}
				break;
			case SCAN_BOX:
				if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
					printf("- xSemaphoreNavigering\n");
					printf("- resume taskSensorer\n");
					vTaskResume(*(taskHandler->taskSensor));
				}
				break;
			case CLOSE_BOX_0:
				if(xSemaphoreTake(xSemaphoreKommunikation, 0) == pdTRUE){
					printf("- xSemaphoreKommunikation\n");
					printf("- resume taskNavigering\n");
					vTaskResume(*(taskHandler->taskNavigering));
				}
				break;
			case CLOSE_BOX_1:
				if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
					printf("- xSemaphoreSensorer\n");
					printf("- resume taskSensorer\n");
					vTaskResume(*(taskHandler->taskSensor));
				}
				break;
			case DROPOFF:
				if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
					printf("- xSemaphoreSensorer\n");
					printf("- resume taskKommunikation\n");
					vTaskResume(*(taskHandler->taskKommunikation));
				}
				break;
		}
		vTaskDelay(xBlockTime);	
	}
}

void changeState(int newState){
	printf("tast_state: changeState()");
	currentState = newState;
}