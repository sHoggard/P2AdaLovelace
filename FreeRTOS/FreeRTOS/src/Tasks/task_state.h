/*
 * task_state.h
 *
 * Created: 2018-02-01 11:26:49
 *  
 */ 


#ifndef TASK_STATE_H_
#define TASK_STATE_H_

#define TASK_STATE_STACK_SIZE (2048/ sizeof(portSTACK_TYPE)) 
#define TASK_STATE_PRIORITY   (1)

xSemaphoreHandle xSemaphoreKommunikation;
xSemaphoreHandle xSemaphoreNavigering;
xSemaphoreHandle xSemaphoreSensor;
xSemaphoreHandle xSemaphoreStyrning;
xSemaphoreHandle xSemaphoreReglering;

void task_state(void *pvParamters);
void changeState(int newState);

#endif /* TASK_NAVIGERING_H_ */