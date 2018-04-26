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

#define xBlockTime 100
portTickType xTimeStampTicks;
portTickType timeStart;
uint32_t reactionTimePlayer1;
uint32_t reactionTimePlayer2;
bool player1btnPressed = false;
bool player2btnPressed = false;

void task_control(void *pvParamters)
{
	
	xHandlerParameters* taskHandler = (xHandlerParameters*) pvParamters;
	
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 1000/portTICK_RATE_MS;
	printf("- task_control first time\n");
	//task_control PIO_PC1_IDX, = Digital Pin 33
	while(1)
	{ioport_set_pin_level(PIO_PC1_IDX, HIGH);
		printf("- task_control\n");
		xLastWakeTime = xTaskGetTickCount();
		//Semaphore take task 1
		if(xSemaphoreTake(xSemaphorePlayer1, 0) == pdTRUE){
			printf("- xSemaphorePlayer1 ---\n");
			vTaskResume(*(taskHandler->taskplayer2));			
			//vTaskSuspend(*(taskHandler->taskplayer1));		
		}
		//Semaphore take task 2
		else if(xSemaphoreTake(xSemaphorePlayer2, 0) == pdTRUE){
			printf("- xSemaphorePlayer2 ---\n");
			vTaskResume(*(taskHandler->taskplayer1));	
			//vTaskSuspend(*(taskHandler->taskplayer2));
		}
		printf("task_control EoL(2)\n");
		ioport_set_pin_level(PIO_PC1_IDX, LOW);
		vTaskDelayUntil(&xLastWakeTime ,xTimeIncrement);	
	}
}
