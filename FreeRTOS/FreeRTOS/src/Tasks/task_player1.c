/*
 * task_player1.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 */ 

#include "task_player1.h"




void task_player1(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 3000/portTICK_RATE_MS;
	printf("P1\n");
	while(1){
		//task_player1
		//PIO_PA15_IDX = Digital Pin 24
		ioport_set_pin_level(PIO_PA15_IDX, HIGH);
		
		xLastWakeTime = xTaskGetTickCount();
		
	
		volatile int j=0; /* makes sure j doesn't overflow */
		for (int i=0; i<50; i++) /* The delay counter */
		{
			
			j++; /* some easy predictable operation */
			
		}
		
		printf("give xSemaphorePlayer1\n");
		printf("end task_player1 EoL(2.1)\n");
		ioport_set_pin_level(PIO_PA15_IDX, LOW);
		vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );	
		//xSemaphoreGive(xSemaphoreInterrupt);
		xSemaphoreGive(xSemaphorePlayer1);
		vTaskSuspend(NULL);
	}
}
