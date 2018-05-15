/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include "task_styrning.h"


#define xBlockTime 1

void task_styrning(void *pvParamters)
{
	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("P2\n");
	while(1){
		vTaskDelay(xBlockTime);
		printf("P2\n");
		xLastWakeTime = xTaskGetTickCount();

		volatile int j=0; /* makes sure j doesn't overflow */
		ioport_set_pin_level(PIO_PB26_IDX, HIGH);

		char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

		char buffer[20];
		int speed = 200;
		uint32_t start = time_tick_get();		
		drive(speed, 1000);		
		printf("speed: %i\n\n", speed);

		counter = 0;
		check = 0;
		//vTaskResume(*(taskHandler->taskTickMovement));
		while(check)
		{
			vTaskDelay(1/portTICK_RATE_MS);
		}	
		printf("delay%i\n", 2000/portTICK_RATE_MS);
		vTaskDelay(2000/portTICK_RATE_MS);
		
		ioport_set_pin_level(PIO_PB26_IDX, LOW);
		printf("give2\n");
		xSemaphoreGive(xSemaphoreStyrning);
		vTaskSuspend(NULL);	
		}
}