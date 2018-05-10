/*
 * angleCalculation.h
 *
 * Created: 2018-05-08 14:16:23
 *  Author: Jelena
 */ 


#ifndef ANGLECALCULATION_H_
#define ANGLECALCULATION_H_

#include <asf.h>
#include <inttypes.h>
#include <stdio_serial.h>

#include "conf_board.h"
#include "conf_clock.h"
#include "math.h"
#include "MotorControl/MotorControl.h"
#include "WheelCounters/WheelCounters.h"

#define PI 3.14159265


#include "Utilities/ConsoleFunctions/consoleFunctions.h"



double correctionAngleCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot, double oldAngle);

double degreeCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot);

double distanceCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot);

//double currentCourseCalculation(uint8_t xRobot, uint8_t xPreviousRobotPosition, uint8_t yRobot, uint8_t yPreviousRobotPosition);

double rad2deg(double radianValue);

#endif /* ANGLECALCULATION_H_ */