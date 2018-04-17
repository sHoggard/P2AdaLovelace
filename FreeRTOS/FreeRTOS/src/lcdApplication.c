/*
* lcdApplication.c
*
* Created: 2016-11-23 16:00:50
* Author: George Albert Florea & Benjamin Sejdic
*/

#include "lcdApplication.h"
#include "buttons.h"	/* to get the buttontype definiton */
#include "lcdFunctions.h"
#include "delayFunctions.h"


int lcdWrite4DigitNumber(int number)
{
	uint8_t temp = number/1000; // get the first digit from number
	lcdWrite(temp + '0', HIGH); // ASCII value for 0(48) + value of temp (0-9)
	number = number - temp*1000; // remove the first digit from number 
	delayMicroseconds(100);
	
	temp = number/100; // get the second digit 
	lcdWrite(temp + '0', HIGH);
	number  = number - temp*100;
	delayMicroseconds(100);
	
	temp = number/10; // get the third digit 
	lcdWrite(temp + '0', HIGH);
	number  = number - temp*10;
	delayMicroseconds(100);
	
	temp = number/1; // get the fourth digit 
	lcdWrite(temp + '0', HIGH);
	number  = number - temp*1;
	delayMicroseconds(100);
	
	return number;	/* Assuming everything went ok */
}

int lcdWriteAsciiString(const char *string)
/* writes an ascii string up to 40 characters on the LCD display */
{
	char *string_ptr = string;
	while(*string_ptr != '\0'){
		lcdWrite(*string_ptr, HIGH);
		*string_ptr++; // move the pointer to the next character
	}
	return 0;	/* Assuming everything went ok */
}

int lcdWriteButtonValue(buttonType inputButton)
/* Writes the text corresponding to one of the buttosn on the LCD dispaly using lcdWriteAsciiString()
* Output should be one of SELECT, LEFT, UP, DOWN, RIGHT on the LCD display
* if no buttons is pushed you can chose on displaying nothing or NONE  */
{
	switch (inputButton)
	{
		case btnRIGHT:
		lcdWriteAsciiString("RIGHT");
		break;
		
		case btnUP:
		lcdWriteAsciiString("UP");
		break;
		
		case btnDOWN:
		lcdWriteAsciiString("DOWN");
		break;
		
		case btnLEFT:
		lcdWriteAsciiString("LEFT");
		break;
		
		case btnSELECT:
		lcdWriteAsciiString("SELECT");
		break;
		
		case btnNONE:
		lcdWriteAsciiString("NONE");
		break;
	}
	return 0;	/* Assuming everything went ok */
}