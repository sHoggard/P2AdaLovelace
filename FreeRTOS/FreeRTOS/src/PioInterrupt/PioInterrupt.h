/*
 * PioInterrupt.h
 *
 * Created: 2018-04-18 10:15:09
 *  Author: George
 */ 

 /* interruptz.h
 *
 * Created: 2018-04-17 13:19:34
 *  Author: gustav
 */
 
 
 #include <asf.h>
 #include "pio.h"
 #include "pio_handler.h"
 #include <stdio.h>

 #include <inttypes.h>

#ifndef PIOINTERRUPT_H_
#define PIOINTERRUPT_H__

uint32_t quadratureCounter;

 void configPioInterrupt(void);
 void myISR(uint32_t id, uint32_t mask);

#endif /* PIOINTERRUPT_H_ */