/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include "task_interrupt.h"
#include "semphr.h"



void task_interrupt(void *pvParamters)
{
	//task_player2
	printf("Interrupt invoked!");
	while(1){
		portTickType xLastWakeTime;
		portTickType xTimeIncrement = 2123/portTICK_RATE_MS;
		xLastWakeTime = xTaskGetTickCount();

		//PIO_PA20_IDX = Digital Pin 44
		if(ioport_get_pin_level(PIO_PA20_IDX) == HIGH){
			ioport_set_pin_level(PIO_PA20_IDX, LOW);
		}
		else{
			ioport_set_pin_level(PIO_PA20_IDX, HIGH);
		}
		
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement );
		printf("end task_interrupt EoL(3.1)\n");
	}
}