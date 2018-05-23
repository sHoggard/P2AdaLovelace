/*
 * Com.c
 *
 * Created: 2018-05-13 13:53:46
 *  Author: Sebastian Hoggard
 */ 

#include <asf.h>
#include "Com.h"
#include "membag/membag.h"
#include "TWI_Kommunikationen/TWI_Handler.h"
#include "Movement/Movement.h"
#include "config/conf_AdaLovelace.h"

struct buffer_data {
	uint8_t *data;
	int start_buffer;
	int end_buffer;
};

struct data_com {
	int i_slave;
	struct buffer_data *buffer_in;
	struct buffer_data *buffer_out;
};

uint8_t peekAtBuffer(struct buffer_data *buffer);
int availableInBuffer(struct buffer_data *buffer);
int readFromBuffer(struct buffer_data *buffer, uint8_t *data, int m_data);
void writeToBuffer(struct buffer_data *buffer, uint8_t *data, int m_data);

//void input(struct buffer_data *buffer, uint8_t value);
uint8_t input(struct buffer_data *buffer);
void output(struct buffer_data *buffer, uint8_t value);
//uint8_t output(struct buffer_data *buffer);

void initCom()
{
	puts("initCom");
	
	// TODO: reset data_extension
	if (position != 0)
	{
		membag_free(position->buffer_in->data);
		membag_free(position->buffer_in);
		membag_free(position->buffer_out->data);
		membag_free(position->buffer_out);
		membag_free(position);
	}
	position = membag_alloc(sizeof(struct data_com));
	position->i_slave = SLAVE_ADDRESS_POSITIONERING;
	position->buffer_in = membag_alloc(sizeof(struct buffer_data));
	position->buffer_in->data = membag_alloc(sizeof(uint8_t)*BUFFER_SIZE);
	position->buffer_in->start_buffer = 0;
	position->buffer_in->end_buffer = 0;
	position->buffer_out = membag_alloc(sizeof(struct buffer_data));
	position->buffer_out->data = membag_alloc(sizeof(uint8_t)*BUFFER_SIZE);
	position->buffer_out->start_buffer = 0;
	position->buffer_out->end_buffer = 0;
	
	if (extension != 0)
	{
		membag_free(extension->buffer_in->data);
		membag_free(extension->buffer_in);
		membag_free(extension->buffer_out->data);
		membag_free(extension->buffer_out);
		membag_free(extension);
	}
	extension = membag_alloc(sizeof(struct data_com));
	extension->i_slave = SLAVE_ADDRESS_PABYGGNAD;
	extension->buffer_in = membag_alloc(sizeof(struct buffer_data));
	extension->buffer_in->data = membag_alloc(sizeof(uint8_t)*BUFFER_SIZE);
	extension->buffer_in->start_buffer = 0;
	extension->buffer_in->end_buffer = 0;
	extension->buffer_out = membag_alloc(sizeof(struct buffer_data));
	extension->buffer_out->data = membag_alloc(sizeof(uint8_t)*BUFFER_SIZE);
	extension->buffer_out->start_buffer = 0;
	extension->buffer_out->end_buffer = 0;
	
	// test address allocation
	//printf("position: %p\n", position);
	//printf("extension: %p\n", extension);
	
	#ifdef DEBUG_PRINTS
	printf("init_twi: %i\n", init_twi());
	#else
	init_twi();
	#endif //DEBUG_PRINTS
	
	delay_s(2);
	
	output(extension->buffer_out, 0x20);		// Uppstart
}

uint8_t peekAtSlave(struct data_com *slave)
{
	return peekAtBuffer(slave->buffer_in);
}

int availableFromSlave(struct data_com *slave)
{
	return (slave->buffer_in->end_buffer - slave->buffer_in->start_buffer + BUFFER_SIZE)%BUFFER_SIZE;
}

int readFromSlave(struct data_com *slave, uint8_t *data, int m_data)
{
	int m_available = availableFromSlave(slave);
	m_data = ((m_data) < (m_available)) ?  (m_data) : (m_available);		// min(a, b)
	return readFromBuffer(slave->buffer_in, data, m_data);
}

void writeToSlave(struct data_com *slave, uint8_t *data, int m_data)
{
	writeToBuffer(slave->buffer_out, data, m_data);
}

void sendToSlave(struct data_com *slave, uint8_t value)
{
	transmit_package(value, slave->i_slave);
}

void task_com()
{
	// request from extension
	receive_package(extension->i_slave);
	
	// store extension data packet in buffer
	int m_data = receive_data_pabyggnad[0];
	receive_data_pabyggnad[0] = 0;						// avoid potentially re-reading data
	for (int index = 1; index <= m_data; index++)
	{
		output(extension->buffer_in, receive_data_pabyggnad[index]);
		#ifdef DEBUG_PRINTS
		printf("received byte from extension: %x\n", receive_data_pabyggnad[index]);
		#endif
	}
	
	// parse extension messages
	// TODO: put switch clause in while (bool parsed) ?
	switch (peekAtSlave(extension))
	{
		case 0x10:									// Identifiering
			if (availableFromSlave(extension) < 2)
			{
				break;
			}
			input(extension->buffer_in);
			data_extension.ID = input(extension->buffer_in);
			data_extension.type_object = data_extension.ID & 0b0011;
			break;
		case 0x11:									// Placering relativt objekt
			if (availableFromSlave(extension) < 3)
			{
				break;
			}
			input(extension->buffer_in);
			data_extension.distance_object = input(extension->buffer_in);
			data_extension.bearing_object = input(extension->buffer_in)*2;
			break;
		case 0x12:									// Placering relativt lådkant
			if (availableFromSlave(extension) < 3)
			{
				break;
			}
			input(extension->buffer_in);
			data_extension.distance_dropzone = input(extension->buffer_in);
			data_extension.bearing_dropzone = input(extension->buffer_in)*2;
			break;
		case 0x13:									// Maxhastighet
			if (availableFromSlave(extension) < 2)
			{
				break;
			}
			input(extension->buffer_in);
			data_extension.max_speed = input(extension->buffer_in);
			break;
		case 0x14:									// Lyckat lyft
			state_com = input(extension->buffer_in);
			printf("state_com: %x\n", state_com);
			// TODO: check and possibly change running state
			break;
		case 0x15:									// Misslyckat lyft
			state_com = input(extension->buffer_in);
			printf("state_com: %x\n", state_com);
			// TODO: check and possibly change running state
			break;
		case 0x16:									// Lyckad avlämning
			state_com = input(extension->buffer_in);
			printf("state_com: %x\n", state_com);
			// TODO: check and possibly change running state
			break;
		case 0x17:									// Misslyckad avlämning
			state_com = input(extension->buffer_in);
			printf("state_com: %x\n", state_com);
			// TODO: check and possibly change running state
			break;
		case 0x18:									// Justera position
			if (availableFromSlave(extension) < 2)
			{
				break;
			}
			state_com = input(extension->buffer_in);
			printf("state_com: %x\n", state_com);
			// TODO: check and possibly call drive(x, 0)
			drive((int)input(extension->buffer_in), 0);
			break;
		case 0x19:									// Justera vinkel
			if (availableFromSlave(extension) < 2)
			{
				break;
			}
			state_com = input(extension->buffer_in);
			printf("state_com: %x\n", state_com);
			// TODO: check and possibly call rotate(x, -1)
			rotate((int)input(extension->buffer_in), -1);
			break;
		case 0x1A:									// Avbryt justering
			state_com = input(extension->buffer_in);
			printf("state_com: %x\n", state_com);
			// TODO: check and possibly call stop()
			stop();
			break;
		default:									// No recognised message
			if (availableFromSlave(extension) > 0)
			{
				input(extension->buffer_in);
			}
			break;
	}
	
	// request from positioning system
	receive_package(position->i_slave);
	
	// store position data packet in buffer
	for (int index = 0; index < 10; index++)
	{
		output(position->buffer_in, receive_data_positionering[index]);
		#ifdef DEBUG_PRINTS
		printf("received byte from position: %i\n", receive_data_positionering[index]);
		#endif
	}
	
	// parse position data
	if (availableFromSlave(position) == 10)		// correct amount for storing
	{
		//x_koord_Box = (double)((int)input(position->buffer_in)*20);
		//y_koord_Box = (double)((int)input(position->buffer_in)*20);
		//x_koord_Kub = (double)((int)input(position->buffer_in)*20);
		//y_koord_Kub = (double)((int)input(position->buffer_in)*20);
		//x_koord_Kula = (double)((int)input(position->buffer_in)*20);
		//y_koord_Kula = (double)((int)input(position->buffer_in)*20);
		//x_koord_Vinglas = (double)((int)input(position->buffer_in)*20);
		//y_koord_Vinglas = (double)((int)input(position->buffer_in)*20);
		//x_koord_Robot = (double)((int)input(position->buffer_in)*20);
		//y_koord_Robot = (double)((int)input(position->buffer_in)*20);
		x_koord_Box = ((int)input(position->buffer_in)*20);
		y_koord_Box = ((int)input(position->buffer_in)*20);
		x_koord_Kub = ((int)input(position->buffer_in)*20);
		y_koord_Kub = ((int)input(position->buffer_in)*20);
		x_koord_Kula = ((int)input(position->buffer_in)*20);
		y_koord_Kula = ((int)input(position->buffer_in)*20);
		x_koord_Vinglas = ((int)input(position->buffer_in)*20);
		y_koord_Vinglas = ((int)input(position->buffer_in)*20);
		x_koord_Robot = ((int)input(position->buffer_in)*20);
		y_koord_Robot = ((int)input(position->buffer_in)*20);
		//printf("x_koord_Box: %i\n", (int)input(position->buffer_in)*20);
		//printf("y_koord_Box: %i\n", (int)input(position->buffer_in)*20);
		//printf("x_koord_Kub: %i\n", (int)input(position->buffer_in)*20);
		//printf("y_koord_Kub: %i\n", (int)input(position->buffer_in)*20);
		//printf("x_koord_Kula: %i\n", (int)input(position->buffer_in)*20);
		//printf("y_koord_Kula: %i\n", (int)input(position->buffer_in)*20);
		//printf("x_koord_Vinglas: %i\n", (int)input(position->buffer_in)*20);
		//printf("y_koord_Vinglas: %i\n", (int)input(position->buffer_in)*20);
		//printf("x_koord_Robot: %i\n", (int)input(position->buffer_in)*20);
		//printf("y_koord_Robo: %i\n"t, (int)input(position->buffer_in)*20);
		#ifdef DEBUG_PRINTS
		printf("Robot X: %i\n", x_koord_Robot);
		printf("Robot Y: %i\n", y_koord_Robot);
		#endif
	}
	else										// must be garbled
	{
		printf("Garbled input from position: %i bytes\n", availableFromSlave(position));
		while (availableFromSlave(position))
		{
			input(position->buffer_in);
		}
	}
	while (availableFromSlave(position))		// clear out potential garbage
	{
		input(position->buffer_in);
	}
	
	// transmit outgoing data, and let slave process it before requesting a reply
	transmit_package(input(extension->buffer_out), extension->i_slave);
}

void test_bufferFunctions()
{
	printf("Testing buffer functions\n");
	
	initCom();
	
	int size_test = 10;
	uint8_t test_write[10] = {0x5F, 0x5E, 0x5D, 0x5C, 0x70, 0x71, 0x72, 0x73, 0xA5, 0xB5};
	uint8_t test_read[10];
	
	printf("Original startup message - 20: %x\n", input(extension->buffer_out));
	
	// test input() and output() on individual buffers
	output(position->buffer_in, 0x63);
	printf("63: %x\n", input(position->buffer_in));
	output(position->buffer_out, 0x75);
	printf("75: %x\n", input(position->buffer_out));
	output(extension->buffer_in, 0x65);
	printf("65: %x\n", input(extension->buffer_in));
	output(extension->buffer_out, 0x67);
	printf("67: %x\n", input(extension->buffer_out));
	
	// test underflow
	printf("input() underflow - 0: %x\n", input(extension->buffer_in));
	
	// test first level functions
	writeToBuffer(extension->buffer_in, test_write, size_test);
	printf("writeToBuffer: \n5F: %x\n5E: %x\nA5: %x\nB5: %x\n", extension->buffer_in->data[1], extension->buffer_in->data[2], extension->buffer_in->data[9], extension->buffer_in->data[10]);
	printf("peekAtBuffer - 5F: %x\n", peekAtBuffer(extension->buffer_in));
	printf("availableInBuffer - 10: %i\n", availableInBuffer(extension->buffer_in));
	readFromBuffer(extension->buffer_in, test_read, size_test);
	printf("readFromBuffer: \n5F: %x\n5E: %x\nA5: %x\nB5: %x\n", test_read[0], test_read[1], test_read[8], test_read[9]);
	printf("peekAtBuffer - 0: %x\n", peekAtBuffer(extension->buffer_in));
	printf("availableInBuffer - 0: %i\n", availableInBuffer(extension->buffer_in));
	
	// test underflow
	printf("readFromBuffer() underflow - 0: %i\n", readFromBuffer(extension->buffer_in, test_read, size_test));
	
	// test second level functions
	writeToSlave(position, test_write, size_test);
	printf("writeToSlave: \n5F: %x\n5E: %x\nA5: %x\nB5: %x\n", position->buffer_out->data[1], position->buffer_out->data[2], position->buffer_out->data[9], position->buffer_out->data[10]);
	for (int index = 0; index < 10; index++)
	{
		output(position->buffer_in, input(position->buffer_out));
	}
	printf("peekAtSlave - 5F: %x\n", peekAtSlave(position));
	printf("availableFromSlave - 10: %i\n", availableFromSlave(position));
	readFromSlave(position, test_read, size_test);
	printf("readFromSlave: \n5F: %x\n5E: %x\nA5: %x\nB5: %x\n", test_read[0], test_read[1], test_read[8], test_read[9]);
	printf("peekAtSlave - 0: %x\n", peekAtSlave(position));
	printf("availableFromSlave - 0: %i\n", availableFromSlave(position));
	
	// test underflow
	printf("readFromSlave() underflow - 0: %i\n", readFromSlave(position, test_read, size_test));
	
	printf("Done testing buffer functions\n");
}



uint8_t peekAtBuffer(struct buffer_data *buffer)
{
	if (buffer->start_buffer == buffer->end_buffer)			// no data to read
	{
		return 0;
	}
	return buffer->data[buffer->start_buffer];
}

int availableInBuffer(struct buffer_data *buffer)
{
	return (buffer->end_buffer - buffer->start_buffer + BUFFER_SIZE)%BUFFER_SIZE;
}

int readFromBuffer(struct buffer_data *buffer, uint8_t *data, int m_data)
{
	int index = 0;
	for (; buffer->start_buffer != buffer->end_buffer && index < m_data; index++)		// don't read too much!
	{
		data[index] = input(buffer);
	}
	return index;
}

void writeToBuffer(struct buffer_data *buffer, uint8_t *data, int m_data)
{
	for (int index = 0; index < m_data; index++)
	{
		output(buffer, data[index]);
	}
}

//void input(struct buffer_data *buffer, uint8_t value)
//{
	//buffer->data[buffer->end_buffer] = value;
	//buffer->end_buffer = (buffer->end_buffer + 1)%BUFFER_SIZE;
//}

uint8_t input(struct buffer_data *buffer)
{
	if (buffer->start_buffer == buffer->end_buffer)
	{
		return 0x00;
	}
	uint8_t value = buffer->data[buffer->start_buffer];
	buffer->start_buffer = (buffer->start_buffer + 1)%BUFFER_SIZE;
	return value;
}

void output(struct buffer_data *buffer, uint8_t value)
{
	buffer->data[buffer->end_buffer] = value;
	buffer->end_buffer = (buffer->end_buffer + 1)%BUFFER_SIZE;
}

//uint8_t output(struct buffer_data *buffer)
//{
	//if (buffer->start_buffer == buffer->end_buffer)
	//{
		//return 0x00;
	//}
	//uint8_t value = buffer->data[buffer->start_buffer];
	//buffer->start_buffer = (buffer->start_buffer + 1)%BUFFER_SIZE;
//}