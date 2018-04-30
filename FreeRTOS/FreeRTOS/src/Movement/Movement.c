/*
 * Movement.c
 *
 * Created: 2018-04-30 11:53:58
 *  Author: Sebastian Hoggard
 */ 

#include <asf.h>
#include "Movement.h"
#include "__vars.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"
#include "FreeRTOS.h"
#include "task.h"
#include "xHandlerParameters.h"
#include <stdbool.h>

static bool f_auto = false;
static int32_t startDistance;
static int32_t targetDistance;
//static uint16_t orientation;
static uint16_t targetOrientation;

/**
 * Calculates current orientation, and returns it. 
 */
uint16_t orientation()
{
	int32_t orientation = (counterLeft - counterRight)%FULL_ROTATION;
	if (orientation < 0)
	{
		orientation += FULL_ROTATION;
	}
	return orientation;
}

/**
 * Makes ARLO move forward or backward (negative speed) at given speed (mm/s). 
 * If distance is 0, it will keep moving indefinitely. 
 * If distance is not 0, it will stop at given distance. 
 */
void drive(int16_t speed, uint32_t distance)
{
	mode = 'd';
	// TODO: convert mm/s to target pulse
	if (speed > MAX_SPEED)
	{
		speed = MAX_SPEED;
	}
	regulated_speed.target = speed;
	if (distance == 0)
	{
		f_auto = false;
	}
	else
	{
		f_auto = true;
		distance *= 200;		// both wheels are counted together
		distance /= 338;		// 3,38mm per pulse
		startDistance = counterLeft + counterRight;
		targetDistance = startDistance + distance;
	}
}

/**
 * Makes ARLO rotate clockwise or counter-clockwise (negative speed) at given speed (degrees/s). 
 * If orientation is 0, it will keep rotating indefinitely. 
 * If orientation is not 0, it will stop at given orientation. 
 */
void rotate(int16_t speed, uint16_t orientation)
{
	mode = 'r';
	// TODO: convert degrees/s to target pulse
	if (speed > MAX_SPEED)
	{
		speed = MAX_SPEED;
	}
	if (orientation == 0)
	{
		f_auto = false;
	}
	else
	{
		f_auto = true;
		targetOrientation = orientation;
	}
}

/**
 * Makes ARLO stop immediately. 
 */
void stop()
{
	mode = 's';
	f_auto = false;
	setMotorSpeed(MOTOR_BRAKE, MOTOR_BRAKE);
}

void task_movement(void *pvParameters)
{
	while (1)
	{
		switch (mode)
		{
			case 'd':
				setMotorSpeed(MOTOR_BRAKE + regulated_speed.target, MOTOR_BRAKE + regulated_speed.target);
				break;
			case 'r':
				setMotorSpeed(MOTOR_BRAKE + regulated_speed.target, MOTOR_BRAKE - regulated_speed.target);
				break;
			case 's':
				setMotorSpeed(MOTOR_BRAKE, MOTOR_BRAKE);
				break;
		}
	}
}

/**
 * For testing if speeds are updated after calling drive() or rotate(). 
 */
void test_movement()
{
	switch (mode)
	{
		case 'd':
		setMotorSpeed(MOTOR_BRAKE + regulated_speed.target, MOTOR_BRAKE + regulated_speed.target);
		break;
		case 'r':
		setMotorSpeed(MOTOR_BRAKE + regulated_speed.target, MOTOR_BRAKE - regulated_speed.target);
		break;
		case 's':
		setMotorSpeed(MOTOR_BRAKE, MOTOR_BRAKE);
		break;
	}
}