/*
 * task_player1.h
 *
 * Created: 2018-02-01 11:26:49
 *  Author: Spellabbet
 */ 

#include <asf.h>
#include "semphr.h"
#include "task_control.h"
#include "../Utilities/ConsoleFunctions/consoleFunctions.h"
#include "../Navigering/angleCalculation.h"


#ifndef TASK_NAVIGERING_H_
#define TASK_NAVIGERING_H_

#define TASK_NAVIGERING_STACK_SIZE (2048/ sizeof(portSTACK_TYPE)) 
#define TASK_NAVIGERING_PRIORITY   (2)


void task_navigering(void *pvParamters);


#endif /* TASK_NAVIGERING_H_ */