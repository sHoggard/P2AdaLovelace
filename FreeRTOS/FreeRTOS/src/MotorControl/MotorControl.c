/*
 * MotorControl.c
 *
 * Created: 2018-04-17 14:46:09
 *  Author: Sebastian Hoggard
 */ 


#include "MotorControl.h"
#include "delay.h"

void initMotors()
{
	// first, set as inputs
	pio_set_input(PIOC, PIN_BOTH_MOTORS, PIO_DEFAULT);
	//pio_set_input(PIOC, PIN_MOTOR_RIGHT, PIO_DEFAULT);
	
	// apparently, pins need to unload their charge
	delay_ms(20);
	
	// wait until both motors are powered up
	while (!pio_get_pin_value(MOTOR_LEFT) || !pio_get_pin_value(MOTOR_RIGHT));
	
	// test progress with built-in LED
	//pio_set_output(PIOB, 1<<27, 0, 0, 0);
	//pio_set_pin_high(IOPORT_CREATE_PIN(PIOB, 27));
	
	// connect peripheral B to pin A23
	pio_configure_pin(MOTOR_LEFT, PIO_TYPE_PIO_PERIPH_B);
	pio_configure_pin(MOTOR_RIGHT, PIO_TYPE_PIO_PERIPH_B);
	
	// alternative way to configure the pins
	//pio_set_peripheral(PIOC, PIO_TYPE_PIO_PERIPH_B, PIN_BOTH_MOTORS);
	
	// enable the peripheral clock for the PWM hardware
	pmc_enable_periph_clk(ID_PWM);
	
	// disable until configured
	pwm_channel_disable(PWM, CHANNEL_MOTOR_LEFT);
	pwm_channel_disable(PWM, CHANNEL_MOTOR_RIGHT);
	
	// configure clock settings
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY*PWM_PERIOD_TICKS,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	
	// apply clock settings
	pwm_init(PWM, &clock_setting);
	
	// assign PWM channels
	pwm_motorLeft.channel = CHANNEL_MOTOR_LEFT;
	pwm_motorRight.channel = CHANNEL_MOTOR_RIGHT;
	
	// select clock A
	pwm_motorLeft.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_motorRight.ul_prescaler = PWM_CMR_CPRE_CLKA;
	
	// active state is logic high
	pwm_motorLeft.polarity = PWM_LOW;
	pwm_motorRight.polarity = PWM_LOW;
	
	// left-aligned mode
	pwm_motorLeft.alignment = PWM_ALIGN_LEFT;
	pwm_motorRight.alignment = PWM_ALIGN_LEFT;
	
	// configure period and duty cycle
	pwm_motorLeft.ul_period = PWM_PERIOD_TICKS;
	pwm_motorRight.ul_period = PWM_PERIOD_TICKS;
	pwm_motorLeft.ul_duty = PULSE_WIDTH_BRAKE;
	pwm_motorRight.ul_duty = PULSE_WIDTH_BRAKE;
	
	// apply the channel configuration
	pwm_channel_init(PWM, &pwm_motorLeft);
	pwm_channel_init(PWM, &pwm_motorRight);
	
	// configuration is complete, so enable the channel
	pwm_channel_enable(PWM, CHANNEL_MOTOR_LEFT);
	pwm_channel_enable(PWM, CHANNEL_MOTOR_RIGHT);
	
	// wait, because the motors are not ready
	delay_ms(20);
	
	// test settings
	//pwm_channel_update_duty(PWM, &pwm_motorLeft, 1800);
	//pwm_channel_update_duty(PWM, &pwm_motorRight, 1200);
}

void setMotorSpeed(uint16_t speedLeft, uint16_t speedRight)
{
	pwm_channel_update_duty(PWM, &pwm_motorLeft, speedLeft);
	pwm_channel_update_duty(PWM, &pwm_motorRight, speedRight);
}

void stopMotors()
{
	pwm_channel_update_duty(PWM, &pwm_motorLeft, PULSE_WIDTH_BRAKE);
	pwm_channel_update_duty(PWM, &pwm_motorRight, PULSE_WIDTH_BRAKE);
}