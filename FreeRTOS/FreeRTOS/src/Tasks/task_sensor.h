/*
 * task_sensor.h
 *
 * Created: 2018-05-15 10:03:23
 *  Author: Jelena
 */ 
#include <asf.h>
#include "semphr.h"
#include "task_state.h"
#include "../Navigering/NAV_SENS_STYR.h"

#ifndef TASK_SENSOR_H_
#define TASK_SENSOR_H_

#define TASK_SENSOR_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_SENSOR_PRIORITY   (2)

#define OBJECT_PROXIMITY 500
#define US_OFFSET 0
#define IR_OFFSET 180

uint32_t US_currentdistance;

uint16_t US_edgeLeft;
uint16_t US_edgeRight;

uint16_t IR_edgeLeft;
uint16_t IR_edgeRight;

uint16_t objectCentre;

void initEdges(void);

void task_sensor(void *pvParamters);


#endif /* TASK_SENSOR_H_ */