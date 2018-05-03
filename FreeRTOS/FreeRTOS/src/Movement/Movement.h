/*
 * Movement.h
 *
 * Created: 2018-04-30 11:38:45
 *  Author: Sebastian Hoggard
 */ 


#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <inttypes.h>
#include "FreeRTOS.h"
#include "task.h"
#include "xHandlerParameters.h"

#define FULL_ROTATION 731
#define HUMAN_FULL_ROTATION 360			// perhaps 720, for half-degrees?
#define ROTATION_PRECISION 2
#define MOTOR_BRAKE PULSE_WIDTH_BRAKE
#define MOTOR_THRESHOLD 50
#define MAX_SPEED 500					// µs difference from MOTOR_BRAKE
#define HUMAN_MAX_SPEED 300				// mm/s

//xSemaphoreHandle xSemaphoreMovement;

uint16_t orientation(void);
void drive(int16_t speed, uint32_t distance);
void rotate(int16_t speed, uint16_t orientation);
void stop(void);

void task_movement(void *pvParameters);
void test_movement(void);

void task_regulate(void *pvParameters);

#endif /* MOVEMENT_H_ */