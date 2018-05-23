/*
 * task_reglering.c
 *
 * Created: 2018-05-14 12:19:00
 *  Author: George
 */ 


#include "task_reglering.h"


#define xBlockTime 5

void task_reglering(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 20/portTICK_RATE_MS;
	printf("task_reglering started\n");
	check = 1;
	while(1){
		xLastWakeTime =  xTaskGetTickCount();
		if(isDone()){
			printf("check = 0\n");
			check = 0;
			vTaskSuspend(NULL);
		}
		else if (check)
		{
			printf("%i: \n", counter++);
			task_movement();
			task_regulate();
			printf("\n");
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
			task_movement();
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
			task_movement();
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
			task_movement();
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
			task_movement();
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		}		
	}
}