/*
 * task_player2.h
 *
 * Created: 2018-02-01 11:29:09
 *  Author: Spellabbet
 */ 


#include <asf.h>
#include "semphr.h"
#include "task_control.h"

#ifndef TASK_INTERRUPT_H_
#define TASK_INTERRUPT_H_

#define TASK_INTERRUPT_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_INTERRUPT_PRIORITY   (1)

void task_interrupt(void *pvParamters);


#endif /* TASK_INTERRUPT_H_ */