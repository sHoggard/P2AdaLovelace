/*
 * task_player1.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 */ 

#include <asf.h>
#include "task_player1.h"
#include "lcdFunctions.h"
#include "lcdApplication.h"
#include "buttons.h"
#include "task_control.h"
#include "semphr.h"




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
	for (int i=0; i<50; i++) /* The delay counter */
	{
		j++; /* some easy predictable operation */
		vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	}
	ioport_set_pin_level(PIO_PA15_IDX, HIGH);
	printf("give xSemaphorePlayer1\n");
	xSemaphoreGive(xSemaphorePlayer1);
	}
}
