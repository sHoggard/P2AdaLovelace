/*
 * task_navigering.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *  Author: Jelena Novacic
 */ 

#include "task_navigering.h"
#include "Movement/Movement.h"
#include "../RunState.h"
#include "../xHandlerParameters.h"
#include "../Com/KOM_NAV.h"
#include "../Com/Extension.h"

#define xBlockTime 5


void task_navigering(void *pvParamters)
{
	printf("task_navigering\n");
	xHandlerParameters *taskHandler =  pvParamters;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	//check_Dist = 0;
	//check_PDMM = 1;	//bara test
	
	while(1)
	{
		vTaskDelay(xBlockTime);
		printf("Navigering\n");
		xLastWakeTime = xTaskGetTickCount();
		
		
		//--------------- Använd bara för att testa Navigering - Movement ----------------------
		//int j;
		//printf("Tryck 1 om TC0, 2 om TC1, 3 om TC2, 4 om TC3, 5 om TC4, 6 om TC5 ska köras");
		//scanf("%i", &j);
		//printf("\nDu tryckte: ");
		//printInt(j);
		//
		//testStyr(j);	
		//--------------------------------------------------------------------------------------

						
		float distance = 0.0;
		float goalAngle = 0.0;
		float robotRadius = 400.0;
	
		if(data_extension.type_object == GLASS){
			printf("data_extension.type_object == GLASS");
			if(currentState == TOWARDS_OBJECT_0){
				printf("TOWARDS_OBJECT_0");
				bool check_rotation = false;
				while(!check_rotation)
					{
						goalAngle = degreeCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot);
						printf("Roboten ska rotera till följande vinkel : ");
						printInt(goalAngle);
					
						distance = abs((distanceCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot))-robotRadius);
						printf("Roboten har följande avstånd till vinglaset : ");
						printInt(distance);
						
						if(distance <= 500){
							changeState(SCAN_OBJECT);
							check_rotation = true;
						}else if(distance > 500)
						{
							rotation_angle = 360 - goalAngle;
							rotate(200, rotation_angle);
						
							vTaskResume(*(taskHandler->taskStyrning));
							changeState(TOWARDS_OBJECT_1);
							check_rotation = true;
						}
					}
			}else if(currentState == TOWARDS_OBJECT_1){
				printf("TOWARDS_OBJECT_1");
				bool check_distance = false;
				while(!check_distance)
				{
					drive(300, distance);
					vTaskResume(*(taskHandler->taskStyrning));
				
					changeState(TOWARDS_OBJECT_0);
					check_distance = true;
				}
			}
			}else if(data_extension.type_object == BALL){
					printf("data_extension.type_object == BALL");
					if(currentState == TOWARDS_OBJECT_0){
						printf("TOWARDS_OBJECT_0");
						bool check_rotation = false;
						while(!check_rotation)
						{
							goalAngle = degreeCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot);
							printf("Roboten ska rotera till följande vinkel : ");
							printInt(goalAngle);
						
							distance = abs((distanceCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot))-robotRadius);
							printf("Roboten har följande avstånd till stålkulan : ");
							printInt(distance);
						
							if(distance <= 500){
								changeState(SCAN_OBJECT);
								check_rotation = true;
							}else if(distance > 500)
							{
								rotation_angle = 360 - goalAngle;
								rotate(200, rotation_angle);
								vTaskResume(*(taskHandler->taskStyrning));
								changeState(TOWARDS_OBJECT_1);
								check_rotation = true;
							}
						}
					}else if(currentState == TOWARDS_OBJECT_1){
						printf("TOWARDS_OBJECT_1");
						bool check_distance = false;
						while(!check_distance)
						{
							drive(300, distance);
							vTaskResume(*(taskHandler->taskStyrning));
						
							changeState(TOWARDS_OBJECT_0);
							check_distance = true;
						}
					}
			}else if(currentState == TOWARDS_BOX_0){
						printf("TOWARDS_BOX_0");
						bool check_rotation = false;
						while(!check_rotation)
						{
							goalAngle = degreeCalculation(x_koord_Box,x_koord_Robot,y_koord_Box,y_koord_Robot);
							printf("Roboten ska rotera till följande vinkel : ");
							printInt(goalAngle);
						
							distance = abs((distanceCalculation(x_koord_Box,x_koord_Robot,y_koord_Box,y_koord_Robot))-robotRadius);
							printf("Roboten har följande avstånd till lådan : ");
							printInt(distance);
						
							if(distance <= 500){
								changeState(SCAN_BOX);
								check_rotation = true;
							}else if(distance > 500)
							{
								rotation_angle = 360 - goalAngle;
								rotate(200, rotation_angle);
							
								changeState(TOWARDS_BOX_1);
								check_rotation = true;
							}
						}
			}else if(currentState == TOWARDS_BOX_1){
					printf("TOWARDS_BOX_1");
					bool check_distance = false;
					while(!check_distance)
					{
						drive(300, distance);
						vTaskResume(*(taskHandler->taskStyrning));
				
						changeState(TOWARDS_BOX_0);
						check_distance = true;
					}
				}
			printf("\nNavigering out");
			xSemaphoreGive(xSemaphoreNavigering);
			vTaskSuspend(NULL);
	}
}