/*
 * task_kommunikation.c
 *
 *
 * Created: 2018-05-15 09:55:22
 *  Author: Jelena
 */ 

#include "task_kommunikation.h"
#include <asf.h>
#include "../TWI_Kommunikationen/I2CFunctions.h"
#define xBlockTime 5
#include "../Navigering/angleCalculation.h"

void task_kommunikation(void *pvParamters)
{
	printf("task_kommunikation started\n");
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	
			
	while (1)
	{
		printf("Kommunikation\n");
		vTaskDelay(xBlockTime);
		xLastWakeTime = xTaskGetTickCount();
		
		//	Uppstart POSITIONERING
		
			delay_ms(1000);
			
			//Test med fejkad positioneringsdata
			int j;
			printf("Tryck 1 om TC0, 2 om TC1, 3 om TC2 ska köras");
			scanf("%i", &j);
			printf("\nDu tryckte: ");
			printInt(j);
			testNavKom(j);
	}
		
	printf("\nKommunikation out");
	xSemaphoreGive(xSemaphoreKommunikation);
	vTaskSuspend(NULL);
}

void testNavKom(int jin)
{
	double  x1=0.0;
	double  x2=0.0;
	double x3=0.0;
	double  x4=0.0;
	double  x5; //kulans testpos x
	double  x6;	//kulans testpos y
	double x7=0.0;
	double  x8=0.0;
	double  x9; //robotens testpos x
	double x10;	//robotens testpos y
	
	int t = jin;
	
	//if (t == 0)
	//{
	//printf("meep, meep\n");
	//continue;
	//}
	
	if(t == 1)	//rotera 90grader!
	{
		x5 = 20.0;	//kulans testpos
		x6 = 50.0;
		
		x9 = 20.0;	//robotens testpos
		x10 = 10.0;
		
		testWhat = 0;	//variabel för att (0) endast köra rotationstest
	} else if(t == 2)	//rotera 180grader!
	{
		x5 = 200.0;	//kulans testpos
		x6 = 200.0;
		
		x9 = 400.0;	//robotens testpos
		x10 = 200.0;
		
		testWhat = 0;	//variabel för att (0) endast köra rotationstest
	} else if(t == 3)	//rotera 270grader!
	{
		x5 = 20.0;	//kulans testpos
		x6 = 20.0;
		
		x9 = 20.0;	//robotens testpos
		x10 = 50.0;
		
		testWhat = 0;	//variabel för att (0) endast köra rotationstest
	} else if(t == 4)	//rotera 0grader!
	{
		x5 = 300.0;	//kulans testpos
		x6 = 100.0;
		
		x9 = 150.0;	//robotens testpos
		x10 = 100.0;
		
		testWhat = 0;	//variabel för att (0) endast köra rotationstest
	} else if(t == 5)
	{
		testWhat = 1;	//variabel för att (1) endast köra distanstest
	} else if(t == 6)
	{
		testWhat = 2;	//variabel för att (2) köra test med rotation/distans-kombo
	}
	fakePositionUpdate(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10);
	printf("testNavKomFunction done");
	
}

void fakePositionUpdate(double xBox,double  yBox,double  xCube,double  yCube,double  xBall,double  yBall,double  xGlass,double  yGlass,double  xRob,double  yRob){
	double posRead [] = {xBox, yBox, xCube, yCube, xBall, yBall, xGlass, yGlass, xRob, yRob};
	int i;
	for(i=0; i<10 ;i++)
	{
		if (i == 0)
		{
			x_koord_Box = posRead[i];
			
		} else if (i == 1)
		{
			y_koord_Box = posRead[i];
			
		} else if (i == 2)
		{
			x_koord_Kub = posRead[i];
			
		} else if (i == 3)
		{
			x_koord_Kub = posRead[i];
			
		} else if (i == 4)
		{
			x_koord_Kula = posRead[i];
			
		} else if (i == 5)
		{
			y_koord_Kula = posRead[i];
			
		} else if (i == 6)
		{
			x_koord_Vinglas = posRead[i];
			
		} else if (i == 7)
		{
			y_koord_Vinglas = posRead[i];
			
		} else if (i == 8)
		{
			x_koord_Robot = posRead[i];
			
		} else if (i == 9)
		{
			y_koord_Robot = posRead[i];
		}
		printInt(posRead[i]);
	}
	printf("fakePositionUpdateFunction done")
}