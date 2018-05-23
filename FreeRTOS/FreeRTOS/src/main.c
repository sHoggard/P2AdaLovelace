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
	//Init movement
	initMovement();
	//Init ultrasonic sensors
	printf("initUltrasonic()");
	initUltrasonic();
	
	//Init communication, TWI, I2C
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
	printf("Creating task handlers...\n");
	printf("Creating tasks...\n");
	bool xReturned = false;
	xReturned = xTaskCreate(task_kommunikation, (const signed char * const) "kommunikation", TASK_KOMMUNIKATION_STACK_SIZE, NULL, TASK_KOMMUNIKATION_PRIORITY, &taskHandlerKommunikation);
	xReturned ? printf("task_kommunikation created...\n"): printf("create task failed");
		
	xReturned = xTaskCreate(task_navigering, (const signed char * const) "navigering", TASK_NAVIGERING_STACK_SIZE, (void *) xHandler, TASK_NAVIGERING_PRIORITY, &taskHandlerNavigering);
	xReturned ? printf("task_navigering created...\n"): printf("create task failed");
	
	xReturned = xTaskCreate(task_sensor, (const signed char * const) "sensor", TASK_SENSOR_STACK_SIZE, (void *) xHandler, TASK_SENSOR_PRIORITY, &taskHandlerSensor);
	xReturned ? printf("task_sensor created...\n"): printf("create task failed");
		
	xReturned = xTaskCreate(task_styrning, (const signed char * const) "styrning", TASK_STYRNING_STACK_SIZE, (void *) xHandler, TASK_STYRNING_PRIORITY, &taskHandlerStyrning);
	xReturned ? printf("task_styrning created...\n"): printf("create task failed");
		
	xReturned = xTaskCreate(task_reglering, (const signed char * const) "tickReglering", TASK_REGLERING_STACK_SIZE, NULL, TASK_REGLERING_PRIORITY, &taskHandlerReglering);
	xReturned ? printf("task_reglering created...\n"): printf("create task failed");
	
	printf("Task handler stored in struct xHandlerParameter.h...\n");
	xHandler->taskKommunikation = &taskHandlerKommunikation;
	xHandler->taskNavigering = &taskHandlerNavigering;
	xHandler->taskSensor = &taskHandlerSensor;
	xHandler->taskStyrning = &taskHandlerStyrning;
	xHandler->taskReglering = &taskHandlerReglering;
	
	printf("Suspending all tasks...");
	vTaskSuspend(*(xHandler->taskKommunikation));
	vTaskSuspend(*(xHandler->taskNavigering));
	vTaskSuspend(*(xHandler->taskSensor));
	vTaskSuspend(*(xHandler->taskStyrning));
	vTaskSuspend(*(xHandler->taskReglering));
		
	// Start the FreeRTOS scheduler running all tasks indefinitely
	printf("Starting scheduler...\n");
	xTaskCreate(task_state, (const signed char * const) "state", TASK_STATE_STACK_SIZE, (void *) xHandler, TASK_STATE_PRIORITY, NULL);
	xHandler->check = &checkInt;
	vTaskStartScheduler();
	while(1);
}
