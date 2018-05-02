/*
 * Regulate.c
 *
 * Created: 2018-05-01 22:51:13
 *  Author: Jack Mao
 */ 
 #include "Movement.h"
 #include "__vars.h"
 #include "WheelCounters.h"
 #define HISTORY_SIZE 10

 int uL = regulated_speed.left;
 int uR = regulated_speed.right;
 
 double error=0;				// felvärde
 int prevError=0;				// förgående felvärde
 int bv = 0;					// börvärde
 double P=0;					// P-regulator
 double I=0;					// I-regulator
 double D=0;					// D-regulator
 double kp=1;
 double Td=0;
 double Ti=0;
 double dT=0;
 double sum=0;					// summan av flera felvärden
 double u;						// nya styrvärdet

 int N =144;					// pulser per rotation
 int t =1;						// samplingstid
 double uV =0;					// hastighet för vänsterhjul
 double uH =0;					// hastighet för högerhjul
 double pi =3.14159265359;
 double omkrets=49;

 signed long lastLeft = 0;
 signed long lastRight = 0;

 signed long currentLeft = 0;
 signed long currentRight = 0;

 signed long historyLeft[HISTORY_SIZE] = {0};
 signed long historyRight[HISTORY_SIZE] = {0};

 struct s_speed {
	 int16_t target;
	 int16_t left;
	 int32_t right;
 } regulated_speed;

 void task_regulate(void *pvParameters) 
{
	currentRight = counterRight;
	currentLeft = counterLeft;

		 //move history upwards
		for (int index = HISTORY_SIZE; index > 0; index--) {
			  historyLeft[index - 1] = historyLeft[index - 2];
			  historyRight[index - 1] = historyRight[index - 2];
		}
  
		//new history
		historyRight[0] = currentRight;
		historyLeft[0] = currentLeft;
  
		uV = (((2*pi*(historyLeft[0] - historyLeft[9]))/(N/t))/(2*pi))*omkrets;
		uH = (((2*pi*(historyRight[0] - historyRight[9]))/(N/t))/(2*pi))*omkrets;
  
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
			uL = (uL - P);
			uR = (uR + P);
		}
		else if( error < bv)
		{
			uL = (uL + 1);
			uR = (uR - 1);
		}

		regulated_speed.left = uL;
		regulated_speed.right = uR;
  }
	 
