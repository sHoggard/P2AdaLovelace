/*
* task_styrning.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	
*/

#include "task_styrning.h"
#include "../xHandlerParameters.h"


#define xBlockTime 5

void task_styrning(void *pvParamters)
{
	 
	printf("task_styrning started\n");
	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("P2\n");
	while(1){
		vTaskDelay(xBlockTime); //hänger i tasken 200 000 ticks
		printf("Styrning\n");
		xLastWakeTime = xTaskGetTickCount();

		if(check_Dist == 0){
			
			
			printf("\nKör med navigering+positioneringssystem");
		}

		volatile int j=0; /* makes sure j doesn't overflow */
		ioport_set_pin_level(PIO_PB26_IDX, HIGH);

		char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

		char buffer[20];
		int speed = 200;
		uint32_t start = time_tick_get();		
		//drive(speed, 1000);
		
		
		//printf("speed: %i\n\n", speed);


		counter = 0;
		check = 1;
		vTaskResume(*(taskHandler->taskReglering));
		while(check)
		{
			task_movement();
			printf("delay%i\n", 50/portTICK_RATE_MS);
			vTaskDelay(50/portTICK_RATE_MS);
			
		}	
		
		
		//ioport_set_pin_level(PIO_PB26_IDX, LOW);
		printf("\nStyrning out");
		xSemaphoreGive(xSemaphoreStyrning);
		//while(1); //+hög prio
		//vTaskSuspendAll();
		vTaskSuspend(NULL);	
		}
}