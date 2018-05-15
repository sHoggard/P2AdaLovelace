/*
 * task_sensor.h
 *
 * Created: 2018-05-15 10:03:23
 *  Author: Jelena
 */ 

#include "task_control.h"
#include "../Navigering/NAV_SENS_STYR.h"

#ifndef TASK_SENSOR_H_
#define TASK_SENSOR_H_

#define TASK_SENSOR_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_SENSOR_PRIORITY   (2)

void task_sensor(void *pvParamters);


#endif /* TASK_SENSOR_H_ */