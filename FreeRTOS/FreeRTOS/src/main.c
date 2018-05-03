/**
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 *
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <inttypes.h>
#include <stdio_serial.h>
//Tasks
#include "Tasks/task_player1.h"
#include "Tasks/task_player2.h"
#include "Tasks/task_control.h"
//Delay
#include "Utilities/DelayFunctions/delayFunctions.h"
//Console Data Visualizer
#include "Utilities/ConsoleFunctions/consoleFunctions.h"
//FreeRTOS
#include "FreeRTOS.h"
//Semaphores
#include "semphr.h"
//Struct
#include "xHandlerParameters.h"
// From module: TC - Timer Counter
#include "Utilities/TimerCounter/TimerCounter.h"
#include "Utilities/PioInterrupt/PioInterrupt.h"

#include "conf_board.h"
#include "conf_clock.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"

/*int main (void)
{
	
	// Initialize the SAM system 
	sysclk_init();
	board_init();
	init_timer();
	delayInit();
	//initMotors();
	
	// Configure the console uart for debug information 
	configureConsole();

	initMotors();
	initSensors();
	// Infinite loop 
	while (1) {
	}
}*/


volatile xHandlerParameters *xHandler;
volatile xTaskHandle taskHandlerPlayer1;
volatile xTaskHandle taskHandlerPlayer2;

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
	delayMicroseconds(100000);
	while(1);
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
	xSemaphorePlayer1 = 0;
	xSemaphorePlayer2 = 0;
	
	printf("Creating semaphores...\n");
	vSemaphoreCreateBinary(xSemaphorePlayer1 );
	vSemaphoreCreateBinary(xSemaphorePlayer2 );
	
	//Semaphores are configured, task1 will be resumed in task_control.c
	xSemaphoreGive(xSemaphorePlayer1); // value 1, available
	xSemaphoreTake(xSemaphorePlayer2, 0); //value 0

	printf("Creating task handler...\n");
	

	bool xReturned = false;
	printf("Creating tasks...\n");
	xReturned = xTaskCreate(task_player1, (const signed char * const) "player1", TASK_PLAYER1_STACK_SIZE, NULL, TASK_PLAYER1_PRIORITY, &taskHandlerPlayer1);                     
	if( xReturned == pdPASS )
	{
		printf("task_player1 created...\n");
		
	}
	xReturned = xTaskCreate(task_player2, (const signed char * const) "player2", TASK_PLAYER2_STACK_SIZE, NULL, TASK_PLAYER2_PRIORITY, &taskHandlerPlayer2);
	if( xReturned == pdPASS )
	{
		printf("task_player2 created...\n");
		
	}
	printf("Task handler stored in struct xHandlerParameter.h...\n");
	xHandler->taskplayer1 = &taskHandlerPlayer1;
	xHandler->taskplayer2 = &taskHandlerPlayer2;
	
	//Suspend all tasks
	vTaskSuspend(*(xHandler->taskplayer1));
	vTaskSuspend(*(xHandler->taskplayer2));
	printf("Address stored in &xHandler: %x\n", &xHandler );
	printf("Address stored in xHandler: %x\n", xHandler );
	printf("Address stored in &xHandler->taskplayer1: %x\n", &xHandler->taskplayer1 );
	printf("Address stored in &xHandler->taskplayer2: %x\n", &xHandler->taskplayer2 );
	printf("Address stored in xHandler->taskplayer1: %x\n", xHandler->taskplayer1 );
	printf("Address stored in xHandler->taskplayer2: %x\n", xHandler->taskplayer2 );
	
	// Start the FreeRTOS scheduler running all tasks indefinitely
	
	xTaskCreate(task_control, (const signed char * const) "control", TASK_CONTROL_STACK_SIZE, (void *) xHandler, TASK_CONTROL_PRIORITY, NULL);	
	//printf("Starting scheduler...\n");
	//vTaskStartScheduler();
	printf("EoL(main)");
	while(1);
	
	
	
}
