/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include <asf.h>
#include "task_player2.h"
#include "lcdFunctions.h"
#include "lcdApplication.h"
#include "buttons.h"
#include "task_control.h"
#include "semphr.h"


void task_player2(void *pvParamters)
{
	printf("P2\n");
	while(1){
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 200/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	//printf("task_player2\n");

	
	//task_player2
	//PIO_PB26_IDX = Digital Pin 22
	volatile int j=0; /* makes sure j doesn't overflow */
	ioport_set_pin_level(PIO_PB26_IDX, LOW);
	for (int i=0; i<50; i++) /* The delay counter */
	{
		j++; /* some easy predictable operation */
		vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );	
	}
		ioport_set_pin_level(PIO_PB26_IDX, HIGH);
		printf("give xSemaphorePlayer2\n");
		xSemaphoreGive(xSemaphorePlayer2);
	}
}