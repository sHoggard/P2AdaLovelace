/*
 * task_player1.h
 *
 * Created: 2018-02-01 11:26:49
 *  Author: Spellabbet
 */ 


#ifndef TASK_CONTROL_H_
#define TASK_CONTROL_H_

#define TASK_CONTROL_STACK_SIZE (2048/ sizeof(portSTACK_TYPE)) 
#define TASK_CONTROL_PRIORITY   (2)


xSemaphoreHandle xSemaphorePlayer1;
xSemaphoreHandle xSemaphorePlayer2;

void task_control(void *pvParamters);

#endif /* TASK_PLAYER1_H_ */