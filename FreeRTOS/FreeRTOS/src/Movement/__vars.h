/*
 * __vars.h
 *
 * Created: 2018-04-30 15:30:56
 *  Author: Sebastian Hoggard
 */ 


#ifndef __VARS_H_
#define __VARS_H_

#include <inttypes.h>

char mode_movement;

struct s_speed {
	int16_t target;
	int16_t left;
	int16_t right;
} regulated_speed;

#endif /* __VARS_H_ */