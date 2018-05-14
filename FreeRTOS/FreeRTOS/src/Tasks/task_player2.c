/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include "task_player2.h"

#define xBlockTime 1

void task_player2(void *pvParamters)
{
	//int work = 100000;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	printf("P2\n");
	while(1){
		vTaskDelay(xBlockTime);
		printf("P2\n");
		xLastWakeTime = xTaskGetTickCount();
		//task_player2
		//PIO_PB26_IDX = Digital Pin 22
		volatile int j=0; /* makes sure j doesn't overflow */
		ioport_set_pin_level(PIO_PB26_IDX, HIGH);

		char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};
		

		// Insert application code here, after the board has been initialized.

		// testing new wheelcounter strategy
		//while (true)
		//{
		//printf("counterLeft: %i\ncounterRight: %i\n\n", (int)counterLeft, (int)counterRight);
		//delay_ms(2000);
		//}
		
		time_tick_init();
		
		char buffer[20];
		
		int speed = 100;
		
		//scanf("%i", &speed);
		
		// test actual speed
		uint32_t start = time_tick_get();
		
		drive(speed, 5000);
		
		printf("speed: %i\n\n", speed);
		
		//setMotorSpeed(MOTOR_BRAKE + speed, MOTOR_BRAKE + speed);
		
		int counter = 0;
		int done = 1;
		while (done)
		{
			if (time_tick_get()%100 == 0)
			{
				//fputs(clrCom, stdout);
				//puts(itoa(counterLeft, buffer, 10));
				//puts(itoa(counterRight, buffer, 10));
				//puts(itoa(orientation(), buffer, 10));
				//puts(itoa(regulated_speed.left, buffer, 10));
				//puts(itoa(regulated_speed.right, buffer, 10));
				//puts(itoa(regulated_speed.target, buffer, 10));
				////drive(speed, 0);
				//test_movement();
				//if (speed < 500)
				//{
				//speed++;
				//}
				printf("%i: \n", counter++);
				test_movement();
				printf("\n");
				delay_ms(1);
			}
			else
				done = 0;
			
			// test accuracy of distance measurement
			//if (time_tick_get() > start + 10000)
			//{
			//printf("distance travelled after 10 seconds: %i\n", (int)(distanceLeft + distanceRight)/2);
			//drive(0, 0);
			//test_movement();
			//delay_ms(5000);
			//}
		}

	
	
	
		ioport_set_pin_level(PIO_PB26_IDX, LOW);
		printf("give2\n");
		xSemaphoreGive(xSemaphorePlayer2);
		vTaskSuspend(NULL);

	
	}
}