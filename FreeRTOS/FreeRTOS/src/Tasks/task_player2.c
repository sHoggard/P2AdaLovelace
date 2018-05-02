/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include "task_player2.h"

#define xBlockTime 5

void task_player2(void *pvParamters)
{
	int work = 10000;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("P2\n");
	while(1){
		vTaskDelay(xBlockTime);
	printf("P2\n");
	xLastWakeTime = xTaskGetTickCount();
	//printf("task_player2\n");

	
	//task_player2
	//PIO_PB26_IDX = Digital Pin 22
	volatile int j=0; /* makes sure j doesn't overflow */
	ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	
		
		
	//ioport_set_pin_level(PIO_PB27_IDX, LOW);
	//printf("PB14 level: ");
	//if(ioport_get_pin_level(PIO_PB14_IDX) != HIGH)
	//	printf("PB14 is LOW");
	
	//printf("P2, pinLevelsSet");
	for (int i=0; i<work; i++) /* The delay counter */
	{
		j++; /* some easy predictable operation */
		//vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
		
	}
	ioport_set_pin_level(PIO_PB26_IDX, LOW);
	printf("give2\n");
	xSemaphoreGive(xSemaphorePlayer2);
	vTaskSuspend(NULL);

	
	}
}