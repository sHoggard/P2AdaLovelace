/*
 * task_kommunikation.c
 *
 *
 * Created: 2018-05-15 09:55:22
 *  Author: Jelena
 */ 

#include <asf.h>
#include "task_kommunikation.h"
#include "../TWI_Kommunikationen/TWI_Handler.h"
#include "../Navigering/angleCalculation.h"
#include "../RunState.h"
#include "semphr.h"
#include "task_state.h"
#include "../config/conf_AdaLovelace.h"
#include "../Utilities/ConsoleFunctions/consoleFunctions.h"
#include "xHandlerParameters.h"
#include "../Com/Com.h"

#define xBlockTime 5

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
		//--------------------------------------------------------
		// GLÖM EJ SÄTTA check_PDMM= 1 för vinglas och check_PDMM=2 för stålkula
		//--------------------------------------------------------

	
	if(currentState == STARTUP){
		bool check_com = false;
		while(!check_com)
		{
			//när vi fått in data från positionering
			//if data mottagits:
			if(data_extension.ID != 0) {
				changeState(TOWARDS_OBJECT_0);
				check_com = true;
			}
			else
			{
				#ifdef DEBUG_PRINTS
				printf("task_com\n");
				#endif
				
				task_com();
				
				#ifdef DEBUG_PRINTS
				printf("task_com done\n");
				#endif
				
				vTaskDelay(500);
			}
		}
	}
	
	else if(currentState == PICKUP){
		bool check_com = false;
		while(!check_com)
		{
			//if(){
			changeState(TOWARDS_BOX_0);
			check_com = true;
			//}
		}
	}
	
	

		//	Example code, send and receive
		/*printf("Start Send\n");
		transmit_package(0x20, SLAVE_ADDRESS_PABYGGNAD);
		printf("end Send\n");
		delay_ms(1000);
		// Läser från påbyggnaden och skriver ut från på byggnaden
		receive_package(SLAVE_ADDRESS_PABYGGNAD);
		for(int i=0;i<10;i++)
		{
			printf(" %d",receive_data_pabyggnad[i]);
		}*/
		
	//	delay_ms(1000);
			
			//Test med fejkad positioneringsdata
			//int j;
			//printf("Tryck 1 om TC0, 2 om TC1, 3 om TC2 ska köras");
			//scanf("%i", &j);
			//printf("\nDu tryckte: ");
			//printInt(j);
			//testNavKom(j);
			
			xSemaphoreGive(xSemaphoreKommunikation);
			vTaskSuspend(NULL);
	}
		
	printf("\nKommunikation out");
	xSemaphoreGive(xSemaphoreKommunikation);
	vTaskSuspend(NULL);
}


//--------------- Test för KOM-NAV --------------------------------------------------------
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
	
	//if(t == 1)	//TC0 
	//{
		//x5 = 20.0;	//kulans testpos
		//x6 = 20.0;
		//
		//x9 = 20.0;	//robotens testpos
		//x10 = 50.0;
		//
		//testWhat = 0;	//variabel för att (0) endast se så data delas
		//
	//} else if(t == 2)	//TC1
	//{		
		//testWhat = 1;	//variabel för att (1) beräkna avstånd från datan
		//
	//} else if(t == 3)	//TC2
	//{
		//testWhat = 2;	//variabel för att (2) beräkna vinkel från datan
	//} 
	//fakePositionUpdate(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10);
	//printf("testNavKomFunction done");
	//
//}
//
//void fakePositionUpdate(double xBox,double  yBox,double  xCube,double  yCube,double  xBall,double  yBall,double  xGlass,double  yGlass,double  xRob,double  yRob){
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
		////printInt(posRead[i]);
	//}
	//printf("fakePositionUpdateFunction done");
}
//------------------------------------------------------------------------------------------