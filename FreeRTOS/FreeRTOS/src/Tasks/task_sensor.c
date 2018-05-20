/*
 * task_sensor.c
 *
 * Created: 2018-05-15 10:03:01
 *  Author: Jelena
 */ 
#include "task_sensor.h"
#include "ADC/sampel_int.h"
#include "Sensor/Ultraljud.h"
#include "Movement/Movement.h"

#define xBlockTime 5

void initEdges()
{
	US_edgeLeft = -1;
	US_edgeRight = -1;
	US_objectCentre = -1;
	IR_edgeLeft = -1;
	IR_edgeRight = -1;
	IR_objectCentre = -1;
}

void task_sensor(void *pvParamters)
{
	printf("task_sensor started\n");
	//xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 20/portTICK_RATE_MS;
	
	int edgeState = 0;
	
	while(1){
		US_currentdistance = PulseIn();
		switch (edgeState)
		{
			case 0:
				initEdges();
				if (US_currentdistance > OBJECT_PROXIMITY && IR_currentdistance > OBJECT_PROXIMITY)
				{
					edgeState = 1;
				}
				break;
			case 1:
				if(US_edgeLeft == -1 && US_currentdistance < OBJECT_PROXIMITY){
					US_edgeLeft = getOrientation();
					edgeState = 2;
				}
				if(IR_edgeLeft == -1 && IR_currentdistance < OBJECT_PROXIMITY){
					IR_edgeLeft = getOrientation();
					edgeState = 2;
				}
				break;
			case 2:
				if(US_edgeRight == -1 && US_currentdistance > OBJECT_PROXIMITY){
					US_edgeRight = getOrientation();
					if (US_edgeLeft != -1)
					{
						if(US_edgeLeft > US_edgeRight)
						{
							US_edgeRight += HUMAN_FULL_ROTATION;
						}
						US_objectCentre = (US_edgeLeft+US_edgeRight)/2;
						US_objectCentre += US_OFFSET;
						US_objectCentre %= HUMAN_FULL_ROTATION;
						edgeState = 3;
					}
				}
				if(IR_edgeRight == -1 && IR_currentdistance > OBJECT_PROXIMITY){
					IR_edgeRight = getOrientation();
					if (IR_edgeLeft != -1)
					{
						if(IR_edgeLeft > IR_edgeRight)
						{
							IR_edgeRight += HUMAN_FULL_ROTATION;
						}
						IR_objectCentre = (IR_edgeLeft+IR_edgeRight)/2;
						IR_objectCentre += IR_OFFSET;
						IR_objectCentre %= HUMAN_FULL_ROTATION;
						edgeState = 3;
					}
				}
				break;
			case 3:
				edgeState = 0;
				stop();
				xSemaphoreGive(xSemaphoreSensor);
				//vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
				//while(1);
				vTaskSuspend(NULL);
				break;
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

