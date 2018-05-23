/*
 * Com.h
 *
 * Created: 2018-05-13 13:47:38
 *  Author: Sebastian Hoggard
 */ 


#ifndef COM_H_
#define COM_H_

#include <inttypes.h>
#include "Extension.h"
#include "KOM_NAV.h"

#define BUFFER_SIZE 100
#define PACKET_SIZE 10

uint8_t state_com;

struct data_com;

struct data_com *position;
struct data_com *extension;

void initCom(void);

uint8_t peekAtSlave(struct data_com *slave);
int availableFromSlave(struct data_com *slave);
int readFromSlave(struct data_com *slave, uint8_t *data, int m_data);
void writeToSlave(struct data_com *slave, uint8_t *data, int m_data);
void sendToSlave(struct data_com *slave, uint8_t value);

void task_com(void);

void test_bufferFunctions(void);

#endif /* COM_H_ */