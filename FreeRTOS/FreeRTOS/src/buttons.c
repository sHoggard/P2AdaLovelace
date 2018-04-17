/*
* buttons.c
*
* Created: 2016-11-23 16:28:53
*  Author: George Albert Florea
*  Author: Benjamin Sejdic
*/
int adc_key_in = 0;

#include "buttons.h"
#include "adcFunctions.h"	/* Must use the value from the ADC to figure out which button */

buttonType readLCDbutton(void)
{
	
	adc_key_in = analogRead(0);
	if(adc_key_in > 3600) {      // If the analogue value is greater than 3600 return no button is pressed
		return btnNONE;
	}
	else if(adc_key_in > 3000) { // Button SELECT pressed
		return btnSELECT;
	}
	else if(adc_key_in > 2000) { // Button LEFT pressed 
		return btnLEFT;
	}
	else if(adc_key_in > 1400) { // Button DOWN pressed 
		return btnDOWN;
	}
	else if(adc_key_in > 500) { // Button UP pressed 
		return btnUP;
	}
	else if(adc_key_in >= 0) { // Button RIGHT pressed 
		return btnRIGHT;
	}
	return btnDOWN;	/* Change to actual value */
}