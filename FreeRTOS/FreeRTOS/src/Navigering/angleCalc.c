/*
 * angleCalc.c
 *
 * Created: 2018-05-07 11:28:14
 *  Author: Jelena
 */ 
/*
*calculations.c
* Created: 2018-04-26 09:18:32
* Author: Kablai Tokhi
*/


#include "angleCalc.h"



double correctionAngleCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot, double oldAngle){
	
	double correctionAngle =0;
	double newAngle = degreeCalculation( xObject,  xRobot,  yObject,  yRobot);

	if (newAngle > oldAngle){
		correctionAngle = oldAngle - newAngle;
		}else if(newAngle < oldAngle){
		correctionAngle = newAngle - oldAngle;
	}
	
	return correctionAngle;
}

double degreeCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot){

	double alpha = 0.0;
	uint8_t yDifference = yObject - yRobot;
	uint8_t xDifference = xObject - xRobot;

	uint8_t yAbsolute = abs(yDifference);
	uint8_t xAbsolute = abs(xDifference);

	double k = yAbsolute / xAbsolute;

	double s = distanceCalculation( xObject,  xRobot,  yObject,  yRobot);

	double cosinusValue = xDifference / s;
	double sinusValue = yDifference / s;

	if(sinusValue == 0 && cosinusValue >0){
		alpha = 0.0;
		}else if(sinusValue > 0 && cosinusValue == 0){
		alpha = 90.0;
		}else if(sinusValue == 0 && cosinusValue <0){
		alpha = 180.0;
		}else if(sinusValue < 0 && cosinusValue == 0){
		alpha = 270.0;
		
		}else if(sinusValue > 0 && cosinusValue >= 0){
		alpha = rad2deg(atan(k));
		}else if(sinusValue >= 0 && cosinusValue < 0){
		alpha = rad2deg(atan(k))+ 90;
		}else if(sinusValue <= 0 && cosinusValue < 0) {
		alpha = 270 - rad2deg(atan(k));
		}else if(sinusValue < 0 && cosinusValue >= 0){
		alpha = 360 - rad2deg(atan(k));
	}
	return alpha;
}

double distanceCalculation(uint8_t xObject, uint8_t xRobot, uint8_t yObject, uint8_t yRobot){
	double s = sqrt((pow((xObject-xRobot),2)) +  (pow((yObject-yRobot),2)));
	return s;
}
double rad2deg(double radianValue){
	double alpha = radianValue * 180 / PI;
	return alpha;
}