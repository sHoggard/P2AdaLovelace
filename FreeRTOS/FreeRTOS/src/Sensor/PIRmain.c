/**
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
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <inttypes.h>
//#include "delay.h"
//#include "delayFunctions.h"
//#include "ConsulFunction/consoleFunctions.h"
#include <stdlib.h>
//#include "stdio_serial.h"
#include "time.h"


int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
        board_init();
        sysclk_init();
        ioport_init();
       //configureConsole();
	// Insert application code here, after the board has been initialized.
	ioport_enable_pin(PIO_PB25_IDX); // Enable PIN 2 for PIR
	ioport_set_pin_dir(PIO_PB25_IDX,IOPORT_DIR_INPUT); // Make it INPUT
	
	ioport_enable_pin(PIO_PB27_IDX); //Enable PIN 13 for LED
	ioport_set_pin_dir(PIO_PB27_IDX,IOPORT_DIR_OUTPUT);  // Make it OUTPUT
	
	while(1){
	   while(ioport_get_pin_level(PIO_PB25_IDX))
	   {
		ioport_set_pin_level(PIO_PB27_IDX,HIGH) ;
	 }
	
	   ioport_set_pin_level(PIO_PB27_IDX,LOW);
	}
}
