/*
 * NoRegulation.c
 *
 * Created: 2018-05-01 11:48:35
 *  Author: Sebastian Hoggard
 */ 

#include "conf_AdaLovelace.h"
#include "Movement.h"
#include "__vars.h"

#ifdef NO_REGULATION
/**
 * Determines appropriate motor speed, given desired speed. 
 * Placeholder for PID. 
 */
void task_regulate(void *pvParameters)
{
	// move duplicate code here?
	int16_t targetSpeed = regulated_speed.target;
	targetSpeed += MOTOR_THRESHOLD;
	if (targetSpeed > MAX_SPEED)
	{
		targetSpeed = MAX_SPEED;
	}
	else if (targetSpeed < (-MAX_SPEED))
	{
		targetSpeed = (-MAX_SPEED);
	}
	switch (mode)
	{
		case 'd': 
			regulated_speed.left = targetSpeed;
			regulated_speed.right = targetSpeed;
			break;
		case 'r':
			regulated_speed.left = targetSpeed;
			regulated_speed.right = -targetSpeed;
			break;
	}
}
#endif