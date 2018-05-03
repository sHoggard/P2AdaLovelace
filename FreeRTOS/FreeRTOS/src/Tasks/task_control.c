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


#define xBlockTime 5
portTickType xTimeStampTicks;
portTickType timeStart;

void task_control(void *pvParamters)
{

	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	//portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	//task_control
	// PIO_PC1_IDX, = Digital Pin 33
	
	printf("Address stored in &taskHandler: %x\n", &taskHandler );
	printf("Address stored in taskHandler: %x\n", taskHandler );
	printf("Address stored in &taskHandler->taskplayer1: %x\n", &taskHandler->taskplayer1 );
	printf("Address stored in &taskHandler->taskplayer2: %x\n", &taskHandler->taskplayer2 );
	printf("Address stored in taskHandler->taskplayer1: %x\n", taskHandler->taskplayer1 );
	printf("Address stored in taskHandler->taskplayer2: %x\n", taskHandler->taskplayer2 );
	while(1)
	{	
		ioport_set_pin_level(PIO_PC1_IDX, HIGH);

		//printf("task_control\n");
		xLastWakeTime = xTaskGetTickCount();
		if(xSemaphoreTake(xSemaphorePlayer1, 0) == pdTRUE){
			printf("-\n");
			//printf("- xSemaphorePlayer1\n");
			vTaskSuspend(*(taskHandler->taskplayer1));	
			vTaskResume(*(taskHandler->taskplayer2));		
			printf("- - - -\n");					
		}
		if(xSemaphoreTake(xSemaphorePlayer2, 0) == pdTRUE){
			printf("- -\n");
			vTaskSuspend(*(taskHandler->taskplayer2));
			vTaskResume(*(taskHandler->taskplayer1));	
			printf("- - - -\n");		
		}

		printf("end task_control\n");
		ioport_set_pin_level(PIO_PC1_IDX, LOW);
		vTaskDelay(xBlockTime);
		printf("EoL(task_control)");	
	}
}