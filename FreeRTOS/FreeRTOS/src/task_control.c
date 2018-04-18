/*
* task_control.c
*
* Created: 2018-02-01 11:25:38
*  Author: George Albert Florea
*  Author: Benjamin Sejdic
*/

#include <asf.h>
#include "task_control.h"
#include "lcdApplication.h"
#include "buttons.h"
#include "lcdFunctions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "xHandlerParameters.h"

#define xBlockTime 100
portTickType xTimeStampTicks;
portTickType timeStart;
uint32_t reactionTimePlayer1;
uint32_t reactionTimePlayer2;
bool player1btnPressed = false;
bool player2btnPressed = false;

void task_control(void *pvParamters)
{
	
	xHandlerParameters* taskHandler = (xHandlerParameters*) pvParamters;
	
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 6000/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	//task_control
	// PIO_PC1_IDX, = Digital Pin 33
	while(1)
	{ioport_set_pin_level(PIO_PC1_IDX, LOW);
		printf("task_control\n");
		
		if(xSemaphoreTake(xSemaphorePlayer1, 0) == pdTRUE){
			printf("- xSemaphorePlayer1\n");
			vTaskResume(*(taskHandler->taskplayer2));	
			printf("- - - -\n");					
			//vTaskSuspend(*(taskHandler->taskplayer1));	
			printf("- - - -\n");	
		}
		else if(xSemaphoreTake(xSemaphorePlayer2, 0) == pdTRUE){
			printf("- xSemaphorePlayer2\n");
			vTaskResume(*(taskHandler->taskplayer1));	
			printf("- - - -\n");	
			vTaskSuspend(*(taskHandler->taskplayer2));
			printf("- - - -\n");
		}
		
		printf("end task_control\n");
		ioport_set_pin_level(PIO_PC1_IDX, HIGH);
		vTaskDelay(1000/portTICK_RATE_MS);	
	}
}

/*
while(!gameStarted)
{
	lcdWrite(0b00000001, LOW); // Clear display 
	//if(readLCDbutton() == btnSELECT){
	gameStarted = true;
	printf("lcdWriteAsciiString(...)\n");
	lcdWriteAsciiString("Game started");
	printf("lcdWriteAsciiString(...)\n");
	vTaskDelay(1000/portTICK_RATE_MS);
	
	uint32_t randomNumberMillis = (getRandomNumber()*1000);
	ioport_set_pin_level(PIO_PB26_IDX, LOW);
	
	lcdWrite(0b00000001, LOW); // Clear display
	printf("RANDOM_NUMBER_MILLIS: %d\n", randomNumberMillis);
	
	vTaskDelay(1000/portTICK_RATE_MS);
	
	timeStart = xTaskGetTickCount();
	printf("TIME_START: %d\n", timeStart);
	ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	//}
}


//Spelare 1 och 2 har trckt på sina knappar minst en gång efter spelet startats
if(player1btnPressed && player2btnPressed){
	if(reactionTimePlayer1<reactionTimePlayer2){
		printf("player1");
		lcdWriteAsciiString("Player1 has won!");
		
		vTaskDelay(1000/portTICK_RATE_MS);
		lcdWrite(0b00000001, LOW); // Clear display
		vTaskDelay(1000/portTICK_RATE_MS);
		
		lcdWriteAsciiString("Player1 reaction:");
		lcdWrite(0x80 | (1 << 6) | 0, LOW);
		lcdWrite4DigitNumber(reactionTimePlayer1);
		lcdWriteAsciiString(" ms");
		
		vTaskDelay(1000/portTICK_RATE_MS);
		lcdWrite(0b00000001, LOW); // Clear display
		vTaskDelay(1000/portTICK_RATE_MS);
		
		lcdWriteAsciiString("Player2 reaction: ");
		lcdWrite(0x80 | (1 << 6) | 0, LOW);
		lcdWrite4DigitNumber(reactionTimePlayer2);
		lcdWriteAsciiString(" ms");
		vTaskDelay(100/portTICK_RATE_MS);
		
		} else{
		printf("player2");
		lcdWriteAsciiString("Player2 has won!");
		
		vTaskDelay(1000/portTICK_RATE_MS);
		lcdWrite(0b00000001, LOW); // Clear display
		vTaskDelay(1000/portTICK_RATE_MS);
		
		lcdWriteAsciiString("Player2 reaction:");
		lcdWrite(0x80 | (1 << 6) | 0, LOW);
		lcdWrite4DigitNumber(reactionTimePlayer2);
		lcdWriteAsciiString(" ms");
		
		vTaskDelay(1000/portTICK_RATE_MS);
		lcdWrite(0b00000001, LOW); // Clear display
		vTaskDelay(1000/portTICK_RATE_MS);
		
		lcdWriteAsciiString("Player1 reaction: ");
		lcdWrite(0x80 | (1 << 6) | 0, LOW);
		lcdWrite4DigitNumber(reactionTimePlayer1);
		lcdWriteAsciiString(" ms");
		vTaskDelay(100/portTICK_RATE_MS);
		
	}
*/