/*
 * task_navigering.h
 *
 * Created: 2018-02-01 11:26:49
 */ 

#include <asf.h>
#include "semphr.h"
#include "task_control.h"
#include "../Utilities/ConsoleFunctions/consoleFunctions.h"
#include "../Navigering/angleCalculation.h"
#include "../Navigering/NAV_SENS_STYR.h"
#include "../Movement/Movement.h"
#include "../TWI_Kommunikationen/KOM_NAV.h"


#ifndef TASK_NAVIGERING_H_
#define TASK_NAVIGERING_H_

#define TASK_NAVIGERING_STACK_SIZE (2048/ sizeof(portSTACK_TYPE)) 
#define TASK_NAVIGERING_PRIORITY   (2)


void task_navigering(void *pvParamters);

void testStyr(int typo);

void fakePositionUpdateNAV(double  xBox,double  yBox,double  xCube,double  yCube,double  xBall,double  yBall,double  xGlass,double yGlass,double  xRob,double  yRob);


#endif /* TASK_NAVIGERING_H_ */