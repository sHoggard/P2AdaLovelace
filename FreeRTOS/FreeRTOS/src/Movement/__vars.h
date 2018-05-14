/*
 * __vars.h
 *
 * Created: 2018-04-30 15:30:56
 *  Author: Sebastian Hoggard
 */ 


#ifndef __VARS_H_
#define __VARS_H_

#include <inttypes.h>

#define CIRCUMFERENCE_LEFT ((double)486)
#define CIRCUMFERENCE_RIGHT ((double)488.5)
#define distanceLeft (counterLeft*CIRCUMFERENCE_LEFT/144)
#define distanceRight (counterRight*CIRCUMFERENCE_RIGHT/144)

char mode_movement;

struct s_speed {
	int16_t target;
	int16_t left;
	int16_t right;
} regulated_speed;

#endif /* __VARS_H_ */