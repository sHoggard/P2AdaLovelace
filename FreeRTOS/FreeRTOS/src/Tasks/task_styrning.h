/*
 * task_styrning.h
 *
 * Created: 2018-02-01 11:29:09
 */ 


#include <asf.h>
#include "semphr.h"
#include "task_state.h"
//System modules
#include "../Navigering/angleCalculation.h"
#include "../Utilities/ConsoleFunctions/consoleFunctions.h"


#ifndef TASK_STYRNING_H_
#define TASK_STYRNING_H_

#define TASK_STYRNING_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_STYRNING_PRIORITY   (2)

void task_styrning(void *pvParamters);


#endif /* TASK_STYRNING_H_ */