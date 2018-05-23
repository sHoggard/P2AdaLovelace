
/*
 * task_sensor.c
 *
 * Created: 2018-05-15 10:03:01
 *  Author: Jelena
 */ 
#include "task_sensor.h"
#include "ADC/sampel_int.h"
#include "Sensor/Ultraljud.h"
#include "UltrasonicSensor/Ultraljud.h"
#include "Movement/Movement.h"
#include "../xHandlerParameters.h"

#define xBlockTime 5

void task_sensor(void *pvParamters)
{
	printf("task_sensor started\n");
	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 20/portTICK_RATE_MS;
		
	while(1){
		vTaskDelay(xBlockTime);
		printf("task_sensor\n");
		xLastWakeTime = xTaskGetTickCount();
		
		if(currentState == SCAN_OBJECT || currentState == SCAN_BOX){
			bool check_scan = false;
			sensor = 0;
			while(!check_scan)
			{
				//scan if object found
				if(pulseIn(LEFT_SENSOR) <=500){
					sensor = LEFT_SENSOR;
					check_scan = true;
				}else if(pulseIn(CENTRE_SENSOR) <=500){
					sensor = CENTRE_SENSOR;
					check_scan = true;
				}else if(pulseIn(RIGHT_SENSOR) <=500){
					sensor = RIGHT_SENSOR;
					check_scan = true;
					
				}else{
					//object not found, rotate 5 degrees
					rotate(50,5);
					vTaskResume(*(taskHandler->taskStyrning));
				}
				if(currentState == SCAN_OBJECT){
					printf("\ntask_sensor: SCAN_OBJECT\n");
					printf("\changeState(CLOSE_OBJECT_0)\n");
					changeState(CLOSE_OBJECT_0);
				}else{
					printf("\ntask_sensor: SCAN_BOX\n");
					printf("\changeState(CLOSE_BOX_1)\n");
					changeState(CLOSE_BOX_1);
				}			
			}
		}
		else if(currentState == CLOSE_OBJECT_0 || currentState == CLOSE_BOX_0){
			bool check_scan = false;
			int rotateAngle = 5;
			while(!check_scan)
			{
				rotate(50, rotateAngle); //searching for minima
				vTaskResume(*(taskHandler->taskStyrning));
				if(checkIfMinima(sensor)){ //returns true if minima found
					if(sensor == LEFT_SENSOR){
						//rotate(200, 360-LEFT_SENSOR_PLACEMENT);
						vTaskResume(*(taskHandler->taskStyrning));
					}
					else if(sensor == RIGHT_SENSOR){
						//rotate(200, 360-RIGHT_SENSOR_PLACEMENT);
						vTaskResume(*(taskHandler->taskStyrning));
					}
					
					check_scan = true;	
				}
				else{
					rotate(50, 2*rotateAngle); //searching for minima
					vTaskResume(*(taskHandler->taskStyrning));
				}
			}
			if(currentState == CLOSE_OBJECT_0){
				printf("\ntask_sensor: CLOSE_OBJECT_0\n");
				printf("\changeState(CLOSE_OBJECT_1)\n");
				changeState(CLOSE_OBJECT_1);
			}else{
				printf("\ntask_sensor: CLOSE_BOX_0\n");
				printf("\changeState(CLOSE_BOX_1)\n");
				changeState(CLOSE_BOX_1);
			}
				
		}
		
		else if(currentState == CLOSE_OBJECT_1 || currentState == CLOSE_BOX_1){
			bool check_scan = false;
			while(!check_scan)
			{
				//if(pulseIn(CENTRE_SENSOR) > idealDistanceToObject)){
					//check_scan = true;
				//}
				drive(50, 30);
				vTaskResume(*(taskHandler->taskStyrning));
			}
			if(currentState == CLOSE_OBJECT_1){
				printf("\ntask_sensor: CLOSE_OBJECT_1\n");
				printf("\changeState(PICKUP)\n");
				changeState(PICKUP);	
			}else{
				printf("\ntask_sensor: CLOSE_BOX_1\n");
				printf("\changeState(DROPOFF)\n");
				changeState(DROPOFF);
			}
			
		}
			printf("\nSensor out");
			xSemaphoreGive(xSemaphoreSensor);
			vTaskSuspend(NULL);
	}
}