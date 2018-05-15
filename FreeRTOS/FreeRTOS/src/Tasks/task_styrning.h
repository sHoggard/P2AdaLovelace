/*
 * task_player2.h
 *
 * Created: 2018-02-01 11:29:09
 *  Author: Spellabbet
 */ 


#include <asf.h>
#include "semphr.h"
#include "task_control.h"
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

#ifndef TASK_STYRNING_H_
#define TASK_STYRNING_H_

#define TASK_PLAYER2_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_PLAYER2_PRIORITY   (2)

void task_styrning(void *pvParamters);


#endif /* TASK_STYRNING_H_ */