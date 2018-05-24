/*
* task_styrning.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	
*/

#include "task_styrning.h"
#include "../xHandlerParameters.h"
#include "../Movement/Movement.h"
#include "../config/conf_AdaLovelace.h"
#include "../Movement/__vars.h"
#include "../Navigering/NAV_SENS_STYR.h"


#define xBlockTime 500

void task_styrning(void *pvParamters)
{
	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	while(1){
		vTaskDelay(xBlockTime);
		xLastWakeTime = xTaskGetTickCount();
		printf("task_styrning started\n");

		counter = 0; //shared with task_reglering
		check = 1; //shared with task_reglering
		f_auto = true;
		//printf("task_styrning: %x\n", f_auto );
		//printf("task_styrning: %x\n", &f_auto );
		vTaskResume(*(taskHandler->taskReglering));
		while(!isDone())
		{
			task_movement();
			printf("task_movement delay: %i\n", 50/portTICK_RATE_MS);
			vTaskDelay(50/portTICK_RATE_MS);		
		}	
		printf("task_styrning out\n");
		xSemaphoreGive(xSemaphoreStyrning);
		vTaskSuspend(NULL);	
	}
}