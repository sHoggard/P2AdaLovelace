/*
 * WheelCounters.c
 *
 * Created: 2018-04-17 13:09:42
 *  Author: Sebastian Hoggard
 */ 


#include "WheelCounters.h"
#include "MotorControl/MotorControl.h"
#include "config/conf_AdaLovelace.h"

void initDecoders()
{
	puts("initDecoders");
	#ifdef SOFTDEC
	puts("Software decoding");
	#endif
	#ifdef ISR_OVERRIDE
	puts("PIOC_Handler overridden");
	#endif
	#ifdef HARDDEC
	puts("Hardware decoding");
	#endif
	
	#ifdef SOFTDEC
	pio_set_input(PIOC, MASK_SENSORS, PIO_PULLUP);
	
	#ifdef ISR_OVERRIDE
	pio_configure_interrupt(PIOC, MASK_SENSORS, PIO_IT_EDGE);
	#else
	pio_handler_set(PIOC, ID_PIOC, MASK_SENSORS, PIO_IT_EDGE, decoder_ISR);
	#endif
	NVIC_EnableIRQ(PIOC_IRQn);
	pio_enable_interrupt(PIOC, MASK_SENSORS);
	#endif
	#ifdef HARDDEC
	// TODO: configure hardware quadrature decoder
	#endif
	
	// test counters with custom motor speeds
	//setMotorSpeed(1100, 1600);
	
	counterLeft = 0;
	counterRight = 0;
}

#ifdef ISR_OVERRIDE
void PIOC_Handler()
#else
void decoder_ISR(uint32_t id, uint32_t mask)
#endif
{
	#ifdef ISR_OVERRIDE
	// PIO_ISR is cleared when read, so save interrupt state
	uint32_t pinChange = PIOC->PIO_ISR & PIOC->PIO_IMR;
	#endif
	
	// read current status of quadrature pins
	uint32_t status = PIOC->PIO_PDSR & MASK_SENSORS;
	
	#ifndef ISR_OVERRIDE
	// compare to previous status, then update
	uint32_t pinChange = status ^ previousStatus;
	previousStatus = status;
	#endif
	
	// there should be no need to disable and re-enable interrupts
	//cpu_irq_disable();
	
	// methods of testing interrupt call
	//pio_set_output(PIOB, 1<<27, 0, 0, 0);
	//pio_toggle_pin(IOPORT_CREATE_PIN(PIOB, 27));
	//pio_set_pin_high(IOPORT_CREATE_PIN(PIOB, 27));
	//ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	
	if (pinChange & PIN_SENSOR_L1)
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
	if (pinChange & PIN_SENSOR_L2)
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
	if (pinChange & PIN_SENSOR_R1)
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
	if (pinChange & PIN_SENSOR_R2)
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

void clearWheelCounters()
{
	counterLeft = 0;
	counterRight = 0;
}