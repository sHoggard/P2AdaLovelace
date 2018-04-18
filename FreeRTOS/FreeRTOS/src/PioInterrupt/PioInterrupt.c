/*
 * PioInterrupt.c
 *
 * Created: 2018-04-18 10:13:52
 *  Author: George
 */ 

#include "PioInterrupt.h"


void configPioInterrupt(){
	printf("Configuring pio interrupt...");
	quadratureCounter = 0;
	pmc_enable_periph_clk(ID_PIOB);
	pio_set_input(PIOB, PIO_PB14, PIO_DEFAULT);
	printf("setting handler interrupt...");
	pio_handler_set(PIOB, ID_PIOB, PIO_PB14, PIO_IT_FALL_EDGE, myISR);
	pio_enable_interrupt(PIOB, PIO_PB14);
	NVIC_EnableIRQ(PIOB_IRQn);
	ioport_set_pin_dir(PIO_PB27_IDX,IOPORT_DIR_OUTPUT);
	printf("setting D13 pin to LOW...");
	ioport_set_pin_level(PIO_PB27_IDX,LOW);
	printf("setting D53 pin to LOW...");
	ioport_set_pin_level(PIO_PB14_IDX,LOW);
}


void myISR(uint32_t id, uint32_t mask){
	quadratureCounter++;
	printf("myISR\n");
	printf("D13 pin to HIGH\n");
	ioport_set_pin_level(PIO_PB27_IDX,HIGH);
	printf("quadratureCounter: ");
	printf("%" PRIu32 "\n",quadratureCounter);
	
}