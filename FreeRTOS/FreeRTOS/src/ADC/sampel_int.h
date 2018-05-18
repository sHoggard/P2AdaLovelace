/*
 * sampel_int.h
 *
 * Created: 2013-12-10 12:30:49
 *  Author: Tommy, George Albert Florea, Jack Mao
 */ 


#ifndef SAMPEL_INT_H_
#define SAMPEL_INT_H_

#define CHECK_PIN PIO_PB26_IDX	//Ardiuno Due pin 22 used to measure work load

uint32_t currentdistance;
uint32_t lastdistance;

void TC_Handler(void);


#endif /* SAMPEL_INT_H_ */