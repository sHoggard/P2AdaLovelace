/*
 * TimerCounte.h
 *
 * Created: 2017-01-11 12:17:49
 *  Author: George & Benjamin 
 */ 


#ifndef TIMERCOUNTE_H_
#define TIMERCOUNTE_H_

void init_timer(void);
void init_array(void);

//CHECK_PIN PIO_PB21_IDX = Digital Pin 52
#define CHECK_PIN PIO_PB21_IDX	//Ardiuno Due pin 22 used to measure work load

void TC3_Handler(void);

#endif /* TIMERCOUNTE_H_ */