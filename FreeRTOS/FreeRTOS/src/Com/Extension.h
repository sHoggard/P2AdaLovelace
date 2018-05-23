/*
 * Extension.h
 *
 * Created: 2018-05-14 00:01:21
 *  Author: Sebastian Hoggard
 */ 


#ifndef EXTENSION_H_
#define EXTENSION_H_

enum t_object {
	BALL = 0b0001, 
	CUBE = 0b0010, 
	GLASS = 0b0011
};

struct s_extension {
	uint8_t ID;
	uint8_t distance_object;
	uint8_t bearing_object;
	uint8_t distance_dropzone;
	uint8_t bearing_dropzone;
	uint8_t max_speed;
	uint8_t type_object;
} data_extension;

#endif /* EXTENSION_H_ */