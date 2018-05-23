
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

#define xBlockTime 5

void initEdges()
{
	US_edgeLeft = -1;
	US_edgeRight = -1;
	
	IR_edgeLeft = -1;
	IR_edgeRight = -1;
	
	objectCentre = -1;
}

void task_sensor(void *pvParamters)
{
	printf("task_sensor started\n");
	//xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 20/portTICK_RATE_MS;
	
	int edgeState = 0;
	
	while(1){
		vTaskDelay(xBlockTime);
		printf("Sensor\n");
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
					//vTaskResume(*(taskHandler->taskStyrning));
				}
				if(currentState == SCAN_OBJECT){
					changeState(CLOSE_OBJECT_0);
				}else{
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
				//vTaskResume(*(taskHandler->taskStyrning));
				if(checkIfMinima(sensor)){ //returns true 
					if(sensor == LEFT_SENSOR){
						//rotate(200, 360-LEFT_SENSOR_PLACEMENT);
					}
					else if(sensor == RIGHT_SENSOR){
						//rotate(200, 360-RIGHT_SENSOR_PLACEMENT);
					//vTaskResume(*(taskHandler->taskStyrning));
					}
					else{
							rotate(50, 2*rotateAngle); //searching for minima
							//vTaskResume(*(taskHandler->taskStyrning));
					}
					check_scan = true;	
				}
			}
			if(currentState == CLOSE_OBJECT_0){
				changeState(CLOSE_OBJECT_1);
			}else{
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
				//drive(50, 30);
				//vTaskResume(*(taskHandler->taskStyrning));
			}
			if(currentState == CLOSE_OBJECT_1){
				changeState(PICKUP);	
			}else{
				changeState(DROPOFF);
			}
			
		}
		
			printf("\ntask_sensor: SCAN_OBJECT\n");
			printf("\nKLART\n");
			
			xSemaphoreGive(xSemaphoreSensor);
			vTaskSuspend(NULL);
		
			//if(check_Dist == 1)
			//{
				//printf("\ntask_sensor: TOWARDS_OBJECT\n");
				//check_Dist = 0;
				////printf("\nSensor out");
				//xSemaphoreGive(xSemaphoreSensor);
				//vTaskSuspend(NULL);
				//
			//}
				
		//
		//US_currentdistance = PulseIn();
		//printf("%lu\n", US_currentdistance);
		//switch (edgeState)
		//{
			//case 0:
				//initEdges();
				//if (US_currentdistance > OBJECT_PROXIMITY && IR_currentdistance > OBJECT_PROXIMITY)
				//{
					//edgeState = 1;
					//objectCentre = -1;
				//}
				//break;
			//case 1:
				//if(US_edgeLeft == -1 && US_currentdistance < OBJECT_PROXIMITY){
					//US_edgeLeft = getOrientation();
					//edgeState = 2;
				//}
				//if(IR_edgeLeft == -1 && IR_currentdistance < OBJECT_PROXIMITY){
					//IR_edgeLeft = getOrientation();
					//edgeState = 2;
				//}
				//break;
			//case 2:
				//if(US_edgeRight == -1 && US_currentdistance > OBJECT_PROXIMITY){
					//US_edgeRight = getOrientation();
					//if (US_edgeLeft != -1)
					//{
						//if(US_edgeLeft > US_edgeRight)
						//{
							//US_edgeRight += HUMAN_FULL_ROTATION;
						//}
						//objectCentre = (US_edgeLeft+US_edgeRight)/2;
						//objectCentre += US_OFFSET;
						//objectCentre %= HUMAN_FULL_ROTATION;
						//edgeState = 3;
					//}
				//}
				//if(IR_edgeRight == -1 && IR_currentdistance > OBJECT_PROXIMITY){
					//IR_edgeRight = getOrientation();
					//if (IR_edgeLeft != -1)
					//{
						//if(IR_edgeLeft > IR_edgeRight)
						//{
							//IR_edgeRight += HUMAN_FULL_ROTATION;
						//}
						//objectCentre = (IR_edgeLeft+IR_edgeRight)/2;
						//objectCentre += IR_OFFSET;
						//objectCentre %= HUMAN_FULL_ROTATION;
						//edgeState = 3;
					//}
				//}
				//break;
			//case 3:
				//edgeState = 0;
				//stop();
				//break;
				//
				//
		//}
		//rotate(200, objectCentre); //rotera till objektet som detekterats
		
		
		//xSemaphoreGive(xSemaphoreSensor);
		//vTaskSuspend(NULL);
		

	//if(check_Dist == 1){
		//printf("\nDo some sensor calculations");
		////if done
		//check_Dist = 0;
	//}
	//ioport_set_pin_level(PIO_PB26_IDX, LOW);		??????
	
	}
	printf("\nSensor out");
	xSemaphoreGive(xSemaphoreSensor);
	////vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	////while(1);
	vTaskSuspend(NULL);
}