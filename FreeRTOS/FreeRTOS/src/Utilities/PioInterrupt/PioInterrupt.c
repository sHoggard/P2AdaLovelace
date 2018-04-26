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
	//PB14 = Digital pin 53
	pio_handler_set(PIOB, ID_PIOB, PIO_PB14, PIO_IT_EDGE, myISR);
	pio_enable_interrupt(PIOB, PIO_PB14);
	NVIC_EnableIRQ(PIOB_IRQn);
	//PB27 = Digital pin 13
	ioport_set_pin_dir(PIO_PB27_IDX,IOPORT_DIR_OUTPUT);
	printf("setting D13 pin to LOW...");
	ioport_set_pin_level(PIO_PB27_IDX,LOW);
	printf("setting D53 pin to LOW...");
	ioport_set_pin_level(PIO_PB14_IDX,LOW);
}


void myISR(uint32_t id, uint32_t mask){
	ioport_set_pin_level(PIO_PB27_IDX,HIGH);
	quadratureCounter++;
	printf("- myISR-\n");
	printf("D13 pin to HIGH\n");
	printf("quadratureCounter: ");
	printf("%" PRIu32 "\n",quadratureCounter);
	volatile int j=0; /* makes sure j doesn't overflow */
	for (int i=0; i<100; i++) /* The delay counter */
	{
		j++; /* some easy predictable operation */
	}
	printf("ISR EoL(3)\n");
	ioport_set_pin_level(PIO_PB27_IDX,LOW);
	
}