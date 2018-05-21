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

 clock_t start_t, end_t, total_t;
 int i;
//uint32_t time_t start=0;
//uint32_t time_t finish;
    long int distance;



long PulseIn(void){
	unsigned long duration=0;
	
	ioport_set_pin_level(PIO_PC25_IDX,LOW); // Säkerställa att pinen börjar med LOW för att sedan räkna hur lång tid det tar tills den blir HIGH
	tc_stop(TC0,0);
	while (ioport_get_pin_level(PIO_PC25_IDX)== LOW){
		
	}
	tc_start(TC0,0);
	
	while (ioport_get_pin_level(PIO_PC25_IDX)==HIGH){
		if(tc_read_cv(TC0,0)/42 > 3000)
		{
			break;
		}
		
	}
	duration=tc_read_cv(TC0,0)/42;//tc_read_cv returnerar räknare värdet. TCLK räknaren körs på 42 MEGA HERTZ
	                              //när vi dividerar det med 42 så får vi det i micro sekunder
	   tc_stop(TC0,0);
	
	
      duration=(duration*10)/58  ; // gör duration till cm enhet genom att dividera med 58 ;  
	return duration;
	
}
int main_SENSOR (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	sysclk_init();
	ioport_init();
	configureConsole();

	
	ioport_enable_pin(PIO_PB27_IDX); // Enable PIN 13 for TRIG
	ioport_set_pin_dir(PIO_PB27_IDX,IOPORT_DIR_OUTPUT); // Make it OUTPUT
	

	ioport_enable_pin(PIO_PC25_IDX); //Enable PIN 5 for ECHO
	ioport_set_pin_dir(PIO_PC25_IDX,IOPORT_DIR_INPUT);  // Make it INPUT
	
	 	pmc_enable_periph_clk(ID_TC0);
	 	tc_init(TC0,0,0);
    
	  
	while(1)     //infinite loop
	{
		unsigned long tid=0;
		//printf ("Characters: %c %c \n", 'a', 65);
		ioport_set_pin_level(PIO_PB27_IDX,LOW);
		delay_us(2);
	    
		ioport_set_pin_level(PIO_PB27_IDX,HIGH);
		
		delay_us(10);
		ioport_set_pin_level(PIO_PB27_IDX,LOW);
		
		   tid = PulseIn();
			
			printf("%ld\n",tid);
		
	}
          
		
			 
		 
}
