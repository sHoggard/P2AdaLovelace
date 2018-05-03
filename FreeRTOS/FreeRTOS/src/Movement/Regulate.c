/*
 * Regulate.c
 *
 * Created: 2018-05-01 22:51:13
 *  Author: Jack Mao
 */ 

 #include "Movement.h"
 #include "__vars.h"
 #include "WheelCounters/WheelCounters.h"
 
 #define HISTORY_SIZE 10

 double uL;
 double uR;
 
 double error=0;				// felvärde
 double prevError=0;			// förgående felvärde
 double bv = 0;					// börvärde
 double P=0;					// P-regulator
 double I=0;					// I-regulator
 double D=0;					// D-regulator
 double kp=2;
 double Td=0;
 double Ti=0;
 double dT=0;
 double sum=0;					// summan av flera felvärden
 double u;						// nya styrvärdet

 double N =144;					// pulser per rotation
 double t =1;					// samplingstid
 double uV =0;					// hastighet för vänsterhjul
 double uH =0;					// hastighet för högerhjul
 double pi =3.14159265359;
 double omkrets=49;

 double lastLeft = 0;
 double lastRight = 0;

 double currentLeft = 0;
 double currentRight = 0;

 double historyLeft[HISTORY_SIZE] = {0};
 double historyRight[HISTORY_SIZE] = {0};

 void task_regulate(void *pvParameters) 
{
	uL = regulated_speed.target;
	uR = regulated_speed.target;
	
	currentRight = counterRight;
	currentLeft = counterLeft;

		 //move history upwards
		for (int index = HISTORY_SIZE; index > 1; index--) {
			  historyLeft[index - 1] = historyLeft[index - 2];
			  historyRight[index - 1] = historyRight[index - 2];
		}
  
		//new history
		historyRight[0] = currentRight;
		historyLeft[0] = currentLeft;
  
		uV = (((2*pi*(historyLeft[0] - historyLeft[4]))/(N/t))/(2*pi))*omkrets;
		uH = (((2*pi*(historyRight[0] - historyRight[4]))/(N/t))/(2*pi))*omkrets;
  
		//PID reglering

		error = uV - uH;
		//sum = sum + error;
		P = kp*error;
		// I = (sum*(dT/Ti));
		// D = ((error-prevError)*(Td/dT));
		//prevError = error;

		u = P + I + D;
  
		if ( error > bv)
		{
			uL = (uL + u);
			uR = (uR - u);
		}
		else if( error < bv)
		{
			uL = (uL - u);
			uR = (uR + u);
		}

		regulated_speed.left = uL;
		regulated_speed.right = uR;
  }
	 
