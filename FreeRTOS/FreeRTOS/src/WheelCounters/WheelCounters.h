/*
 * WheelCounters.h
 *
 * Created: 2018-04-17 13:07:42
 *  Author: Sebastian Hoggard
 */ 


#include <asf.h>
#include <inttypes.h>
#include "config/conf_AdaLovelace.h"

#ifndef WHEELCOUNTERS_H_
#define WHEELCOUNTERS_H_

#define SOFTDEC
//#define HARDDEC

#define PIOC_BASE_ADDRESS	0x400E1200U
#define p_PIOC_PDSR			(uint32_t*) (PIOC_BASE_ADDRESS + 0x08)

#define MASK_SENSOR_L1		0x00000004
#define MASK_SENSOR_L2		0x00000008
#define MASK_SENSOR_R1		0x00000040
#define MASK_SENSOR_R2		0x00000080

#define MASK_SENSORS		0x000000CC

#define PIN_SENSOR_L1		PIO_PC2
#define PIN_SENSOR_L2		PIO_PC3
#define PIN_SENSOR_R1		PIO_PC6
#define PIN_SENSOR_R2		PIO_PC7

#define STATUS_SENSOR_L1	(*p_PIOC_PDSR & MASK_SENSOR_L1)
#define STATUS_SENSOR_L2	(*p_PIOC_PDSR & MASK_SENSOR_L2)
#define STATUS_SENSOR_R1	(*p_PIOC_PDSR & MASK_SENSOR_R1)
#define STATUS_SENSOR_R2	(*p_PIOC_PDSR & MASK_SENSOR_R2)

int32_t counterLeft;
int32_t counterRight;

#ifndef ISR_OVERRIDE
uint32_t previousStatus;
#endif

void initDecoders(void);
#ifndef ISR_OVERRIDE
void decoder_ISR(uint32_t id, uint32_t mask);
#endif
#ifdef HARDDEC
void readFromHardDec(void);
#endif
void clearWheelCounters(void);

#endif /* WHEELCOUNTERS_H_ */