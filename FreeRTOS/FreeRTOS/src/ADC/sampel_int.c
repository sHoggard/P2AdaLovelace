﻿/*
 * sampel_int.c
 *
 * Created: 2013-12-10 12:32:30
 *  Author: Tommy, George Albert Florea, Jack Mao
 */ 

#include <asf.h>
#include "sampel_int.h"
#include "../Utilities/ConsoleFunctions/consoleFunctions.h"

//void TCO_Handler(void);

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;
	uint32_t IR_invalue;
	uint32_t IR_distance;


	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);			//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	ioport_set_pin_level(CHECK_PIN,HIGH);		//put test pin HIGH 
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  //Wait until DRDY get high
	IR_invalue=adc_get_latest_value(ADC);			//get input value
	IR_distance = (192000/(IR_invalue));
	//distance = 4800/(invalue - 20);
	IR_currentdistance = ((IR_distance + IR_lastdistance)/2);
	printInt(IR_currentdistance);
	IR_lastdistance = IR_distance;
	ioport_set_pin_level(CHECK_PIN,LOW);		//put test pin LOW
	
}