/*
 * task_player1.h
 *
 * Created: 2018-02-01 11:26:49
 *  Author: Spellabbet
 */ 

#include <asf.h>
#include "semphr.h"
#include "task_control.h"


#ifndef TASK_PLAYER1_H_
#define TASK_PLAYER1_H_

#define TASK_PLAYER1_STACK_SIZE (2048/ sizeof(portSTACK_TYPE)) 
#define TASK_PLAYER1_PRIORITY   (2)


void task_player1(void *pvParamters);


#endif /* TASK_PLAYER1_H_ */