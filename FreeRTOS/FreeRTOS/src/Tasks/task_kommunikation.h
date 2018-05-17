/*
 * task_kommunikation.h
 *
 * Created: 2018-05-15 09:55:45
 *  Author: Jelena
 */ 
#include <asf.h>
#include "semphr.h"
#include "task_control.h"
#include "../config/conf_AdaLovelace.h"
#include "../TimeTick/time_tick.h"
#include "../Utilities/ConsoleFunctions/consoleFunctions.h"
#include "../TWI_Kommunikationen/KOM_NAV.h"
#include "xHandlerParameters.h"

#ifndef TASK_KOMMUNIKATION_H_
#define TASK_KOMMUNIKATION_H_


#define TASK_KOMMUNIKATION_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_KOMMUNIKATION_PRIORITY   (2)

void task_kommunikation(void *pvParamters);

void fakePositionUpdate(double  xBox,double  yBox,double  xCube,double  yCube,double  xBall,double  yBall,double  xGlass,double yGlass,double  xRob,double  yRob);



#endif /* TASK_KOMMUNIKATION_H_ */