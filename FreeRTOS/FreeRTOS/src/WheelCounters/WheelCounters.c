/*
 * WheelCounters.c
 *
 * Created: 2018-04-17 13:09:42
 *  Author: Sebastian Hoggard
 */ 


#include "WheelCounters.h"
#include "MotorControl/MotorControl.h"

void initSensors()
{
	#ifdef SOFTDEC
	pio_set_input(PIOC, MASK_SENSORS, PIO_PULLUP);
	
	pio_configure_interrupt(PIOC, MASK_SENSORS, PIO_IT_EDGE);
	NVIC_EnableIRQ(PIOC_IRQn);
	pio_enable_interrupt(PIOC, MASK_SENSORS);
	#else
	// TODO: configure hardware quadrature decoder
	#endif
	
	// test counters with own motor speeds
	//setMotorSpeed(1100, 1600);
}

void PIOC_Handler()
{
	// PIO_ISR is cleared when read, so save interrupt state
	uint32_t mask = PIOC->PIO_ISR & PIOC->PIO_IMR;
	
	// read current status of quadrature pins
	uint32_t status = PIOC->PIO_PDSR & MASK_SENSORS;
	
	// compare to previous status, then update
	//uint32_t pinChange = status ^ previousStatus;
	//previousStatus = status;
	
	// there should be no need to disable and re-enable interrupts
	//cpu_irq_disable();
	
	// methods of testing interrupt call
	//pio_set_output(PIOB, 1<<27, 0, 0, 0);
	//pio_toggle_pin(IOPORT_CREATE_PIN(PIOB, 27));
	//pio_set_pin_high(IOPORT_CREATE_PIN(PIOB, 27));
	//ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	
	if (mask & PIN_SENSOR_L1)
	{
		if (status & PIN_SENSOR_L1)
		{
			if (!(status & PIN_SENSOR_L2))
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
			if (status & PIN_SENSOR_L2)
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
		if (status & PIN_SENSOR_L2)
		{
			if (status & PIN_SENSOR_L1)
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
			if (!(status & PIN_SENSOR_L1))
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
		if (status & PIN_SENSOR_R1)
		{
			if (!(status & PIN_SENSOR_R2))
			{
				counterRight++;
			}
			else
			{
				counterRight--;
			}
		}
		else
		{
			if (status & PIN_SENSOR_R2)
			{
				counterRight++;
			}
			else
			{
				counterRight--;
			}
		}
	}
	if (mask & PIN_SENSOR_R2)
	{
		if (status & PIN_SENSOR_R2)
		{
			if (status & PIN_SENSOR_R1)
			{
				counterRight++;
			}
			else
			{
				counterRight--;
			}
		}
		else
		{
			if (!(status & PIN_SENSOR_R1))
			{
				counterRight++;
			}
			else
			{
				counterRight--;
			}
		}
	}
}

#ifdef HARDDEC
void readFromHardDec()
{
	//ATOMICALLY read from both registers into counter variables
}
#endif