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
//#include "PioInterrupt/PioInterrupt.h"

#include "conf_board.h"
#include "conf_clock.h"
#include "MotorControl/MotorControl.h"

/**
 * \file
 *
 * \brief PWM LED example for SAM.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 * \mainpage PWM LED Example
 *
 * \par Purpose
 *
 * This example demonstrates a simple configuration of 2 PWM channels to
 * generate variable duty cycle signals.
 * The 2 LEDs on the evaluation kit will glow repeatedly.
 *
 * \section Requirements
 *
 * This example can be used on SAM boards. The 2 required leds need to
 * be connected to PWM output pins, else consider probing the PWM output pins
 * with an oscilloscope.
 *
 * \par Usage
 *
 * -# Initialize system clock and pins setting on board
 * -# Initialize PWM clock
 * -# Configure PIN_PWM_LED0_CHANNEL
 * -# Configure PIN_PWM_LED1_CHANNEL
 * -# Enable interrupt of counter event and PIN_PWM_LED0_CHANNEL
 * & PIN_PWM_LED1_CHANNEL
 * -# Change duty cycle in ISR
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */


/** PWM frequency in Hz */
#define PWM_FREQUENCY      1000
/** Period value of PWM output waveform */
#define PERIOD_VALUE       100
/** Initial duty cycle value */
#define INIT_DUTY_VALUE    50

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PWM LED Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** PWM channel instance for LEDs */
pwm_channel_t g_pwm_channel_led;
//
///**
 //* \brief Interrupt handler for the PWM controller.
 //*/
//#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
//void PWM0_Handler(void)
//#else
//void PWM_Handler(void)
//#endif
//{
	//static uint32_t ul_count = 0;  /* PWM counter value */
	//static uint32_t ul_duty = INIT_DUTY_VALUE;  /* PWM duty cycle rate */
	//static uint8_t fade_in = 1;  /* LED fade in flag */
//
//#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	//uint32_t events = pwm_channel_get_interrupt_status(PWM0);
//#else
	//uint32_t events = pwm_channel_get_interrupt_status(PWM);
//#endif

void PWM_Handler(void)
{
static uint32_t ul_count = 0;  /* PWM counter value */
static uint32_t ul_duty = INIT_DUTY_VALUE;  /* PWM duty cycle rate */
static uint8_t fade_in = 1;  /* LED fade in flag */

uint32_t events = pwm_channel_get_interrupt_status(PWM);



	/* Interrupt on PIN_PWM_LED0_CHANNEL */
	if ((events & (1 << PIN_PWM_LED0_CHANNEL)) ==
	(1 << PIN_PWM_LED0_CHANNEL)) {
		ul_count++;

		/* Fade in/out */
		if (ul_count == (PWM_FREQUENCY / (PERIOD_VALUE - INIT_DUTY_VALUE))) {
			/* Fade in */
			if (fade_in) {
				ul_duty++;
				if (ul_duty == PERIOD_VALUE) {
					fade_in = 0;
				}
				} else {
				/* Fade out */
				ul_duty--;
				if (ul_duty == INIT_DUTY_VALUE) {
					fade_in = 1;
				}
			}

			/* Set new duty cycle */
			ul_count = 0;
			g_pwm_channel_led.channel = PIN_PWM_LED0_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
			pwm_channel_update_duty(PWM0, &g_pwm_channel_led, ul_duty);
#else
			pwm_channel_update_duty(PWM, &g_pwm_channel_led, ul_duty);
#endif
			g_pwm_channel_led.channel = PIN_PWM_LED1_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
			pwm_channel_update_duty(PWM0, &g_pwm_channel_led, ul_duty);
#else
			pwm_channel_update_duty(PWM, &g_pwm_channel_led, ul_duty);
#endif
		}
	}
	}
	
	

/**
 * \brief Application entry point for PWM with LED example.
 * Output PWM waves on LEDs to make them fade in and out.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	//initMotors();
	
	/* Configure the console uart for debug information */
	configureConsole();
	
	/* Output example information */
	puts(STRING_HEADER);
	
	/* Enable PWM peripheral clock */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pmc_enable_periph_clk(ID_PWM0);
#else
	pmc_enable_periph_clk(ID_PWM);
#endif

pio_configure_pin(IOPORT_CREATE_PIN(PIOC, 21), PIO_TYPE_PIO_PERIPH_B);
pio_configure_pin(IOPORT_CREATE_PIN(PIOC, 22), PIO_TYPE_PIO_PERIPH_B);


	/* Disable PWM channels for LEDs */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_disable(PWM0, PIN_PWM_LED0_CHANNEL);
	pwm_channel_disable(PWM0, PIN_PWM_LED1_CHANNEL);
#else
	pwm_channel_disable(PWM, PIN_PWM_LED0_CHANNEL);
	pwm_channel_disable(PWM, PIN_PWM_LED1_CHANNEL);
#endif

	/* Set PWM clock A as PWM_FREQUENCY*PERIOD_VALUE (clock B is not used) */
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY * PERIOD_VALUE,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_init(PWM0, &clock_setting);
#else
	pwm_init(PWM, &clock_setting);
#endif

	/* Initialize PWM channel for LED0 */
	/* Period is left-aligned */
	g_pwm_channel_led.alignment = PWM_ALIGN_LEFT;
	/* Output waveform starts at a low level */
	g_pwm_channel_led.polarity = PWM_LOW;
	/* Use PWM clock A as source clock */
	g_pwm_channel_led.ul_prescaler = PWM_CMR_CPRE_CLKA;
	/* Period value of output waveform */
	g_pwm_channel_led.ul_period = PERIOD_VALUE;
	/* Duty cycle value of output waveform */
	g_pwm_channel_led.ul_duty = INIT_DUTY_VALUE;
	g_pwm_channel_led.channel = PIN_PWM_LED0_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_init(PWM0, &g_pwm_channel_led);
#else
	pwm_channel_init(PWM, &g_pwm_channel_led);
#endif

	/* Enable channel counter event interrupt */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_enable_interrupt(PWM0, PIN_PWM_LED0_CHANNEL, 0);
#else
	pwm_channel_enable_interrupt(PWM, PIN_PWM_LED0_CHANNEL, 0);
#endif

	/* Initialize PWM channel for LED1 */
	/* Period is center-aligned */
	g_pwm_channel_led.alignment = PWM_ALIGN_CENTER;
	/* Output waveform starts at a high level */
	g_pwm_channel_led.polarity = PWM_HIGH;
	/* Use PWM clock A as source clock */
	g_pwm_channel_led.ul_prescaler = PWM_CMR_CPRE_CLKA;
	/* Period value of output waveform */
	g_pwm_channel_led.ul_period = PERIOD_VALUE;
	/* Duty cycle value of output waveform */
	g_pwm_channel_led.ul_duty = INIT_DUTY_VALUE;
	g_pwm_channel_led.channel = PIN_PWM_LED1_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_init(PWM0, &g_pwm_channel_led);

	/* Disable channel counter event interrupt */
	pwm_channel_disable_interrupt(PWM0, PIN_PWM_LED1_CHANNEL, 0);
#else
	pwm_channel_init(PWM, &g_pwm_channel_led);

	/* Disable channel counter event interrupt */
	pwm_channel_disable_interrupt(PWM, PIN_PWM_LED1_CHANNEL, 0);
#endif

	/* Configure interrupt and enable PWM interrupt */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	NVIC_DisableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	NVIC_SetPriority(PWM0_IRQn, 0);
	NVIC_EnableIRQ(PWM0_IRQn);
	
	/* Enable PWM channels for LEDs */
	pwm_channel_enable(PWM0, PIN_PWM_LED0_CHANNEL);
	pwm_channel_enable(PWM0, PIN_PWM_LED1_CHANNEL);
#else
	/*NVIC_DisableIRQ(PWM_IRQn);
	NVIC_ClearPendingIRQ(PWM_IRQn);
	NVIC_SetPriority(PWM_IRQn, 0);
	NVIC_EnableIRQ(PWM_IRQn);
	*/
	/* Enable PWM channels for LEDs */
	pwm_channel_enable(PWM, PIN_PWM_LED0_CHANNEL);
	pwm_channel_enable(PWM, PIN_PWM_LED1_CHANNEL);
#endif


	/* Infinite loop */
	while (1) {
	}
}


/*int main (void)
{
/*
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
	//init_timer();
	ioport_init();
	configPioInterrupt();	
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
/*	printf("Starting scheduler...\n");
	xTaskCreate(task_control, (const signed char * const) "control", TASK_CONTROL_STACK_SIZE, (void *) xHandler, TASK_CONTROL_PRIORITY, NULL);	
	vTaskStartScheduler();
	*/
	//while(1);
	
	
	
/*}*/
