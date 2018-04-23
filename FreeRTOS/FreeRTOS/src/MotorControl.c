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
	//first, set as inputs
	pio_set_input(PIOB, PIN_MOTOR_LEFT, PIO_DEFAULT);
	pio_set_input(PIOC, PIN_MOTOR_RIGHT, PIO_DEFAULT);
	
	//wait until both motors are powered up
	while (!pio_get_pin_value(IOPORT_CREATE_PIN(PIOB, 25)) || !pio_get_pin_value(IOPORT_CREATE_PIN(PIOC, 28)))
	{
		//just a semi-colon didn't work
	}
	
	//test progress
	//pio_set_output(PIOB, 1<<27, 0, 0, 0);
	//pio_set_pin_high(IOPORT_CREATE_PIN(PIOB, 27));
	
	//connect peripheral B to pin A23
	pio_configure_pin(IOPORT_CREATE_PIN(PIOB, 25), PIO_TYPE_PIO_PERIPH_B);
	pio_configure_pin(IOPORT_CREATE_PIN(PIOB, 28), PIO_TYPE_PIO_PERIPH_C);
	
	//alternative way to configure the pins
	//pio_set_output(PIOB, PIN_MOTOR_LEFT, 0, 0, 0);
	//pio_set_output(PIOC, PIN_MOTOR_RIGHT, 0, 0, 0);
	
	//test configuration
	//pio_set_pin_high(IOPORT_CREATE_PIN(PIOB, 25));
	//pio_set_pin_high(IOPORT_CREATE_PIN(PIOC, 28));
	
	//enable the peripheral clock for the PWM hardware
	pmc_enable_periph_clk(ID_PWM);
	
	//disable until configured
	pwm_channel_disable(PWM, PWM_CHANNEL_0);
	pwm_channel_disable(PWM, PWM_CHANNEL_1);
	
	//configure clock settings
	pwm_clock_t clock_setting = {
		.ul_clka = 1000000,
		.ul_clkb = 0,
		.ul_mck = 48000000
	};
	
	//apply clock settings
	pwm_init(PWM, &clock_setting);
	
	//assign PWM channels
	pwm_motorLeft.channel = PWM_CHANNEL_0;
	pwm_motorRight.channel = PWM_CHANNEL_1;
	
	//select clock A
	pwm_motorLeft.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_motorRight.ul_prescaler = PWM_CMR_CPRE_CLKA;
	
	//active state is logic high
	pwm_motorLeft.polarity = PWM_HIGH;
	pwm_motorRight.polarity = PWM_HIGH;
	
	//left-aligned mode
	pwm_motorLeft.alignment = PWM_ALIGN_LEFT;
	pwm_motorRight.alignment = PWM_ALIGN_LEFT;
	
	//configure period and duty cycle
	pwm_motorLeft.ul_period = PWM_PERIOD_TICKS;
	pwm_motorRight.ul_period = PWM_PERIOD_TICKS;
	pwm_motorLeft.ul_duty = PULSE_WIDTH_CENTER_TICKS;
	pwm_motorRight.ul_duty = PULSE_WIDTH_CENTER_TICKS;
	
	//apply the channel configuration
	pwm_channel_init(PWM, &pwm_motorLeft);
	pwm_channel_init(PWM, &pwm_motorRight);
	
	//configuration is complete, so enable the channel
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	pwm_channel_enable(PWM, PWM_CHANNEL_1);
	
	//wait for motors to initialize
	delay_ms(5);
	
	//stop motors
	pwm_channel_update_duty(PWM, &pwm_motorLeft, 1500);
	pwm_channel_update_duty(PWM, &pwm_motorRight, 1500);
	
	//wait, for some reason
	delay_ms(20);
	
	//test settings
	pwm_channel_update_duty(PWM, &pwm_motorLeft, 1800);
	pwm_channel_update_duty(PWM, &pwm_motorRight, 1200);
}

void setMotorSpeed(uint16_t speedLeft, uint16_t speedRight)
{
	pwm_channel_update_duty(PWM, &pwm_motorLeft, speedLeft);
	pwm_channel_update_duty(PWM, &pwm_motorRight, speedRight);
}

void stopMotors()
{
	pwm_channel_update_duty(PWM, &pwm_motorLeft, 1500);
	pwm_channel_update_duty(PWM, &pwm_motorRight, 1500);
}