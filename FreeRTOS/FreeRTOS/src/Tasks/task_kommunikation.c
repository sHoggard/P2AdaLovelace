/*
 * task_kommunikation.c
 *
 * Tasken testar just nu endast att uppdatera fejkpositioner till 
 * delade variabler med navigeringen för att se så att de kan integreras
 * (vet ännu inte exakt hur kommunikationen kommer att fungera)
 *
 * Created: 2018-05-15 09:55:22
 *  Author: Jelena
 */ 

#include "task_kommunikation.h"
#include <asf.h>
#include "../TWI_Kommunikationen/I2CFunctions.h"
#define xBlockTime 5000
#include "../Navigering/angleCalculation.h"

void task_kommunikation(void *pvParamters)
{
	printf("task_kommunikation\n");
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
			
	while (1)
	{
		printf("Kommunikation\n");
		vTaskDelay(xBlockTime);
		printf("Kommunikation\n");
		xLastWakeTime = xTaskGetTickCount();
		
		if(init_twi())
		{
	/*	
		//	Uppstart 
		send_package(0x20, TWI_SLAVE_ADR_PAB);
		delay_ms(1000);
		
		// Läser från påbyggnaden och skriver ut från på byggnaden
		
		
		
		read_package(TWI_SLAVE_ADR_PAB);
		for(int i=0;i<10;i++)
		{
			//printf(" %d",rec_data_pos[i]);		//tar inte emot något just nu
		}
		// Switchcase sats behövs
		// Lyft kula
		//Case 1
		send_package(0x21, TWI_SLAVE_ADR_PAB);
		//Lyft vinglas
		//Case 2
		send_package(0x23, TWI_SLAVE_ADR_PAB);
		//Lyft vinglas
		//Case 3
		send_package(0x24, TWI_SLAVE_ADR_PAB);
		//Lämna av object
		//Case 4
		send_package(0x25, TWI_SLAVE_ADR_PAB);
	*/
		check_PDMM = 1;		//när kommunikationen fått info om vilken påbyggnad som körs? 1=stålkula, 0=vinglas
		
			//	Uppstart POSITIONERING
			//send_package(0x20, TWI_SLAVE_ADR_POS);
			delay_ms(1000);
			
			uint8_t number = rand() % 30 + 1;
			uint8_t number2 = rand() % 30 + 1;
			double number3 = number;
			double number4 = number2;
			
			// Läser från positioneringen och skriver ut till rätt positionsvariebler som delas med navigering
			double  x1 = x1+5.0;
			double  x2 = x2+5.0;
			double x3 = x3+5.0;
			double  x4 = x4+5.0;
			double  x5 = 300.0;
			double  x6 = 300.0;
			double x7 = x7+5.0;
			double  x8 = x8+5.0;
			
			double  x9 = x9 + number3;
			double x10 = x10 + number4;
			
			//Test med fejkad positioneringsdata
			fakePositionUpdate(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10);
			printf("Positioneringsdata: ");
		
			printf(" %d");
		}
		
		printf("\nKommunikation out");
		xSemaphoreGive(xSemaphoreKommunikation);
		vTaskSuspend(NULL);
	}
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
	
}