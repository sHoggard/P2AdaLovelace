/*
 * task_navigering.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *  Author: Jelena Novacic
 */ 

#include "task_navigering.h"
#include "Movement/Movement.h"

#define xBlockTime 5


void task_navigering(void *pvParamters)
{
	printf("task_navigering started\n");
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	check_Dist = 0;
	check_PDMM = 1;	//bara test
	
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
	
		if(check_PDMM == 1)
		{
			//--------------- Test för NAV-SENS ---------------------------------------------------------
				int j;
				printf("Tryck 1 om TC0, 2 om TC1 ska köras");
				scanf("%i", &j);
				printf("\nDu tryckte: ");
				printInt(j);
				
				if(j == 1)	//Sensor tar över
				{
					check_Dist = 0;
					printf("\ntask_navigering: switch to SCAN_OBJECT\n");
				}
					
				if(j == 2)	//Navigering aktiv igen
				{
					check_Dist = 1;
					printf("\ntask_navigering: TOWARDS_OBJECT\n");
					//printf("\nNavigering out");
					
					//xSemaphoreGive(xSemaphoreSensor);
					//vTaskSuspend(NULL);
				}
			//------------------------------------------------------------------------------------------

			
			
			//--------------- Test för KOM-NAV ---------------------------------------------------------
			
			//if(testWhat == 0)	//TC0
			//{
				//printf("\nTesting communication data transfer to navigation\n");
				//printInt(testWhat);
				//
				//printf("\nStålkulans x-koordinat är: ");
				//printInt(x_koord_Kula);
				//printf("\nStålkulans y-koordinat är: ");
				//printInt(y_koord_Kula);
				//printf("\nRobotens x-koordinat är: ");
				//printInt(x_koord_Robot);
				//printf("\nRobotens y-koordinat är: ");
				//printInt(y_koord_Robot);
			//}
			//
			//if(testWhat == 1)	//TC1
			//{
				//printf("\nTesting distance calculation\n");
				//printInt(testWhat);
				//distance = (distanceCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot))*10;
				//printf("Roboten har följande avstånd (i mm) till stålkulan : ");
				//printInt(distance);
			//}
			//
			//if(testWhat == 2)	//TC2
			//{
				//printf("\nTesting angle calculation\n");
				//printInt(testWhat);
				//goalAngle = degreeCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot);
				//printf("Roboten ska rotera till följande vinkel : ");
				//printInt(goalAngle);
			//}
				
			//------------------------------------------------------------------------------------------
			
			//--------------- Test för NAV-MOVE --------------------------------------------------------
			
			//if(testWhat == 0)	//testa rotation	TC0-TC3
			//{
				//printf("Testing rotation");
				//printInt(testWhat);
				//goalAngle = degreeCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot);
				//printf("Roboten ska rotera till följande vinkel : ");
				//printInt(goalAngle);
				//rotation_angle = 360 - goalAngle;
				//
				//rotate(200, rotation_angle);	//kommenterat pga ej uppdaterd movement
			//}
			//
			//if(testWhat == 1)	//testa köra	TC4
			//{
				//printf("Testing drive");
				//printInt(testWhat);
				//
				//distance = (distanceCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot))*10;
				//printf("Roboten har följande avstånd till stålkulan : ");
				//printInt(distance);
				//
				////rotation_angle = 0.0;
				////rotate(200, rotation_angle);	//kommenterat pga ej uppdaterd movement
				//drive(200, distance);			//kommenterat pga ej uppdaterd movement
			//}
			//
			//if(testWhat == 2)	//testa köra rakt, vända tillbaka, hamna i startposition	TC5
			//{
				//printf("Testing combination");
				//printInt(testWhat);
				////goalAngle = degreeCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot);
				//printf("Roboten ska rotera till följande vinkel : ");
				//printInt(goalAngle);
				////rotation_angle = goalAngle;
				//
				//rotation_angle = (getOrientation() + 180);
				//
				//distance = 1000;
				////distance = (distanceCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot))*10;
				//printf("Roboten har följande avstånd till stålkulan : ");
				//printInt(distance);
				//
				//drive(200, distance);
				//
				//xSemaphoreGive(xSemaphoreNavigering);
				////vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
				//vTaskSuspend(NULL);
				//
				//rotate(200, rotation_angle);	
				//
				//xSemaphoreGive(xSemaphoreNavigering);
				//vTaskSuspend(NULL);
				//
				//drive(200, distance);			
			//}
			
			//xSemaphoreGive(xSemaphoreNavigering);
			////vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
			//vTaskSuspend(NULL);
			//---------------------------------------------------------------------------------------------
				//rotate(200,-1);	//sätt i rotation för scanning
				printf("\nNavigering out");
				xSemaphoreGive(xSemaphoreNavigering);
				//vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
				
				vTaskSuspend(NULL);
		}
	
	//printf("\nNavigering out");
	//xSemaphoreGive(xSemaphoreNavigering);
	////vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
	//vTaskSuspend(NULL);
			
	}
}
			
//--------------- Test för NAV-MOVE --------------------------------------------------------	
//void testStyr(int typo)
//{
	//double  x1=0.0;
	//double  x2=0.0;
	//double x3=0.0;
	//double  x4=0.0;
	//double  x5; //kulans testpos x
	//double  x6;	//kulans testpos y
	//double x7=0.0;
	//double  x8=0.0;
	//double  x9; //robotens testpos x
	//double x10;	//robotens testpos y
	//
	//int t = typo;
	//
	////if (t == 0)
	////{
		////printf("meep, meep\n");
		////continue;
	////}
	//
	//if(t == 1)	//rotera 90grader!
	//{
		//x5 = 20.0;	//kulans testpos
		//x6 = 50.0;
		//
		//x9 = 20.0;	//robotens testpos
		//x10 = 10.0;
		//
		//testWhat = 0;	//variabel för att (0) endast köra rotationstest
	//} else if(t == 2)	//rotera 180grader!
	//{
		//x5 = 200.0;	//kulans testpos
		//x6 = 200.0;
		//
		//x9 = 400.0;	//robotens testpos
		//x10 = 200.0;
		//
		//testWhat = 0;	//variabel för att (0) endast köra rotationstest
	//} else if(t == 3)	//rotera 270grader!
	//{
		//x5 = 20.0;	//kulans testpos
		//x6 = 20.0;
		//
		//x9 = 20.0;	//robotens testpos
		//x10 = 50.0;
		//
		//testWhat = 0;	//variabel för att (0) endast köra rotationstest
	//} else if(t == 4)	//rotera 0grader!
	//{
		//x5 = 300.0;	//kulans testpos
		//x6 = 100.0;
		//
		//x9 = 150.0;	//robotens testpos
		//x10 = 100.0;
		//
		//testWhat = 0;	//variabel för att (0) endast köra rotationstest
	//} else if(t == 5)
	//{
		//x5 = 50.0;	//kulans testpos
		//x6 = 100.0;
		//
		//x9 = 0.0;	//robotens testpos
		//x10 = 100.0;
		//testWhat = 1;	//variabel för att (1) endast köra distanstest
	//} else if(t == 6)
	//{
		//testWhat = 2;	//variabel för att (2) köra test med rotation/distans-kombo
	//}
	//fakePositionUpdateNAV(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10);
	//printf("testStyr-Function done");
	//
//}
//
	//void fakePositionUpdateNAV(double xBox,double  yBox,double  xCube,double  yCube,double  xBall,double  yBall,double  xGlass,double  yGlass,double  xRob,double  yRob)
	//{
		//double posRead [] = {xBox, yBox, xCube, yCube, xBall, yBall, xGlass, yGlass, xRob, yRob};
		//int i;
		//for(i=0; i<10 ;i++)
		//{
			//if (i == 0)
			//{
		//x_koord_Box = posRead[i];
				//
			//} else if (i == 1)
			//{
				//y_koord_Box = posRead[i];
				//
			//} else if (i == 2)
			//{
				//x_koord_Kub = posRead[i];
				//
			//} else if (i == 3)
			//{
				//x_koord_Kub = posRead[i];
				//
			//} else if (i == 4)
			//{
				//x_koord_Kula = posRead[i];
				//
			//} else if (i == 5)
			//{
				//y_koord_Kula = posRead[i];
				//
			//} else if (i == 6)
			//{
				//x_koord_Vinglas = posRead[i];
				//
			//} else if (i == 7)
			//{
				//y_koord_Vinglas = posRead[i];
				//
			//} else if (i == 8)
			//{
				//x_koord_Robot = posRead[i];
				//
			//} else if (i == 9)
			//{
				//y_koord_Robot = posRead[i];
			//}
			//printInt(posRead[i]);
			//
		//}			
	//printf("fakePositionNAV-function done");
//}
//---------------------------------------------------------------------------------------------


			//goalAngle = degreeCalculation(x_koord_Kula,x_koord_Robot,y_koord_Kula,y_koord_Robot);
			//printf("Roboten ska rotera till följande vinkel : ");
			//printInt(goalAngle);
			//rotation_angle = goalAngle;
			
			//Till styrning
			//rotate(200, rotation_angle);
			//drive(200, distance);


	
		//if(check_PDMM == 0){
			//distance = distanceCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot);
			//printf("Roboten har följande avstånd till viglaset : ");
			//printInt(distance);
			//if(distance <= 50){
				////sätt navigering i vila och kör sensorer
				//check_Dist = 1;
				//
			//}
			//goalAngle = degreeCalculation(x_koord_Vinglas,x_koord_Robot,y_koord_Vinglas,y_koord_Robot);
			//printf("Roboten ska rotera till följande vinkel : ");
			//printInt(goalAngle);
			//rotation_angle = goalAngle;
		//}

	//ioport_set_pin_level(PIO_PA15_IDX, LOW);		//what is this?