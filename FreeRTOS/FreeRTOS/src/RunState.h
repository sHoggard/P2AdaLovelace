/*
 * RunState.h
 *
 * Created: 2018-05-23 10:02:53
 *  Author: Jelena
 */ 


#ifndef RUNSTATE_H_
#define RUNSTATE_H_

#define STARTUP				1
#define TOWARDS_OBJECT_0	2
#define TOWARDS_OBJECT_1	3
#define SCAN_OBJECT			4
#define CLOSE_OBJECT_0		5
#define CLOSE_OBJECT_1		6
#define PICKUP				7
#define TOWARDS_BOX_0		8
#define TOWARDS_BOX_1		9
#define SCAN_BOX			10
#define CLOSE_BOX_0			11
#define CLOSE_BOX_1			12
#define DROPOFF				13

int currentState;


void changeState(int newState);

#endif /* RUNSTATE_H_ */