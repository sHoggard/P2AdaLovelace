/*
 * task_navigering.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *  Author: Jelena Novacic
 */ 

#include "task_navigering.h"
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
				
				float distance = 0.0;
				float goalAngle = 0.0;
				float robotRadius = 400.0;
				
	
	while(1)
	{
		vTaskDelay(xBlockTime);
		printf("Navigering\n");
		xLastWakeTime = xTaskGetTickCount();
		/*
		
		printf("x_koord_Vinglas\n");
		printf( x_koord_Vinglas);

		printf("y_koord_Vinglas\n");
		printInt(y_koord_Vinglas);
		


		printf("\nx_koord_Kulan");
		printInt(x_koord_Kula);
			
		
		printf("y_koord_Kula");
		printf(y_koord_Kula);
		


		printf("\nx_koord_Robot\n");
		printInt(x_koord_Robot);
		
		
		
		printf("\ny_koord_Robot\n");
		printInt(y_koord_Robot);


		printf("\nx_koord_Box\n");
		printInt(x_koord_Box);
		
		printf("\ny_koord_Box\n");
		printInt(y_koord_Box);


		printf("\nx_koord_Kub\n");
		printf(x_koord_Kub);
		
		printf("\ny_koord_Kub\n");
		printf(y_koord_Kub);
		


		printf("\ncheck_PDMM\n");
		printf(check_PDMM);

		printf("\ncheck_Arm\n");
		printf(check_Arm);
*/
		printf("x_koord_Box: %i\n", x_koord_Box);
		printf("y_koord_Box: %i\n", y_koord_Box);
		printf("x_koord_Kub: %i\n", x_koord_Kub);
		printf("y_koord_Kub: %i\n", y_koord_Kub );
		printf("x_koord_Kula: %i\n", x_koord_Kula );
		printf("y_koord_Kula: %i\n", y_koord_Kula );
		printf("x_koord_Vinglas: %i\n", x_koord_Vinglas);
		printf("y_koord_Vinglas: %i\n", y_koord_Vinglas);
		printf("x_koord_Robot: %i\n", x_koord_Robot );
		printf("y_koord_Robot: %i\n", y_koord_Robot );
		
		
		//--------------- Anv�nd bara f�r att testa Navigering - Movement ----------------------
		//int j;
		//printf("Tryck 1 om TC0, 2 om TC1, 3 om TC2, 4 om TC3, 5 om TC4, 6 om TC5 ska k�ras");
		//scanf("%i", &j);
		//printf("\nDu tryckte: ");
		//printInt(j);
		//
		//testStyr(j);	
		//--------------------------------------------------------------------------------------

			
		if(data_extension.type_object == GLASS){
			printf("data_extension.type_object == GLASS\n");
			if(currentState == TOWARDS_OBJECT_0){
				printf("TOWARDS_OBJECT_0\n");
				bool check_rotation = false;
				while(!check_rotation)
					{
						goalAngle = degreeCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot);
						printf("Roboten ska rotera till f�ljande vinkel : ");
						printInt(goalAngle);
					printf("\n");
						distance = abs((distanceCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot))-robotRadius);
						printf("Roboten har f�ljande avst�nd till vinglaset : ");
						printInt(distance);
						printf("\n");
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
				printf("\n");
				bool check_distance = false;
				while(!check_distance)
				{
					drive(300, distance);
					vTaskResume(*(taskHandler->taskStyrning));
					printf("TOWARDS_OBJECT_0\n");
					changeState(TOWARDS_OBJECT_0);
					check_distance = true;
				}
			}
			}else if(data_extension.type_object == BALL){
					printf("data_extension.type_object == BALL");
					printf("\n");
					if(currentState == TOWARDS_OBJECT_0){
						printf("TOWARDS_OBJECT_0");
						bool check_rotation = false;
						while(!check_rotation)
						{
							goalAngle = degreeCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot);
							printf("Roboten ska rotera till f�ljande vinkel : ");
							printInt(goalAngle);
						printf("\n");
							distance = abs((distanceCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot))-robotRadius);
							printf("Roboten har f�ljande avst�nd till st�lkulan : ");
							printInt(distance);
						printf("\n");
							if(distance <= 500){
								changeState(SCAN_OBJECT);
								printf("SCAN_OBJECT\n");
								check_rotation = true;
							}else if(distance > 500)
							{
								rotation_angle = 360 - goalAngle;
								rotate(200, rotation_angle);
								vTaskResume(*(taskHandler->taskStyrning));
								changeState(TOWARDS_OBJECT_1);
								printf("TOWARDS_OBJECT_1\n");
								check_rotation = true;
							}
						}
					}else if(currentState == TOWARDS_OBJECT_1){
						printf("TOWARDS_OBJECT_1\n");
						bool check_distance = false;
						while(!check_distance)
						{
							drive(300, distance);
							vTaskResume(*(taskHandler->taskStyrning));
							printf("TOWARDS_OBJECT_0\n");
							changeState(TOWARDS_OBJECT_0);
							check_distance = true;
						}
					}
			}else if(currentState == TOWARDS_BOX_0){
						printf("TOWARDS_BOX_0\n");
						bool check_rotation = false;
						while(!check_rotation)
						{
							goalAngle = degreeCalculation(x_koord_Box,x_koord_Robot,y_koord_Box,y_koord_Robot);
							printf("Roboten ska rotera till f�ljande vinkel : ");
							printInt(goalAngle);
						printf("\n");
							distance = abs((distanceCalculation(x_koord_Box,x_koord_Robot,y_koord_Box,y_koord_Robot))-robotRadius);
							printf("Roboten har f�ljande avst�nd till l�dan : ");
							printInt(distance);
						printf("\n");
							if(distance <= 500){
								printf("SCAN_BOX\n");
								changeState(SCAN_BOX);
								check_rotation = true;
							}else if(distance > 500)
							{
								rotation_angle = 360 - goalAngle;
								rotate(200, rotation_angle);
							printf("TOWARDS_BOX_1\n");
								changeState(TOWARDS_BOX_1);
								check_rotation = true;
							}
						}
			}else if(currentState == TOWARDS_BOX_1){
					printf("TOWARDS_BOX_1\n");
					bool check_distance = false;
					while(!check_distance)
					{
						drive(300, distance);
						vTaskResume(*(taskHandler->taskStyrning));
						printf("TOWARDS_BOX_0\n");
						changeState(TOWARDS_BOX_0);
						check_distance = true;
					}
				}
			printf("Navigering out\n");
			xSemaphoreGive(xSemaphoreNavigering);
			vTaskSuspend(NULL);
	}
}