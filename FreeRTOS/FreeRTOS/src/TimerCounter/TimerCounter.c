/*
* TimerCounter.c
*
* Created: 2017-01-11 12:17:31
*  Author: George & Benjamin
* Arrayen räknades ut 
*/

#include <inttypes.h>
#include "asf.h"
#include "TimerCounter.h"
#include "../consoleFunctions.h"
#include "DelayFunctions.h"

//#include <util/delay.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define frequency (uint32_t)( 10)
static uint32_t k = 0;

void init_timer(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	pmc_enable_periph_clk(ID_TC3);
	tc_find_mck_divisor( (frequency*16), ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk );
	tc_init(TC1, 0, ul_tcclks | TC_CMR_CPCTRG); 
	tc_write_rc(TC1, 0, (ul_sysclk / ul_div) / frequency/16);
	
	NVIC_EnableIRQ( (IRQn_Type)ID_TC3 );
	tc_enable_interrupt(TC1, 0, TC_IER_CPCS);
	tc_start(TC1, 0);
}

//double sinx[16] = {0.000, 0.383, 0.707, 0.924, 1.000, 0.924, 0.707, 0.383, 0.000, -0.383, -0.707, -0.924, -1.000, -0.924, -0.707, -0.383}; 

// Dessa värden beräknades genom att använda sinusvärden som tillhandahölls i labbhandleningen. Analoga värdet 1768 motsvarar 1.5V på DAC-utgången vi använder.
// Detta beräknades enligt handledningen. V_ADVREF = 4095. D/A-omvandlaren har arbetsområdet mellan (1/6)*V_ADVREF och (5/6)*V_ADVREF. För att beräkna de 
// analoga värden vi behöver som motsvarar 1.0-2.0V så används ekvationen som tillhandahölls i labbhandledningen:
// k = (Reg1-Reg0)/(V1-V0)
// b = Reg0 - k*V0
// Reg0 = (1/6)*VADVREF= 0,	Reg1 = (5/6)*VADVREF = 4095
// V0 = 0.55V och V1 = 2.75V
// => k = 1861
// => b = 0-1861*0.55 = -1024
// => Reg = 1861*V - 1024
// Spänningen 1V och 1.5V motsvarar analoga värdena 837 respektive 1768 för D/A-omvandlaren. 
// Högsta värdet i arrayen är 2605 och motsvarar 2V vilket beräknats
// genom att lägga samman 1768 + 837/2 = 2605 <=> 1.5V + 0.5V = 2.0V.
// Lägsta värdet i arrayen är 931 och motsvarar 1.0V. Detta beräknades genom att sätta samman 1768 - 837/2 = 931 <=> 1.5V - 0.5V = 1.0V.
uint32_t sinx[16] = {1768, 2089, 2360, 2541, 2605, 2541, 2360, 2089, 1768, 1447, 1176, 995, 931, 995, 1176, 1447 }; 
	
void TC3_Handler(void) 
{
	printf("TC3_Handler");
	ioport_set_pin_level(CHECK_PIN, HIGH);
	
	if(k==16)
	{
		k=0;
	}
	//uint32_t result = (uint32_t)(sinx[k]*837+1768);
	volatile uint32_t ul_dummy;
	ul_dummy = tc_get_status(TC1, 0);
	UNUSED(ul_dummy);
	//dacc_write_conversion_data(DACC, sinx[k]); // (837 = 1V, 1768 = 1.5V)
	k++;
	ioport_set_pin_level(CHECK_PIN, LOW);
}


