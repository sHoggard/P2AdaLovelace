/*
 * WheelCounters.h
 *
 * Created: 2018-04-17 13:07:42
 *  Author: Sebastian Hoggard
 */ 


#include <asf.h>
#include "inttypes.h"

#ifndef WHEELCOUNTERS_H_
#define WHEELCOUNTERS_H_

#define PIOC_BASE_ADDRESS	0x400E1200U
#define p_PIOC_PDSR			(uint32_t*) (PIOC_BASE_ADDRESS + 0x08)

#define PIN_SENSOR_L1		0x00000004
#define PIN_SENSOR_L2		0x00000008
#define PIN_SENSOR_R1		0x00000040
#define PIN_SENSOR_R2		0x00000080

#define STATUS_SENSOR_L1	*p_PIOC_PDSR & PIN_SENSOR_L1
#define STATUS_SENSOR_L2	*p_PIOC_PDSR & PIN_SENSOR_L2
#define STATUS_SENSOR_R1	*p_PIOC_PDSR & PIN_SENSOR_R1
#define STATUS_SENSOR_R2	*p_PIOC_PDSR & PIN_SENSOR_R2

#define PINS_SENSORS		PIN_SENSOR_L1 | PIN_SENSOR_L2 | PIN_SENSOR_R1 | PIN_SENSOR_R2

int32_t counterLeft;
int32_t counterRight;

void initSensors(void);
void counter_ISR(uint32_t id, uint32_t mask);

#endif /* WHEELCOUNTERS_H_ */