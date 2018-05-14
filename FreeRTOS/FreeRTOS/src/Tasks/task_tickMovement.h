/*
 * task_tickMovement.h
 *
 * Created: 2018-05-14 12:19:32
 *  Author: George
 */ 

//System modules
#include "../WheelCounters/WheelCounters.h"
#include "../Navigering/angleCalculation.h"
#include "../config/conf_AdaLovelace.h"
#include "../MotorControl/MotorControl.h"
#include "../WheelCounters/WheelCounters.h"
#include "../Movement/Movement.h"
#include "../TimeTick/time_tick.h"
#include "../Utilities/ConsoleFunctions/consoleFunctions.h"

#include "../Movement/__vars.h"

#ifndef TASK_TICKMOVEMENT_H_
#define TASK_TICKMOVEMENT_H_

#define TASK_TICKMOVEMENT_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_TICKMOVEMENT_PRIORITY   (3)

void task_tickMovement(void *pvParamters);



#endif /* TASK_TICKMOVEMENT_H_ */