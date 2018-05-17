/*
 * task3.c
 *
 * Created: 2018-05-14 12:19:00
 *  Author: George
 */ 


#include "task_tickMovement.h"


#define xBlockTime 5000

void task_tickMovement(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("task_tickMovement\n");
	check = 1;
	while(1){
		xLastWakeTime =  xTaskGetTickCount();
		if(mode_movement == 's'){
			//printf("check = 0\n");
			check = 0;
			vTaskSuspend(NULL);
		}
		else if (check)
		{
			//fputs(clrCom, stdout);
			//puts(itoa(counterLeft, buffer, 10));
			//puts(itoa(counterRight, buffer, 10));
			//puts(itoa(orientation(), buffer, 10));
			//puts(itoa(regulated_speed.left, buffer, 10));
			//puts(itoa(regulated_speed.right, buffer, 10));
			//puts(itoa(regulated_speed.target, buffer, 10));
			////drive(speed, 0);
			//test_movement();
			//if (speed < 500)
			//{
			//speed++;
			//}
			printf("%i: \n", counter++);
			test_movement();
			printf("\n");
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		}		
	}
}