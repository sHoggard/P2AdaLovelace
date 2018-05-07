/*
 * angleCalc.h
 *
 * Created: 2018-05-07 11:29:12
 *  Author: Jelena
 */ 


#ifndef ANGLECALC_H_
#define ANGLECALC_H_
#include <asf.h>
#include <inttypes.h>
#include <stdio_serial.h>

#include "conf_board.h"
#include "conf_clock.h"
#include "math.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"

#define PI 3.14159265

double correctionAngleCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot, double oldAngle);

double degreeCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot);

double distanceCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot);

double rad2deg(double radianValue);

#endif /* ANGLECALC_H_ */