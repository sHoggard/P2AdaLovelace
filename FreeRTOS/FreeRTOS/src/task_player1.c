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
	printf("P1\n");
	while(1){
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 200/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	//printf("task_player1\n");
	
	//task_player1
	//PIO_PA15_IDX = Digital Pin 24
	volatile int j=0; /* makes sure j doesn't overflow */
	ioport_set_pin_level(PIO_PA15_IDX, LOW);
	
	
	
	ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	printf("P1, pinLevelsSet");
	printf("PB14 level: ");
	if(ioport_get_pin_level(PIO_PB14_IDX) == HIGH)
		printf("PB14 is HIGH");
	for (int i=0; i<50; i++) /* The delay counter */
	{
		ioport_set_pin_level(PIO_PA16_IDX, LOW);
		j++; /* some easy predictable operation */
		vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	}
	printf("give xSemaphorePlayer1\n");
	xSemaphoreGive(xSemaphorePlayer1);
	}
}
