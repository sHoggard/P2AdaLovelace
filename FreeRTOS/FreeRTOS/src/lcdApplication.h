/*
 * lcdApplication.h
 *
 * Created: 2015-09-10 08:46:16
 *  Author: Uek
 */ 

#ifndef LCDAPPLICATION_H_
#define LCDAPPLICATION_H_

#include "lcdApplication.h"
#include "buttons.h" /* Ugly to include an h-file in another h-file, but necessary to use buttonType */
#include "lcdFunctions.h"
#include "delayFunctions.h"

int lcdWrite4DigitNumber(int number);
int lcdWriteAsciiString(const char *string);
int lcdWriteButtonValue(buttonType inputButton);

#endif /* LCDAPPLICATION_H_ */