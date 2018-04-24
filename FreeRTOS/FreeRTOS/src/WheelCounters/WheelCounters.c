/*
 * WheelCounters.c
 *
 * Created: 2018-04-17 13:09:42
 *  Author: Sebastian Hoggard
 */ 


#include "WheelCounters.h"

void initSensors()
{
	//pio_get_pin_group(PIOC_BASE_ADDRESS);
	//pio_set_input
	//pio_enable_pin_interrupt
	//pio_configure_interrupt
	
	pio_set_input(PIOC, PINS_SENSORS, PIO_PULLUP);
	
	pio_handler_set(PIOC, ID_PIOC, PINS_SENSORS, PIO_IT_EDGE, counter_ISR);
	NVIC_EnableIRQ(PIOC_IRQn);
	pio_enable_interrupt(PIOC, PINS_SENSORS);
}

void counter_ISR(uint32_t id, uint32_t mask)
{
	//there should be no need to disable interrupts
	//cpu_irq_disable();
	
	//test interrupt call
	//pio_set_output(PIOB, 1<<27, 0, 0, 0);
	//pio_toggle_pin(IOPORT_CREATE_PIN(PIOB, 27));
	//pio_set_pin_high(IOPORT_CREATE_PIN(PIOB, 27));
	//ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	
	if (mask & PIN_SENSOR_L1)
	{
		if (STATUS_SENSOR_L1)
		{
			if (!STATUS_SENSOR_L2)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
		else
		{
			if (STATUS_SENSOR_L2)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
	}
	if (mask & PIN_SENSOR_L2)
	{
		if (STATUS_SENSOR_L2)
		{
			if (STATUS_SENSOR_L1)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
		else
		{
			if (!STATUS_SENSOR_L1)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
	}
	if (mask & PIN_SENSOR_R1)
	{
		if (STATUS_SENSOR_R1)
		{
			if (!STATUS_SENSOR_R2)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
		else
		{
			if (STATUS_SENSOR_R2)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
	}
	if (mask & PIN_SENSOR_R2)
	{
		if (STATUS_SENSOR_R2)
		{
			if (STATUS_SENSOR_R1)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
		else
		{
			if (!STATUS_SENSOR_R1)
			{
				counterLeft++;
			}
			else
			{
				counterLeft--;
			}
		}
	}
}

//void sensorLeft1Event(Pio* p_pio, uint32_t ul_id) {
	//sensorLeft1 = digitalRead(pin_sensorLeft1);
	//if (sensorLeft1 == HIGH) {
		//if (sensorLeft2 == LOW) counterLeft++;
		//if (sensorLeft2 == HIGH) counterLeft--;
	//}
	//if (sensorLeft1 == LOW) {
		//if (sensorLeft2 == HIGH) counterLeft++;
		//if (sensorLeft2 == LOW) counterLeft--;
	//}
//}
//
//void sensorLeft2Event() {
	//sensorLeft2 = digitalRead(pin_sensorLeft2);
	//if (sensorLeft2 == HIGH) {
		//if (sensorLeft1 == HIGH) counterLeft++;
		//if (sensorLeft1 == LOW) counterLeft--;
	//}
	//if (sensorLeft2 == LOW) {
		//if (sensorLeft1 == LOW) counterLeft++;
		//if (sensorLeft1 == HIGH) counterLeft--;
	//}
//}
//
//void sensorRight1Event()
//{
	//sensorRight1 = digitalRead(pin_sensorRight1);
	//if (sensorRight1 == HIGH) {
		//if (sensorRight2 == LOW) counterRight++;
		//if (sensorRight2 == HIGH) counterRight--;
	//}
	//if (sensorRight1 == LOW) {
		//if (sensorRight2 == HIGH) counterRight++;
		//if (sensorRight2 == LOW) counterRight--;
	//}
//}
//
//void sensorRight2Event()
//{
	//sensorRight2 = digitalRead(pin_sensorRight2);
	//if (sensorRight2 == HIGH) {
		//if (sensorRight1 == HIGH) counterRight++;
		//if (sensorRight1 == LOW) counterRight--;
	//}
	//if (sensorRight2 == LOW) {
		//if (sensorRight1 == LOW) counterRight++;
		//if (sensorRight1 == HIGH) counterRight--;
	//}
//}