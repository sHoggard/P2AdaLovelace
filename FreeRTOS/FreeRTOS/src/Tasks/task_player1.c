/*
 * task_player1.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 */ 

#include "task_player1.h"

#define xBlockTime 1


void task_player1(void *pvParamters)
{
	printf("P1\n");
	int work = 500000;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	while(1){
		vTaskDelay(xBlockTime);
		printf("P1\n");
		xLastWakeTime = xTaskGetTickCount();
		//task_player1
		//PIO_PA15_IDX = Digital Pin 24
		ioport_set_pin_level(PIO_PA15_IDX, HIGH);
		volatile int j=0; /* makes sure j doesn't overflow */
		for (int i=0; i<work; i++) /* The delay counter */
		{
			j++; /* some easy predictable operation */
			//trigger interrupt (only for testing)
			if(j % 200000 == 0){
				if(ioport_get_pin_level(PIO_PC19_IDX) == HIGH)
					ioport_set_pin_level(PIO_PC19_IDX, LOW);
				else
					ioport_set_pin_level(PIO_PC19_IDX, HIGH);
			}
		
		}
		ioport_set_pin_level(PIO_PA15_IDX, LOW);
		printf("give1\n");
		printf("EoL(task1)");	
		xSemaphoreGive(xSemaphorePlayer1);
		vTaskSuspend(NULL);
	}
}
