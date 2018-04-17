/*
* adcFunctions.c
*
* Created: 2016-11-23 09:00:18
*  Author: George Albert Florea & Benjamin Sejdic 
*/

#include <inttypes.h>
#include <asf.h>
#include <adc.h>
#include "adcFunctions.h"
#include "delayFunctions.h"

int analogInit(int pinNumber)
{
	
	/*
	* The pin number is the analog input pin on the DUe board, see http://www.arduino.cc/en/Hacking/PinMappingSAM3X
	* Obviously it starts at analog 0 which is equivalent to the analog input on PA16
	* so you need to figure out which AD channel this corresponds to
	*
	* See code example http://asf.atmel.com/docs/latest/sam.drivers.adc.adc_example.arduino_due_x/html/sam_adc_quickstart.html
	* It is assumed that the AD-converter is using 12 bits
	*/
	
	pmc_enable_periph_clk(ID_ADC);	/* power the clock for the ADC with pmc_enable_periph_clk(ID_ADC) */

	if(pinNumber == 0) { // IF pinNumber == A0
		adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
		adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
		adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
		adc_enable_channel(ADC, ADC_CHANNEL_7);
		adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	}
	
	return 0;	/* if everything is ok */
}

uint32_t analogRead(int pinNumber)
{
	adc_start(ADC);
	delayMicroseconds(200);
	uint32_t result = 1;
	if(pinNumber == 0){
		result = adc_get_channel_value(ADC, ADC_CHANNEL_7);
	}
	return result;	// value read from A/D input
}