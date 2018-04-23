/*
 * MotorControl.h
 *
 * Created: 2018-04-17 13:49:32
 *  Author: Sebastian Hoggard
 */ 


#include <asf.h>

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#define PIN_MOTOR_LEFT				1<<25
#define PIN_MOTOR_RIGHT				1<<28
#define PWM_PERIOD_TICKS			50000
#define PULSE_WIDTH_CENTER_TICKS	1500

pwm_channel_t pwm_motorLeft;
pwm_channel_t pwm_motorRight;

void initMotors(void);

void setMotorSpeed(uint16_t, uint16_t);

void stopMotors(void);

#endif /* MOTORCONTROL_H_ */