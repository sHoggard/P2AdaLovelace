/*
 * Movement.c
 *
 * Created: 2018-04-30 11:53:58
 *  Author: Sebastian Hoggard
 */ 

#include <asf.h>
#include <stdbool.h>
#include "Movement.h"
#include "__vars.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"

char mode = 's';

static bool f_auto = false;
static int32_t humanTargetDistance;
static int32_t targetDistance;
//static uint16_t orientation;
static uint16_t humanTargetOrientation;
static uint16_t targetOrientation;

void updateTargetSpeed(void);
void applyRegulatedSpeeds(void);

void initMovement()
{
	initMotors();
	initSensors();
	
	mode = 's';
	regulated_speed.left = 0;
	regulated_speed.right = 0;
	regulated_speed.target = 0;
}

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
 * Makes Arlo move forward or backward (negative speed) at given speed (mm/s). 
 * If distance is 0, it will keep moving indefinitely. 
 * If distance is not 0, it will stop at given distance. 
 */
void drive(int16_t speed, uint32_t distance)
{
	mode = 'd';
	// TODO: convert mm/s to target pulse
	if (speed > HUMAN_MAX_SPEED)
	{
		speed = HUMAN_MAX_SPEED;
	}
	else if (speed < (-HUMAN_MAX_SPEED))
	{
		speed = (-HUMAN_MAX_SPEED);
	}
	regulated_speed.target = speed;
	if (distance == 0)
	{
		f_auto = false;
	}
	else
	{
		f_auto = true;
		humanTargetDistance = distance;
		distance *= 200;				// both wheels are counted together
		distance /= 338;				// 3,38mm per pulse
		int32_t startDistance = counterLeft + counterRight;
		targetDistance = startDistance + distance;
	}
}

/**
 * Makes Arlo rotate clockwise or counter-clockwise (negative speed) at given speed (degrees/s). 
 * If orientation is 0, it will keep rotating indefinitely. 
 * If orientation is not 0, it will stop at given orientation (degrees). 
 */
void rotate(int16_t speed, uint16_t orientation)
{
	mode = 'r';
	// TODO: convert degrees/s to target pulse
	if (speed > HUMAN_MAX_SPEED)
	{
		speed = HUMAN_MAX_SPEED;
	}
	else if (speed < (-HUMAN_MAX_SPEED))
	{
		speed = (-HUMAN_MAX_SPEED);
	}
	orientation %= HUMAN_FULL_ROTATION;
	if (orientation == 0)
	{
		f_auto = false;
	}
	else
	{
		f_auto = true;
		humanTargetOrientation = orientation;
		orientation *= FULL_ROTATION;
		orientation /= HUMAN_FULL_ROTATION;
		targetOrientation = orientation;
	}
}

/**
 * Makes Arlo stop immediately. 
 */
void stop()
{
	mode = 's';
	f_auto = false;
	setMotorSpeed(MOTOR_BRAKE, MOTOR_BRAKE);
}

/**
 * FreeRTOS task, running continuously when needed, for updating motor speeds to follow commands. 
 * Calculates appropriate speed in mm/s. Sends regulated motor speeds to MotorControl. 
 */
void task_movement(void *pvParameters)
{
	while (1)
	{
		// update target speed?
		if (f_auto)
		{
			updateTargetSpeed();
		}
		// apply regulated motor speeds

	}
}

/**
 * For testing if speeds are updated after calling drive() or rotate(). 
 */
void test_movement()
{
	task_regulate(0);
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

void updateTargetSpeed()
{
	int16_t targetSpeed = 0;
	int32_t remaining_distance = 0;
	// calculate remaining distance
	if (mode == 'd')
	{
		remaining_distance = counterLeft + counterRight - targetDistance;
	}
	else if (mode == 'r')
	{
		remaining_distance = orientation() - targetOrientation;
		// shortest path
		if (remaining_distance > FULL_ROTATION/2)
		{
			remaining_distance -= FULL_ROTATION;
		}
		if (remaining_distance < (-FULL_ROTATION/2))
		{
			remaining_distance += FULL_ROTATION;
		}
	}
	// calculate target speed
	if (remaining_distance == 0)
	{
		mode = 's';
		regulated_speed.target = 0;
		//setMotorSpeed(MOTOR_BRAKE, MOTOR_BRAKE);
		//delay_ms(10);
		// precise adjustments
	}
	else if (remaining_distance > 0)
	{
		targetSpeed = targetDistance/50;
		if (targetSpeed > HUMAN_MAX_SPEED)
		{
			targetSpeed = HUMAN_MAX_SPEED;
		}
	}
	else if (remaining_distance < 0)
	{
		targetSpeed = targetDistance/50;
		if (targetSpeed < HUMAN_MAX_SPEED)
		{
			targetSpeed = -HUMAN_MAX_SPEED;
		}
	}
	// send to regulator
	regulated_speed.target = targetSpeed;
}

void applyRegulatedSpeeds()
{
	switch (mode)
	{
		case 'd':
		setMotorSpeed(MOTOR_BRAKE + regulated_speed.left, MOTOR_BRAKE + regulated_speed.right);
		break;
		case 'r':
		setMotorSpeed(MOTOR_BRAKE + regulated_speed.left, MOTOR_BRAKE - regulated_speed.right);
		break;
		case 's':
		setMotorSpeed(MOTOR_BRAKE, MOTOR_BRAKE);
		break;
	}
}