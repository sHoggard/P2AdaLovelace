/*
 * task_player1.h
 *
 * Created: 2018-02-01 11:26:49
 *  Author: Spellabbet
 */ 


#ifndef TASK_PLAYER1_H_
#define TASK_PLAYER1_H_

#define TASK_PLAYER1_STACK_SIZE (2048/ sizeof(portSTACK_TYPE)) 
#define TASK_PLAYER1_PRIORITY   (1)


void task_player1(void *pvParamters);


#endif /* TASK_PLAYER1_H_ */