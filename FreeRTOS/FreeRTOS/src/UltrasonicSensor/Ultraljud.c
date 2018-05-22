/*
 * Ultraljud.c
 *
 * Created: 2018-05-21 15:26:10
 *  Author: maardookh
 */ 

#include "Ultraljud.h"


void initUltrasonic()
{
	pmc_enable_periph_clk(ID_TC0); // Enable clock
	tc_init(TC0,0,0); // init clock
}
uint16_t pulseIn(int sensor){
	int echo, trigger;
	unsigned long duration=0;
	
	// Säkerställa att pinen börjar med LOW för att sedan räkna hur lång tid det tar tills den blir HIGH
	tc_stop(TC0,0);
	
	switch(sensor){
		
		case LEFT_SENSOR: // sensor 1
		trigger = PIO_PB26_IDX; //PIN 22
		echo   = PIO_PA14_IDX; //PIN 23
		break;
		
		case CENTRE_SENSOR:   // sensor 2
		trigger = PIO_PA15_IDX; //PIN 24
		echo   = PIO_PD0_IDX; //PIN 25
		break;
		
		
		case RIGHT_SENSOR:   // sensor 3
		trigger = PIO_PD1_IDX; //PIN 26
		echo   = PIO_PD2_IDX; //PIN 27
		break;
		
		default:
		trigger = PIO_PA15_IDX; //PIN 24
		echo   = PIO_PD0_IDX; //PIN 25
		break;
	}
	
	// init
	ioport_enable_pin(trigger); // Enable PIN 22 for TRIG
	ioport_set_pin_dir(trigger,IOPORT_DIR_OUTPUT); // Make it OUTPUT

	ioport_enable_pin(echo); //Enable PIN 23 for ECHO
	ioport_set_pin_dir(echo,IOPORT_DIR_INPUT);  // Make it INPUT
	
	ioport_set_pin_level(echo,LOW);
	
	
	ioport_set_pin_level(trigger,LOW);
	delay_us(2);
	ioport_set_pin_level(trigger,HIGH);
	delay_us(10);
	ioport_set_pin_level(trigger,LOW);
	
	while (ioport_get_pin_level(echo)== LOW){
		
	}
	tc_start(TC0,0);
	
	while (ioport_get_pin_level(echo)==HIGH){
		if ((tc_read_cv(TC0,0)/42) > 3000){
			break;
		}
		
	}
	duration=tc_read_cv(TC0,0)/42;//tc_read_cv returnerar räknare värdet. TCLK räknaren körs på 42 MEGA HERTZ
	//när vi dividerar det med 42 så får vi det i micro sekunder
	tc_stop(TC0,0);
	duration=duration*10; // svar i mm
	duration=duration/58  ; // gör duration till cm enhet genom att dividera med 58 ;

	return duration;
}