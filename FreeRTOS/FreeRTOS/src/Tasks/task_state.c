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
	//task_state
	// PIO_PC1_IDX, = Digital Pin 33
	
	currentState = STARTUP;
	
	while(1)
	{	
		//printf("task_state\n");
		xLastWakeTime = xTaskGetTickCount();
				
		switch(currentState)
		{
			case STARTUP: 
				
			break;	
			case TOWARDS_OBJECT_0:
				if(xSemaphoreTake(xSemaphoreKommunikation, 0) == pdTRUE){
					printf("- xSemaphoreKommunikation\n");
					vTaskResume(*(taskHandler->taskNavigering));
				}
			break;
			case TOWARDS_OBJECT_1:
				if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
					printf("- xSemaphoreNavigering\n");
					vTaskResume(*(taskHandler->taskNavigering));
				}
				
			break;
			case SCAN_OBJECT:
			if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
				printf("- xSemaphoreNavigering\n");
				vTaskResume(*(taskHandler->taskSensor));
			}
			break;
			case CLOSE_OBJECT_0:
			break;
			case CLOSE_OBJECT_1:
			break;
			case PICKUP:
			break;
			case TOWARDS_BOX_0:
			break;
			case TOWARDS_BOX_1:
			break;
			case SCAN_BOX:
			break;
			case CLOSE_BOX_0:
			break;
			case CLOSE_BOX_1:
			break;
			case DROPOFF:
			break;
		}
		
		
		//if(xSemaphoreTake(xSemaphoreNavigering, 0) == pdTRUE){
			//printf("-\n");
			//printf("- xSemaphoreNavigering\n");	
			//vTaskResume(*(taskHandler->taskSensor)); //denna ska användas i slutändan
			////vTaskResume(*(taskHandler->taskStyrning));	//denna är bara för nav-styr-test	
			////vTaskResume(*(taskHandler->taskKommunikation));	//denna är bara för kom-nav-test
			//printf("- - - -\n");					
		//}
		//if(xSemaphoreTake(xSemaphoreSensor, 0) == pdTRUE){
			//printf("-\n");
			//printf("- xSemaphoreSensor\n");
			////vTaskResume(*(taskHandler->taskStyrning));	//denna ska användas i slutändan
			//vTaskResume(*(taskHandler->taskNavigering));	//denna är bara för nav-sens-test
			//printf("- - - -\n");
		//}
		////if(xSemaphoreTake(xSemaphoreStyrning, 0) == pdTRUE){
			////printf("- -\n");
			////printf("- xSemaphoreStyrning\n");
			//////vTaskResume(*(taskHandler->taskKommunikation));	//denna ska användas i slutändan
			////vTaskResume(*(taskHandler->taskNavigering));	//denna är bara för nav-styr-test
			////printf("- - - -\n");		
		////}

		//printf("end task_control\n");
		vTaskDelay(xBlockTime);	
	}
}

void changeState(int newState)
{
	currentState = newState;
}