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
		printf("Nu har navigeringen startat task_sensor och satt den i rotation för scanning");
	
		
		if (check_Dist == 0)
		{
			printf("\ntask_sensor: SCAN_OBJECT\n");
			printf("\nKLART\n");
			
			xSemaphoreGive(xSemaphoreSensor);
			vTaskSuspend(NULL);
		}
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

