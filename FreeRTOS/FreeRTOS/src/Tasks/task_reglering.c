/*
 * task3.c
 *
 * Created: 2018-05-14 12:19:00
 *  Author: George
 */ 


#include "task_reglering.h"


#define xBlockTime 5

void task_reglering(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("task_reglering\n");
	check = 1;
	while(1){
		xLastWakeTime =  xTaskGetTickCount();
		if(mode_movement == 's'){
			printf("check = 0\n");
			check = 0;
			vTaskSuspend(NULL);
		}
		else if (check)
		{
			printf("%i: \n", counter++);
			task_regulate();
			printf("\n");
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		}		
	}
}