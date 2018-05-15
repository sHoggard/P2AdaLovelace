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
#include "Tasks/task_navigering.h"
#include "Tasks/task_styrning.h"
#include "Tasks/task_tickMovement.h"
#include "Tasks/task_control.h"
#include "Movement/Movement.h"



volatile xHandlerParameters *xHandler;
volatile xTaskHandle taskHandlerNavigering;
volatile xTaskHandle taskHandlerStyrning;
volatile xTaskHandle taskHandlerTickMovement;
volatile int checkInt = 1;

int main (void)
{
	//Instantiating the struct
	xHandler = ( xHandlerParameters* ) pvPortMalloc( sizeof( xHandler ) );
	
	// Insert board initialization code here (board_init())
	board_init();
	// Insert system clock initialization code here (sysclk_init())
	sysclk_init();
	// Configuring console (Tools->Data Visulizer)
	configureConsole();
	// Delay initialization
	delayInit();
	// Insert application code here, after the board has been initialized.
	//init_timer();
	ioport_init();
	
	//Check pin for the TC-handler
	ioport_set_pin_dir(CHECK_PIN, IOPORT_DIR_OUTPUT);
	//Configuring board settings
	pmc_enable_periph_clk(ID_TRNG);
	trng_enable(TRNG);
	initMovement();
	//analogInit(0);
	
	delayMicroseconds(100000);

	// Initiating board pins
	ioport_set_pin_dir(PIO_PB26_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	ioport_set_pin_dir(PIO_PA15_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PA15_IDX, HIGH);
	ioport_set_pin_dir(PIO_PC1_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PC1_IDX, HIGH);
	ioport_set_pin_dir(PIO_PC19_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PC19_IDX, HIGH);
	
	configPioInterrupt();
	
	//Creating semaphores and tasks
	xSemaphoreNavigering = 0;
	xSemaphoreStyrning = 0;
	xSemaphoreTickMovement = 0;
	
	printf("Creating semaphores...\n");
	vSemaphoreCreateBinary(xSemaphoreNavigering );
	vSemaphoreCreateBinary(xSemaphoreStyrning );
	vSemaphoreCreateBinary(xSemaphoreTickMovement );
	
	//Semaphores are configured, task1 will be resumed in task_control.c
	xSemaphoreGive(xSemaphoreNavigering); // value 1, available
	xSemaphoreTake(xSemaphoreStyrning, 0); //value 0

	printf("Creating task handler...\n");
	

	bool xReturned = false;
	printf("Creating tasks...\n");
	xReturned = xTaskCreate(task_navigering, (const signed char * const) "navigering", TASK_NAVIGERING_STACK_SIZE, NULL, TASK_NAVIGERING_PRIORITY, &taskHandlerNavigering);
	if( xReturned == pdPASS )
	{
		printf("task_navigering created...\n");
		
	}
	xReturned = xTaskCreate(task_tickMovement, (const signed char * const) "tickMovement", TASK_TICKMOVEMENT_STACK_SIZE, xHandler, TASK_TICKMOVEMENT_PRIORITY, &taskHandlerTickMovement);
	if( xReturned == pdPASS )
	{
		printf("task_tickMovement created...\n");
		
	}
	printf("Task handler stored in struct xHandlerParameter.h...\n");
	xHandler->taskNavigation = &taskHandlerNavigering;
	xHandler->taskStyrning = &taskHandlerStyrning;
	xHandler->taskTickMovement = &taskHandlerTickMovement;
	
	//Suspend all tasks
	vTaskSuspend(*(xHandler->taskNavigation));
	vTaskSuspend(*(xHandler->taskStyrning));
	vTaskSuspend(*(xHandler->taskTickMovement));
	printf("Address stored in &xHandler: %x\n", &xHandler );
	printf("Address stored in xHandler: %x\n", xHandler );
	printf("Address stored in &xHandler->taskplayer1: %x\n", &xHandler->taskNavigation );
	printf("Address stored in &xHandler->taskplayer2: %x\n", &xHandler->taskStyrning );
	printf("Address stored in xHandler->taskplayer1: %x\n", xHandler->taskNavigation );
	printf("Address stored in xHandler->taskplayer2: %x\n", xHandler->taskStyrning );
	
	xReturned = xTaskCreate(task_styrning, (const signed char * const) "styrning", TASK_STYRNING_STACK_SIZE, (void *) xHandler, TASK_STYRNING_PRIORITY, &taskHandlerStyrning);
	if( xReturned == pdPASS )
	{
		printf("task_styrning created...\n");
		
	}
	
	// Start the FreeRTOS scheduler running all tasks indefinitely
	printf("Starting scheduler...\n");
	xTaskCreate(task_control, (const signed char * const) "control", TASK_CONTROL_STACK_SIZE, (void *) xHandler, TASK_CONTROL_PRIORITY, NULL);
	vTaskStartScheduler();
	
	xHandler->check = &checkInt;
	while(1);
	
	
	
}

//ctrk+k, ctrl+c f�r att kommentera bort kod
//ctrk+k, ctrl+u f�r att avkommentera

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
	//initMovement();
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



