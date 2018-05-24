/*
 * task_reglering.c
 *
 * Created: 2018-05-14 12:19:00
 *  Author: George
 */ 


#include "task_reglering.h"
#include "../Movement/Movement.h"


#define xBlockTime 5

void task_reglering(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("task_reglering started\n");
	check = 1;
	f_auto = true;
	
	//printf("task_reglering: %x\n", f_auto );
	//printf("task_reglering: %x\n", &f_auto );
	while(1){
		xLastWakeTime =  xTaskGetTickCount();
		if(isDone()){
			
			//printf("check = 0\n");
			
			printf("isDone: %x\n", f_auto );
			printf("isDone: %x\n", &f_auto );
			check = 0;
			printf("task_reglering out\n");
			vTaskSuspend(NULL);
		}
		else if (!isDone())
		{
			printf("%i: \n", counter++);
			printf("task_regulate\n");
			task_regulate();
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		}		
	}
}