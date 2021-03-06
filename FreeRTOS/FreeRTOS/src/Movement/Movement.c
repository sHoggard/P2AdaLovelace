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

static bool f_auto = false;
static int16_t humanTargetSpeed;
static int32_t humanTargetDistance;
static int32_t targetDistance;
//static uint16_t orientation;
static uint16_t humanTargetOrientation;
static uint16_t targetOrientation;

void updateTargetSpeed(void);
void applyRegulatedSpeeds(void);

/**
 * Initiates everything needed to start sending movement commands and using the regulator task. 
 */
void initMovement()
{
	puts("initMovement");
	#ifdef NO_REGULATION
	puts("No regulation");
	#endif
	
	initMotors();
	initDecoders();
	
	mode_movement = 's';
	regulated_speed.left = 0;
	regulated_speed.right = 0;
	regulated_speed.target = 0;
}

/**
 * Calculates current orientation, and returns it. 
 */
uint16_t orientation()
{
	int32_t orientation = (int)(distanceLeft - distanceRight)%FULL_ROTATION;
	if (orientation < 0)
	{
		orientation += FULL_ROTATION;
	}
	return orientation;
}

/**
 * Makes Arlo move forwards or backwards (negative speed) at given speed (mm/s). 
 * If distance is 0, it will keep moving indefinitely. 
 * If distance is not 0, it will stop at given distance. 
 */
void drive(int16_t speed, uint32_t distance)
{
	mode_movement = 'd';
	if (speed > HUMAN_MAX_SPEED)
	{
		speed = HUMAN_MAX_SPEED;
	}
	else if (speed < (-HUMAN_MAX_SPEED))
	{
		speed = (-HUMAN_MAX_SPEED);
	}
	humanTargetSpeed = speed;
	regulated_speed.target = speed;
	#ifndef DOUBLE_REGULATION
	// TODO: convert mm/s to target pulse
	regulated_speed.left = speed;
	regulated_speed.right = speed;
	#endif	//DOUBLE_REGULATION
	printf("Moving straight %s at %i mm/s\n", (speed >= 0 ? "forwards" : "backwards"), abs(speed));
	
	// calculate target distance
	if (distance == 0)
	{
		f_auto = false;
	}
	else
	{
		f_auto = true;
		humanTargetDistance = distance;
		distance *= 2;
		//distance *= 200;				// both wheels are counted together
		//distance /= 338;				// 3,38mm per pulse
		int32_t startDistance = distanceLeft + distanceRight;
		targetDistance = startDistance + distance;
		printf("Will stop after %i mm\n", abs(distance));
	}
}

/**
 * Makes Arlo rotate clockwise or counter-clockwise (negative speed) at given speed (degrees/s). 
 * If orientation is 0, it will keep rotating indefinitely. 
 * If orientation is not 0, it will stop at given orientation (degrees). 
 */
void rotate(int16_t speed, uint16_t orientation)
{
	mode_movement = 'r';
	if (speed > HUMAN_MAX_SPEED)
	{
		speed = HUMAN_MAX_SPEED;
	}
	else if (speed < (-HUMAN_MAX_SPEED))
	{
		speed = (-HUMAN_MAX_SPEED);
	}
	humanTargetSpeed = speed;
	regulated_speed.target = speed;
	#ifndef DOUBLE_REGULATION
	// TODO: convert degrees/s to target pulse
	regulated_speed.left = speed;
	regulated_speed.right = (-speed);
	#endif	//DOUBLE_REGULATION
	printf("Rotating %s at %i degrees/s\n", (speed >= 0 ? "clockwise" : "counter-clockwise"), abs(speed));
	
	// calculate target orientation
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
	mode_movement = 's';
	f_auto = false;
	stopMotors();
}

/**
 * Clears all counters, meaning angles and distances travelled are counted from after this call. 
 */
void clearCounters()
{
	clearWheelCounters();
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
		
		applyRegulatedSpeeds();
	}
}

/**
 * For testing if speeds are updated after calling drive() or rotate(). 
 */
void test_movement()
{
	printf("test_movement");
	if (f_auto)
	{
		updateTargetSpeed();
	}
	task_regulate(0);
	applyRegulatedSpeeds();
	printf("test_movement END");
}

void updateTargetSpeed()		// should only revise speeds downwards
{
	int16_t targetSpeed = 0;
	int32_t remaining_distance = 0;
	
	// calculate remaining distance
	switch (mode_movement)
	{
		case 'd':
			remaining_distance = targetDistance - (distanceLeft + distanceRight);
			break;
		case 'r':
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
			break;
		case 's':
			return;
	}
	printf("remaining_distance: %i\n", (int)remaining_distance);
	
	// calculate target speed
	switch (mode_movement)
	{
		case 'd':
			if (abs(remaining_distance) < DISTANCE_PRECISION)
			{
				stop();
				regulated_speed.target = 0;
				//delay_ms(10);
				// TODO: precise adjustments
			}
			else if (remaining_distance > 0)
			{
				targetSpeed = (remaining_distance/50)*MOTOR_INCREMENTS + MOTOR_THRESHOLD;
				if (targetSpeed > humanTargetSpeed)
				{
					targetSpeed = humanTargetSpeed;
				}
			}
			else if (remaining_distance < 0)
			{
				targetSpeed = (remaining_distance/50)*MOTOR_INCREMENTS - MOTOR_THRESHOLD;
				if (targetSpeed < humanTargetSpeed)
				{
					targetSpeed = -humanTargetSpeed;
				}
			}
			break;
		case 'r':
			break;
		case 's':
			targetSpeed = 0;
			break;
	}
	printf("targetSpeed: %i\n", (int)targetSpeed);
	
	// send to regulator
	regulated_speed.target = targetSpeed;
}

void applyRegulatedSpeeds()
{
	switch (mode_movement)
	{
		case 'd':
		setMotorSpeed(MOTOR_BRAKE + regulated_speed.left, MOTOR_BRAKE + regulated_speed.right);
		break;
		case 'r':
		setMotorSpeed(MOTOR_BRAKE + regulated_speed.left, MOTOR_BRAKE - regulated_speed.right);
		break;
		case 's':
		stopMotors();
		break;
	}
}