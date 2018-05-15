/*
 * task_kommunikation.h
 *
 * Created: 2018-05-15 09:55:45
 *  Author: Jelena
 */ 

#include "task_control.h"
#include "../TWI_Kommunikation/KOM_NAV.h"

#ifndef TASK_KOMMUNIKATION_H_
#define TASK_KOMMUNIKATION_H_


#define TASK_KOMMUNIKATION_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_KOMMUNIKATION_PRIORITY   (2)

void task_kommunikation(void *pvParamters);



#endif /* TASK_KOMMUNIKATION_H_ */