/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 *   Naser kakadost
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
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <inttypes.h>
#include "delay.h"
//#include "delayFunctions.h"
#include "Utilities/ConsoleFunctions/consoleFunctions.h"
#include <stdlib.h>
#include "stdio_serial.h"
#include "time.h"

char buffer[20];

 clock_t start_t, end_t, total_t;
 int i;
//uint32_t time_t start=0;
//uint32_t time_t finish;
    unsigned long distance;




//unsigned long numloops = 0;
//unsigned long maxloops = 250000;
//unsigned long width = 0;

long PulseIn(void){
	unsigned long duration=0;
	tc_stop(TC0,0);
	while (ioport_get_pin_level(PIO_PC25_IDX)== LOW){
		
	}
	tc_start(TC0,0);
	
	while (ioport_get_pin_level(PIO_PC25_IDX)==HIGH){
		
		
	}
	duration=tc_read_cv(TC0,0);
	tc_stop(TC0,0);
	duration=duration*0.0382;
	return duration;
	
}
/*int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	sysclk_init();
	ioport_init();
	configureConsole();
	//delayInit();
	ioport_enable_pin(PIO_PB27_IDX); // Enable PIN 13 for TRIG
	ioport_set_pin_dir(PIO_PB27_IDX,IOPORT_DIR_OUTPUT); // Make it OUTPUT
	
	ioport_enable_pin(PIO_PC25_IDX); //Enable PIN 5 for ECHO
	ioport_set_pin_dir(PIO_PC25_IDX,IOPORT_DIR_INPUT);  // Make it INPUT
	
	 	pmc_enable_periph_clk(ID_TC0);
	 	tc_init(TC0,0,0);
    
	  
	while(1)     //infinite loop
	{
		unsigned long tid=0;
		
		ioport_set_pin_level(PIO_PB27_IDX,LOW);
		delay_us(2);
	    
		ioport_set_pin_level(PIO_PB27_IDX,HIGH);
		
		delay_us(10);
		ioport_set_pin_level(PIO_PB27_IDX,LOW);
		
		ioport_set_pin_level(PIO_PC25_IDX,LOW); 
		   tid = PulseIn();
				
			 printf("%ld\n",tid);
			
		
	}
          
		
			 
		 
}*/

		  
  
		  

	/*

	   //long pulseInn()
	{
		//
		////timeout zone
		//unsigned long numloops = 0;
		//unsigned long maxloops = 250000;
		//unsigned long width = 0;
		//// wait for the pulse to start
		//while (ioport_get_pin_level(PIO_PC25_IDX)== LOW)
		//{
			//if (numloops++ == maxloops)
			//{
				//printf("brokenLOW\n");
				//break;
			//}
		//}
		//
		//// wait for the pulse to stop @ here we are measuring the pulse width = incrementing the WIDTH value by one each cycle. atmega328 1 micro second is equal to 16 cycles.
		//while (ioport_get_pin_level(PIO_PC25_IDX)==HIGH)
		//{
			//if (numloops++ == maxloops)
			//{
				//printf("brokenHIGH: Too far away\n");
				//break;
			//}
			//width++;
		//}
		//return width/214;
//
   //}*/
