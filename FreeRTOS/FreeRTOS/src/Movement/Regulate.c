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
 
 double error=0;				// felv�rde
 double prevError=0;			// f�rg�ende felv�rde
 double bv = 0;					// b�rv�rde
 double P=0;					// P-regulator
 double I=0;					// I-regulator
 double D=0;					// D-regulator
 double kp=0.100;				// kp = t/1000 verkar fungera bra med Arduino-kod
 double Td=0;
 double Ti=0;
 double dT=0;
 double sum=0;					// summan av flera felv�rden
 double u;						// nya styrv�rdet

 double N =144;					// pulser per rotation
 double t =100;					// samplingstid
 double uV =0;					// hastighet f�r v�nsterhjul
 double uH =0;					// hastighet f�r h�gerhjul
 double pi =3.14159265359;
 double omkretsV=486;
 double omkretsH=488.5;

 double lastLeft = 0;
 double lastRight = 0;

 double currentLeft = 0;
 double currentRight = 0;

 double historyLeft[HISTORY_SIZE] = {0};
 double historyRight[HISTORY_SIZE] = {0};

 void task_regulate(void *pvParameters) 
{
	currentLeft = counterLeft;
	currentRight = counterRight;
	
	printf("counterLeft: %i\ncounterRight: %i\n", (int)counterLeft, (int)counterRight);

	//uL = regulated_speed.target;
	//uR = regulated_speed.target;
	
		 //move history upwards
		for (int index = HISTORY_SIZE; index > 1; index--) {
			  historyLeft[index - 1] = historyLeft[index - 2];
			  historyRight[index - 1] = historyRight[index - 2];
		}
  
		//new history
		historyLeft[0] = currentLeft;
		historyRight[0] = currentRight;
  
		//uV = (((2*pi*(historyLeft[0] - historyLeft[1]))/(N/t))/(2*pi))*omkretsV;
		//uH = (((2*pi*(historyRight[0] - historyRight[1]))/(N/t))/(2*pi))*omkretsH;
		
		uV = ((historyLeft[0] - historyLeft[1])*omkretsV*1000/(N*t));
		uH = ((historyRight[0] - historyRight[1])*omkretsH*1000/(N*t));
		
		printf("uV*K: %i\nuH*K: %i\n", (int)(uV*1000), (int)(uH*1000));
  
		//PID reglering

		error = uV - uH;
		printf("error*K: %i\n", (int)(error*1000));
		//sum = sum + error;
		P = kp*error;
		printf("P*K: %i\n", (int)(P*1000));
		// I = (sum*(dT/Ti));
		// D = ((error-prevError)*(Td/dT));
		//prevError = error;

		u = P + I + D;
  
		uL = (uL - u);
		uR = (uR + u);

		regulated_speed.left = regulated_speed.target + uL;
		regulated_speed.right = regulated_speed.target + uR;
		
		printf("left: %i\nright: %i\n", regulated_speed.left, regulated_speed.right);
  }
	 
