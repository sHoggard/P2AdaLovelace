/*
 * Ultraljud.h
 *
 * Created: 2018-05-21 15:27:12
 *  Author: maardookh
 */ 


#ifndef ULTRALJUD_H_
#define ULTRALJUD_H_

#include <asf.h>
#include <inttypes.h>

#define LEFT_SENSOR 1
#define CENTRE_SENSOR 2
#define RIGHT_SENSOR 3

void initUltrasonic(void);

uint16_t pulseIn(int);

#endif /* ULTRALJUD_H_ */