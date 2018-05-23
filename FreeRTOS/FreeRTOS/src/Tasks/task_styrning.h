/*
 * task_styrning.h
 *
 * Created: 2018-02-01 11:29:09
 */ 


#include <asf.h>
#include "semphr.h"
#include "task_state.h"
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
#include "../Navigering/NAV_SENS_STYR.h"

#ifndef TASK_STYRNING_H_
#define TASK_STYRNING_H_

#define TASK_STYRNING_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_STYRNING_PRIORITY   (2)

void task_styrning(void *pvParamters);


#endif /* TASK_STYRNING_H_ */