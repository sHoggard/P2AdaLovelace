/*
 * task_control.h
 *
 * Created: 2018-02-01 11:26:49
 *  
 */ 


#ifndef TASK_CONTROL_H_
#define TASK_CONTROL_H_

#define TASK_CONTROL_STACK_SIZE (2048/ sizeof(portSTACK_TYPE)) 
#define TASK_CONTROL_PRIORITY   (1)

xSemaphoreHandle xSemaphoreKommunikation;
xSemaphoreHandle xSemaphoreNavigering;
xSemaphoreHandle xSemaphoreSensor;
xSemaphoreHandle xSemaphoreStyrning;
xSemaphoreHandle xSemaphoreReglering;

void task_control(void *pvParamters);

#endif /* TASK_NAVIGERING_H_ */