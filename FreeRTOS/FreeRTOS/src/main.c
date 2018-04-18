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
#include "task_player1.h"
#include "task_player2.h"
#include "task_control.h"
//Delay
#include "delayFunctions.h"
//Console Data Visualizer
#include "consoleFunctions.h"
//FreeRTOS
#include "FreeRTOS.h"
//Semaphores
#include "semphr.h"
//Struct
#include "xHandlerParameters.h"
// From module: TC - Timer Counter
#include "TimerCounter/TimerCounter.h"

int main (void)
{

	//Instantiating the struct
	xHandlerParameters* xHandler;
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
	init_timer();
	//Check pin for the TC-handler
	ioport_set_pin_dir(CHECK_PIN, IOPORT_DIR_OUTPUT);
	//Configuring board settings
	pmc_enable_periph_clk(ID_TRNG);
	trng_enable(TRNG);
	
	
	//analogInit(0);
	
	delayMicroseconds(100000);

	// Initiating board pins
	ioport_set_pin_dir(PIO_PB26_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	ioport_set_pin_dir(PIO_PA15_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PA15_IDX, HIGH);
	ioport_set_pin_dir(PIO_PC1_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PA15_IDX, HIGH);
	ioport_set_pin_dir(PIO_PC1_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PB21_IDX, HIGH);
	
	//Creating semaphores and tasks
	xSemaphorePlayer1 = 0;
	xSemaphorePlayer2 = 0;
	
	printf("Creating semaphores...\n");
	vSemaphoreCreateBinary(xSemaphorePlayer1 );
	vSemaphoreCreateBinary(xSemaphorePlayer2 );
	
	//Semaphores are taken and bot available
	xSemaphoreTake(xSemaphorePlayer1, 0);
	xSemaphoreTake(xSemaphorePlayer2, 0);

	printf("Creating task handler...\n");
	xTaskHandle taskHandlerPlayer1;
	xTaskHandle taskHandlerPlayer2;

	printf("Creating tasks...\n");
	xTaskCreate(task_player1, (const signed char * const) "player1", TASK_PLAYER1_STACK_SIZE, NULL, TASK_PLAYER1_PRIORITY, &taskHandlerPlayer1);                     
	xTaskCreate(task_player2, (const signed char * const) "player2", TASK_PLAYER2_STACK_SIZE, NULL, TASK_PLAYER2_PRIORITY, &taskHandlerPlayer2);
	
	printf("Task handler stored in struct xHandlerParameter.h...\n");
	xHandler->taskplayer1 = &taskHandlerPlayer1;
	xHandler->taskplayer2 = &taskHandlerPlayer2;
	
	/* Start the FreeRTOS scheduler running all tasks indefinitely*/    
	printf("Starting scheduler...\n");
	xTaskCreate(task_control, (const signed char * const) "control", TASK_CONTROL_STACK_SIZE, (void *) xHandler, TASK_CONTROL_PRIORITY, NULL);	
	vTaskStartScheduler();
	
	//while(1);
}
