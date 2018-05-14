/*
 * xHandlerParameter.h
 *
 * Created: 2018-04-12 12:25:42
 *  Author: George
 */ 


#ifndef XHANDLERPARAMETER_H_
#define XHANDLERPARAMETER_H_

typedef struct TASKHANDLER_PARAM
{
	xTaskHandle* taskplayer1;
	xTaskHandle* taskplayer2;
	xTaskHandle* taskTickMovement;
	int* check;
} xHandlerParameters;



#endif /* XHANDLERPARAMETER_H_ */