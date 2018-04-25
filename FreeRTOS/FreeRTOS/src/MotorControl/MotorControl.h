/*
 * MotorControl.h
 *
 * Created: 2018-04-17 13:49:32
 *  Author: Sebastian Hoggard
 */ 


#include <asf.h>


#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#define PIN_MOTOR_LEFT				1<<21
#define PIN_MOTOR_RIGHT				1<<22
#define PIN_BOTH_MOTORS				PIN_MOTOR_LEFT | PIN_MOTOR_RIGHT
#define MOTOR_LEFT					IOPORT_CREATE_PIN(PIOC, 21)
#define MOTOR_RIGHT					IOPORT_CREATE_PIN(PIOC, 22)
#define CHANNEL_MOTOR_LEFT			PWM_CHANNEL_4
#define CHANNEL_MOTOR_RIGHT			PWM_CHANNEL_5
#define PWM_FREQUENCY				100
#define PWM_PERIOD_TICKS			10000
#define PULSE_WIDTH_BRAKE			1500

pwm_channel_t pwm_motorLeft;
pwm_channel_t pwm_motorRight;

void initMotors(void);

void setMotorSpeed(uint16_t, uint16_t);

void stopMotors(void);

#endif /* MOTORCONTROL_H_ */