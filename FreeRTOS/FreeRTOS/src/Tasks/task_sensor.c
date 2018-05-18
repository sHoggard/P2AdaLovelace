/*
 * task_sensor.c
 *
 * Created: 2018-05-15 10:03:01
 *  Author: Jelena
 */ 
#include "task_sensor.h"

#define xBlockTime 5

void task_sensor(void *pvParamters)
{
	printf("task_sensor\n");
	//xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	
	while(1){
		if(check_Dist == 0){
			vTaskSuspend(NULL);
		}
		vTaskDelay(xBlockTime);
		printf("Sensor\n");
		xLastWakeTime = xTaskGetTickCount();
		delay_ms(500);
	if(check_Dist == 1){
		printf("\nDo some sensor calculations");
		//if done
		check_Dist = 0;
	}
	//ioport_set_pin_level(PIO_PB26_IDX, LOW);		??????
	printf("\nSensor out");
	xSemaphoreGive(xSemaphoreSensor);
	//vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	//while(1);
	vTaskSuspend(NULL);
	}
	
}

