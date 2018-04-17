/*
 * conf_tc.c
 *
 * Created: 2013-12-10 08:37:41
 *  Author: Tommy
 */ 

#include <asf.h>
#include "conf_tc.h"

void configure_tc(void)
{
	printf("configure_tc");
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	/* Configure power management of timer clocks */
	pmc_enable_periph_clk(ID_TC0);
	/* Configure TC for a 44,1kHz frequency and trigger
	on RC compare. */
	tc_find_mck_divisor(44100, ul_sysclk, &ul_div,
	&ul_tcclks, ul_sysclk);
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / 44100);
	
	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
	
	/* Configure PMC */
//	pmc_enable_periph_clk(ID_TC0);
//
//	/** Configure TC for a 10 kHz frequency and trigger on RC compare. */
//	tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
//	tc_write_rc(TC0, 0, 4200);					//4200 corresponds to fs = 10 kHz
//
//	/* Configure and enable interrupt on RC compare */
//	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
//	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
//
	printf("tc_start");
	tc_start(TC0, 0);

}

