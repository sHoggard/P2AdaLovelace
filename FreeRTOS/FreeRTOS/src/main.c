/**
 *  Author: Ada Lovelace,
 */

#include <asf.h>
#include <inttypes.h>
#include <stdio_serial.h>
//Utilities
#include "Utilities/DelayFunctions/delayFunctions.h"
#include "Utilities/ConsoleFunctions/consoleFunctions.h"
#include "Utilities/TimerCounter/TimerCounter.h" //From module: TC - Timer Counter
#include "Utilities/PioInterrupt/PioInterrupt.h"
//FreeRTOS, Semaphores
#include "FreeRTOS.h"
#include "semphr.h"
//Struct
#include "xHandlerParameters.h"
//board
#include "conf_board.h"
#include "conf_clock.h"
//Tasks
#include "Tasks/task_player1.h"
#include "Tasks/task_player2.h"
#include "Tasks/task_control.h"
//System modules
#include "WheelCounters/WheelCounters.h"
#include "Navigering/angleCalculation.h"
#include "config/conf_AdaLovelace.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"
#include "Movement/Movement.h"
#include "TimeTick/time_tick.h"
#include "Utilities/ConsoleFunctions/consoleFunctions.h"

#include "Movement/__vars.h"

char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	configureConsole();

	// Insert application code here, after the board has been initialized.
	
	initMovement();
	
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
	
	while (1)
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
		
		// test accuracy of distance measurement
		//if (time_tick_get() > start + 10000)
		//{
		//printf("distance travelled after 10 seconds: %i\n", (int)(distanceLeft + distanceRight)/2);
		//drive(0, 0);
		//test_movement();
		//delay_ms(5000);
		//}
	}
}




//ctrk+k, ctrl+c f�r att kommentera bort kod
//ctrk+k, ctrl+u f�r att avkommentera
////2018-05-10
//int i = 0;
//
//float goalAngle = 0.0;
//float oldAngle = 0.0;
//float newAngle = 0.0;
//float angle = 0.0;
//
//
////NAVIGATION MAIN
//int main (void)
//{
	//i++;
	///* Initialize the SAM system */
	//sysclk_init();
	//board_init();
	//
	//delayInit();
	////initMotors();
	//
	////char buffer [34];
	////itoa(sysclk_get_cpu_hz(), buffer, 10);
	////puts(buffer);
	//
	///* Configure the console uart for debug information */
	//configureConsole();
	//
	//
	//int test = 1;
	//while(test == 1){
	///* -----------------------------------------------------------------------------------
				//NAVIGERING - TEST	
	//--------------------------------------------------------------------------------------*/
	//
	////----------Test f�r att kontrollera s� att grad-ber�kning fr�n radianer funkar----------
	///*float degrees = 0.0;
	//float radians [] = {(PI/6), (PI/4), (PI/3), (PI/2), (PI), ((3*PI)/2), (2*PI)};
	//char rads [7][9] = {"PI/6 = ", "PI/4 = ", "PI/3 = ", "PI/2 = ", "PI = ", "3PI/2 = ", "2PI = "};
	//for (int i=0; i < 7; i++){
		//degrees = rad2deg(radians[i]);
		//printf(rads[i]);
		//printInt(degrees);
	//}*/
	//
	//
	////----------Test f�r avst�ndsber�kningar----------
	///*float distance = 0.0;
	//distance = distanceCalculation(2,2,2,5); //3 l�ngdenheter
	//printf("Roboten i (2,5) har f�ljande avst�nd till objektet i (2,2) : ");
	//printInt(distance);
	//distance = distanceCalculation(2,4,2,2); //2 l�ngdenheter
	//printf("\nRoboten i (4,2) har f�ljande avst�nd till objektet i (2,2) : ");
	//printInt(distance);
	//distance = distanceCalculation(2,2,2,2); //0 l�ngdenheter
	//printf("\nRoboten i (2,2) har f�ljande avst�nd till objektet i (2,2) : ");
	//printInt(distance);
	//distance = distanceCalculation(2,10,2,2); //8 l�ngdenheter
	//printf("\nRoboten i (10,2) har f�ljande avst�nd till objektet i (2,2) : ");
	//printInt(distance);*/
	//
	//
	////----------Test f�r 1a kvadranten----------
	///*goalAngle = degreeCalculation(2,1,2,2); //0 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,1,2,1);	//45 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,2,5,1);	//90 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,0,2,1);	//26grader
	//printInt(goalAngle);*/
	//
	//
	////----------Test f�r 2a kvadranten----------
	///*goalAngle = degreeCalculation(2,4,2,2);	//180 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,3,2,1);	//135 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,2,5,1);	//90 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,6,2,0);	//116 grader
	//printInt(goalAngle);*/
	//
	//
	////----------Test f�r 3e kvadranten----------
	///*goalAngle = degreeCalculation(2,4,2,3);	//243 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,2,2,5);	//270 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,3,1,5);	//194 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,5,2,5);	//225 grader
	//printInt(goalAngle);*/
	//
	//
	////----------Test f�r 4e kvadranten----------
	///*goalAngle = degreeCalculation(2,1,1,3);	//296 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,2,2,5);	//270 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(2,0,1,6);	//291 grader
	//printInt(goalAngle);
	//goalAngle = degreeCalculation(8,2,6,7);	//350 grader
	//printInt(goalAngle);*/
	//
	//
	////----------Test f�r ber�kning av korrigeringsvinkel----------
	///*printf("\n----- TEST: ROTERA TILL 180 -----\n");
	//newAngle = correctionAngleCalculation(2,4,2,2,oldAngle);
	//angle = oldAngle + newAngle;
	//printf("Current angle: ");
	//printInt(oldAngle);
	//printf("\nGoal angle: ");
	//goalAngle = degreeCalculation(2,4,2,2);
	//printInt(goalAngle);	
	//printf("\nCorrection angle: ");
	//printInt(newAngle);
	//printf("\n--------------------------------\n");
	//oldAngle = angle;
	//
	//printf("\n----- TEST: ROTERA TILL 45 -----\n");
	//newAngle = correctionAngleCalculation(2,1,2,1,oldAngle);
	//angle = oldAngle + newAngle;
	//printf("Current angle: ");
	//printInt(oldAngle);
	//printf("\nGoal angle: ");
	//goalAngle = degreeCalculation(2,1,2,1);
	//printInt(goalAngle);
	//printf("\nCorrection angle: ");
	//printInt(newAngle);
	//printf("\n--------------------------------\n");
	//oldAngle = angle;
	//
	//printf("\n----- TEST: ROTERA TILL 0 -----\n");
	//newAngle = correctionAngleCalculation(2,1,2,2,oldAngle);
	//angle = oldAngle + newAngle;
	//printf("Current angle: ");
	//printInt(oldAngle);
	//printf("\nGoal angle: ");
	//goalAngle = degreeCalculation(2,1,2,2);
	//printInt(goalAngle);	
	//printf("\nCorrection angle: ");
	//printInt(newAngle);
	//printf("\n--------------------------------\n");
	//oldAngle = angle;
	//
		//printf("\n----- TEST: ROTERA TILL 225 -----\n");
	//newAngle = correctionAngleCalculation(2,5,2,5,oldAngle);
	//angle = oldAngle + newAngle;
	//printf("Current angle: ");
	//printInt(oldAngle);
	//printf("\nGoal angle: ");
	//goalAngle = degreeCalculation(2,5,2,5);
	//printInt(goalAngle);
	//printf("\nCorrection angle: ");
	//printInt(newAngle);
	//printf("\n--------------------------------\n");
	//oldAngle = angle;
	//
	//printf("\n----- TEST: ROTERA TILL 225 -----\n");
	//newAngle = correctionAngleCalculation(2,5,2,5,oldAngle);
	//angle = oldAngle + newAngle;
	//printf("Current angle: ");
	//printInt(oldAngle);
	//printf("\nGoal angle: ");
	//goalAngle = degreeCalculation(2,5,2,5);
	//printInt(goalAngle);
	//printf("\nCorrection angle: ");
	//printInt(newAngle);
	//printf("\n--------------------------------\n");
	//oldAngle = angle;*/
	//
		//
	//test = 0;
	//}
	//
	///* Infinite loop */
	//while (1) 
	//{
//
	//}
//}





//RTOS MAIN
////2018-05-10
//volatile xHandlerParameters *xHandler;
//volatile xTaskHandle taskHandlerPlayer1;
//volatile xTaskHandle taskHandlerPlayer2;
//int main (void)
//{
	////Instantiating the struct
	//xHandler = ( xHandlerParameters* ) pvPortMalloc( sizeof( xHandler ) );
	//
	//// Insert board initialization code here (board_init())
	//board_init();
	//// Insert system clock initialization code here (sysclk_init())
	//sysclk_init();
	//// Configuring console (Tools->Data Visulizer)
	//configureConsole();
	//// Delay initialization
	//delayInit();
	//// Insert application code here, after the board has been initialized.
	////init_timer();
	//ioport_init();
	//
	////Check pin for the TC-handler
	//ioport_set_pin_dir(CHECK_PIN, IOPORT_DIR_OUTPUT);
	////Configuring board settings
	//pmc_enable_periph_clk(ID_TRNG);
	//trng_enable(TRNG);
	//
	//delayMicroseconds(100000);
//
	//// Initiating board pins
	//ioport_set_pin_dir(PIO_PB26_IDX, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	//ioport_set_pin_dir(PIO_PA15_IDX, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_level(PIO_PA15_IDX, HIGH);
	//ioport_set_pin_dir(PIO_PC1_IDX, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_level(PIO_PC1_IDX, HIGH);
	//ioport_set_pin_dir(PIO_PC19_IDX, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_level(PIO_PC19_IDX, HIGH);
	//
	//int test = 1;
	//configPioInterrupt();
	//
	////Creating semaphores and tasks
	//xSemaphorePlayer1 = 0;
	//xSemaphorePlayer2 = 0;
	//
	//printf("Creating semaphores...\n");
	//vSemaphoreCreateBinary(xSemaphorePlayer1 );
	//vSemaphoreCreateBinary(xSemaphorePlayer2 );
	//
	////Semaphores are configured, task1 will be resumed in task_control.c
	//xSemaphoreGive(xSemaphorePlayer1); // value 1, available
	//xSemaphoreTake(xSemaphorePlayer2, 0); //value 0
//
	//printf("Creating task handler...\n");
	//
//
	//bool xReturned = false;
	//printf("Creating tasks...\n");
	//xReturned = xTaskCreate(task_player1, (const signed char * const) "player1", TASK_PLAYER1_STACK_SIZE, NULL, TASK_PLAYER1_PRIORITY, &taskHandlerPlayer1);
	//if( xReturned == pdPASS )
	//{
		//printf("task_player1 created...\n");
		//
	//}
	//xReturned = xTaskCreate(task_player2, (const signed char * const) "player2", TASK_PLAYER2_STACK_SIZE, NULL, TASK_PLAYER2_PRIORITY, &taskHandlerPlayer2);
	//if( xReturned == pdPASS )
	//{
		//printf("task_player2 created...\n");
		//
	//}
	//printf("Task handler stored in struct xHandlerParameter.h...\n");
	//xHandler->taskplayer1 = &taskHandlerPlayer1;
	//xHandler->taskplayer2 = &taskHandlerPlayer2;
	//
	////Suspend all tasks
	//vTaskSuspend(*(xHandler->taskplayer1));
	//vTaskSuspend(*(xHandler->taskplayer2));
	//printf("Address stored in &xHandler: %x\n", &xHandler );
	//printf("Address stored in xHandler: %x\n", xHandler );
	//printf("Address stored in &xHandler->taskplayer1: %x\n", &xHandler->taskplayer1 );
	//printf("Address stored in &xHandler->taskplayer2: %x\n", &xHandler->taskplayer2 );
	//printf("Address stored in xHandler->taskplayer1: %x\n", xHandler->taskplayer1 );
	//printf("Address stored in xHandler->taskplayer2: %x\n", xHandler->taskplayer2 );
	//
	//// Start the FreeRTOS scheduler running all tasks indefinitely
	//printf("Starting scheduler...\n");
	//xTaskCreate(task_control, (const signed char * const) "control", TASK_CONTROL_STACK_SIZE, (void *) xHandler, TASK_CONTROL_PRIORITY, NULL);
	//vTaskStartScheduler();
	//while(1);	
//}


//ctrk+k, ctrl+c f�r att kommentera bort kod
//ctrk+k, ctrl+u f�r att avkommentera

//PRINT INT TEST MAIN
////2018-05-10
//int i = 0;
//
//int main (void)
//{
	//i++;
	///* Initialize the SAM system */
	//sysclk_init();
	//board_init();
	//init_timer();
	//delayInit();
	//initMotors();
	//
	//char buffer [34];
	//itoa(sysclk_get_cpu_hz(), buffer, 10);
	//puts(buffer);
	//
	///* Configure the console uart for debug information */
	//configureConsole();
//
	//initMotors();
	//initSensors();
	//
	///* Infinite loop */
	//while (1) 
	//{
		//printf("hejsan");
		//char c = (char) i;
		//printf((int)i);
		//printf("\n");
		//delayMicroseconds(100000);
			//char buffer [34];
			//
			//itoa(i, buffer, 10); 
			 //sysclk_get_cpu_hz() //ger klockfrekvensen
			//i++;
			//printInt(i);
		//delayMicroseconds(100000);
	//}
//}



