/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include "task_player2.h"



void task_player2(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 3000/portTICK_RATE_MS;
	printf("P2\n");
	while(1){
		//task_player2 PIO_PB26_IDX = Digital Pin 22
		ioport_set_pin_level(PIO_PB26_IDX, HIGH);

		xLastWakeTime = xTaskGetTickCount();
	
		
	volatile int j=0; /* makes sure j doesn't overflow */
	for (int i=0; i<50; i++) /* The delay counter */
	{

		j++; /* some easy predictable operation */
		
	}
	printf("give xSemaphorePlayer2\n");
	printf("end task_player1 EoL(2.2)\n");
	ioport_set_pin_level(PIO_PB26_IDX, LOW);
	vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	//xSemaphoreGive(xSemaphoreInterrupt);
	xSemaphoreGive(xSemaphorePlayer2);
	vTaskSuspend(NULL);
	}
}