/**
 *  Author: Ada Lovelace,
 */

#include <asf.h>
#include <inttypes.h>
#include <stdio_serial.h>
//Utilities
#include "Utilities/ConsoleFunctions/consoleFunctions.h"
//FreeRTOS, Semaphores
#include "FreeRTOS.h"
#include "semphr.h"
//Struct
#include "xHandlerParameters.h"
//board
#include "conf_board.h"
#include "conf_clock.h"
//Tasks
#include "Tasks/task_kommunikation.h"
#include "Tasks/task_navigering.h"
#include "Tasks/task_sensor.h"
#include "Tasks/task_styrning.h"
#include "Tasks/task_reglering.h"
#include "Tasks/task_state.h"
#include "Movement/Movement.h"
#include "ADC/sampel_int.h"
#include "UltrasonicSensor/Ultraljud.h"
#include "Com/Com.h"


volatile xHandlerParameters *xHandler;
volatile xTaskHandle taskHandlerKommunikation;
volatile xTaskHandle taskHandlerNavigering;
volatile xTaskHandle taskHandlerSensor;
volatile xTaskHandle taskHandlerStyrning;
volatile xTaskHandle taskHandlerReglering;
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
	// Insert application code here, after the board has been initialized.
	ioport_init();
	
	//Check pin for the TC-handler
	ioport_set_pin_dir(CHECK_PIN, IOPORT_DIR_OUTPUT);
	//Configuring board settings
	pmc_enable_periph_clk(ID_TRNG);
	trng_enable(TRNG);
	initMovement();
	initUltrasonic();
	
	membag_init();
	initCom();
	delay_ms(100);

	// Initiating board pins
	ioport_set_pin_dir(PIO_PB26_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	ioport_set_pin_dir(PIO_PA15_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PA15_IDX, HIGH);
	ioport_set_pin_dir(PIO_PC1_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PC1_IDX, HIGH);
	ioport_set_pin_dir(PIO_PC19_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PC19_IDX, HIGH);
	
	//Creating semaphores and tasks
	xSemaphoreKommunikation = 0;
	xSemaphoreNavigering = 0;
	xSemaphoreSensor = 0;
	xSemaphoreStyrning = 0;
	xSemaphoreReglering = 0;
	
	printf("Creating semaphores...\n");
	vSemaphoreCreateBinary(xSemaphoreKommunikation);
	vSemaphoreCreateBinary(xSemaphoreNavigering);
	vSemaphoreCreateBinary(xSemaphoreSensor);
	vSemaphoreCreateBinary(xSemaphoreStyrning);
	vSemaphoreCreateBinary(xSemaphoreReglering);
	
	//Semaphores are configured, task1 will be resumed in task_control.c
	xSemaphoreTake(xSemaphoreKommunikation, 0);
	xSemaphoreTake(xSemaphoreNavigering, 0); 
	xSemaphoreTake(xSemaphoreSensor,0);
	xSemaphoreGive(xSemaphoreStyrning); //GLÖM EJ ATT AVKOMMENTERA DESSA EFTER DE OLIKA TESTEN
	
	//Test Nav-Styr
	//xSemaphoreGive(xSemaphoreNavigering);
	//xSemaphoreTake(xSemaphoreStyrning,0);
	
	//Test Kom-Nav
	 //xSemaphoreGive(xSemaphoreKommunikation);
	 //xSemaphoreTake(xSemaphoreNavigering,0);
	 
	 //Test Nav-Sens-Styr
	 //xSemaphoreGive(xSemaphoreSensor);
	 ////xSemaphoreTake(xSemaphoreStyrning,0);
	 //xSemaphoreTake(xSemaphoreNavigering,0);

	printf("Creating task handler...\n");
	
	bool xReturned = false;
	
	printf("Creating tasks...\n");
	
	xReturned = xTaskCreate(task_kommunikation, (const signed char * const) "kommunikation", TASK_KOMMUNIKATION_STACK_SIZE, NULL, TASK_KOMMUNIKATION_PRIORITY, &taskHandlerKommunikation);
	if( xReturned == pdPASS )
	{
		printf("task_kommunikation created...\n");
		
	}
	xReturned = xTaskCreate(task_navigering, (const signed char * const) "navigering", TASK_NAVIGERING_STACK_SIZE, (void *) xHandler, TASK_NAVIGERING_PRIORITY, &taskHandlerNavigering);
	if( xReturned == pdPASS )
	{
		printf("task_navigering created...\n");
		
	}
	xReturned = xTaskCreate(task_sensor, (const signed char * const) "sensor", TASK_SENSOR_STACK_SIZE, (void *) xHandler, TASK_SENSOR_PRIORITY, &taskHandlerSensor);
	if( xReturned == pdPASS )
	{
		printf("task_sensor created...\n");
		
	}
	xReturned = xTaskCreate(task_styrning, (const signed char * const) "styrning", TASK_STYRNING_STACK_SIZE, (void *) xHandler, TASK_STYRNING_PRIORITY, &taskHandlerStyrning);
	if( xReturned == pdPASS )
	{
		printf("task_styrning created...\n");
		
	}
	xReturned = xTaskCreate(task_reglering, (const signed char * const) "tickReglering", TASK_REGLERING_STACK_SIZE, NULL, TASK_REGLERING_PRIORITY, &taskHandlerReglering);
	if( xReturned == pdPASS )
	{
		printf("task_reglering created...\n");
		
	}
	
	printf("Task handler stored in struct xHandlerParameter.h...\n");
	xHandler->taskKommunikation = &taskHandlerKommunikation;
	xHandler->taskNavigering = &taskHandlerNavigering;
	xHandler->taskSensor = &taskHandlerSensor;
	xHandler->taskStyrning = &taskHandlerStyrning;
	xHandler->taskReglering = &taskHandlerReglering;
	
	//Suspend all tasks
	vTaskSuspend(*(xHandler->taskKommunikation));
	vTaskSuspend(*(xHandler->taskNavigering));
	vTaskSuspend(*(xHandler->taskSensor));
	vTaskSuspend(*(xHandler->taskStyrning));
	vTaskSuspend(*(xHandler->taskReglering));
	
	printf("Address stored in &xHandler: %x\n", &xHandler );
	printf("Address stored in xHandler: %x\n", xHandler );
	
	printf("Address stored in &xHandler->taskplayer1: %x\n", &xHandler->taskKommunikation );
	printf("Address stored in &xHandler->taskplayer1: %x\n", &xHandler->taskNavigering );
	printf("Address stored in &xHandler->taskplayer1: %x\n", &xHandler->taskSensor );
	printf("Address stored in &xHandler->taskplayer2: %x\n", &xHandler->taskStyrning );
	
	printf("Address stored in xHandler->taskplayer1: %x\n", xHandler->taskKommunikation );
	printf("Address stored in xHandler->taskplayer1: %x\n", xHandler->taskNavigering );
	printf("Address stored in xHandler->taskplayer1: %x\n", xHandler->taskSensor );
	printf("Address stored in xHandler->taskplayer2: %x\n", xHandler->taskStyrning );
	
	

	
	// Start the FreeRTOS scheduler running all tasks indefinitely
	printf("Starting scheduler...\n");
	xTaskCreate(task_state, (const signed char * const) "state", TASK_STATE_STACK_SIZE, (void *) xHandler, TASK_STATE_PRIORITY, NULL);
	vTaskStartScheduler();
	
	xHandler->check = &checkInt;
	

	
	/*
	while(1){
		delay_ms(500);
		printInt(pulseIn(1));
		
		}
	*/
}
