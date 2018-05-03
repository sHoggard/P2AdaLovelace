/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include "task_player2.h"

#define xBlockTime 1
//task_player2
void task_player2(void *pvParamters)
{
	int work = 200000;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("P2\n");
	while(1){
		vTaskDelay(xBlockTime);
		printf("P2\n");
		xLastWakeTime = xTaskGetTickCount();
	
		//PIO_PB26_IDX = Digital Pin 22
		volatile int j=0; /* makes sure j doesn't overflow */
		ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	
		for (int i=0; i<work; i++) /* The delay counter */
		{
			j++; /* some easy predictable operation */
		}
		ioport_set_pin_level(PIO_PB26_IDX, LOW);
		printf("give2\n");
		printf("EoL(task2)");
		xSemaphoreGive(xSemaphorePlayer2);
		while(1);
		vTaskSuspend(NULL);
	}
}