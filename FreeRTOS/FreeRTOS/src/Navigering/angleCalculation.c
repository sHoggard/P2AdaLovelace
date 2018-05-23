/*
 * CFile1.c
 *
 * Created: 2018-05-08 14:15:12
 *  Author: Jelena
 */ 
/*
*calculations.c
* Created: 2018-04-26 09:18:32
* Author: Kablai Tokhi
*/


#include "angleCalculation.h"
#include <math.h>


/*
double correctionAngleCalculation(double xObject, double xRobot, uint8_t yObject, uint8_t yRobot, double oldAngle){
	
	double correctionAngle =0.0;
	double newAngle = degreeCalculation(xObject, xRobot, yObject, yRobot);
	
	if(oldAngle == 0){
		correctionAngle = newAngle;
	}
	
	if (newAngle > oldAngle){
		correctionAngle = newAngle - oldAngle;
		}else if(newAngle < oldAngle){
		correctionAngle = -(oldAngle - newAngle);
	}
	
	return correctionAngle;
}
*/

double degreeCalculation(double xObject, double xRobot, double yObject, double yRobot){
	
	double alpha = 0.0;
	double yDifference = yObject - yRobot;
	double xDifference = xObject - xRobot;

	double yAbsolute = abs(yDifference);
	double xAbsolute = abs(xDifference);

	double k = yAbsolute / xAbsolute;

	double s = distanceCalculation( xObject,  xRobot,  yObject, yRobot);

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
		
		}else if(sinusValue > 0 && cosinusValue > 0){
		alpha = rad2deg(atan(k));
		}else if(sinusValue > 0 && cosinusValue < 0){
		alpha = rad2deg(atan(k))+ 90;
		}else if(sinusValue < 0 && cosinusValue < 0) {
		alpha = 180 + rad2deg(atan(k));
		}else if(sinusValue < 0 && cosinusValue >= 0){
		alpha = 270 + rad2deg(atan(k));
	}
	return alpha;
}

double distanceCalculation(double xObject, double xRobot, double yObject, double yRobot){
	double s = 10*(sqrt( pow((xObject-xRobot),2)  +  pow ( (yObject-yRobot),2) ));
	return s;
}
double rad2deg(double radianValue){
	double alpha = radianValue * 180 / PI;
	return alpha;
}