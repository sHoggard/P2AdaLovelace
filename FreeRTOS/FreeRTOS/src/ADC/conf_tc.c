﻿/*
 * conf_tc.c
 *
 * Created: 2013-12-10 08:37:41
 *  Author: Tommy, George Albert Florea, Jack Mao
 */ 

#include <asf.h>
#include "conf_tc.h"

void configure_tc()
{
	//configure_tc(5);
}

//void configure_tc(int frequency)
//{
	//if (frequency > 1000)
	//{
		//frequency = 1000;
	//}
//
	///* Configure PMC */
	//pmc_enable_periph_clk(ID_TC0);
//
	///** Configure TC for a 10 kHz frequency and trigger on RC compare. */
	//tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
	//tc_write_rc(TC0, 0, 42000000/frequency);	//4200 corresponds to fs = 10 kHz
//
	///* Configure and enable interrupt on RC compare */
	//NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	//tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
//
	//tc_start(TC0, 0);
//
//}

