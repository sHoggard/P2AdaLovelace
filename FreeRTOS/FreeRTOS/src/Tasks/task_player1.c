/*
 * task_player1.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 */ 

#include "task_player1.h"

#define xBlockTime 5


void task_player1(void *pvParamters)
{
	printf("P1\n");
	int work = 150000;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	while(1){
		vTaskDelay(xBlockTime);
	printf("P1\n");
	xLastWakeTime = xTaskGetTickCount();
	//printf("task_player1\n");
	
	//task_player1
	//PIO_PA15_IDX = Digital Pin 24
	volatile int j=0; /* makes sure j doesn't overflow */
	ioport_set_pin_level(PIO_PA15_IDX, HIGH);
	
	//ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	//printf("P1, pinLevelsSet");
	//printf("PB14 level: ");
	/*if(ioport_get_pin_level(PIO_PB14_IDX) == HIGH)
		printf("PB14 is HIGH");*/
	for (int i=0; i<work; i++) /* The delay counter */
	{
		j++; /* some easy predictable operation */
		
	}
	ioport_set_pin_level(PIO_PA15_IDX, LOW);
	printf("give1\n");
	xSemaphoreGive(xSemaphorePlayer1);
	//vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	vTaskSuspend(NULL);
	
	
	}
}
