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

 double leftCorrection;
 double rightCorrection;
 double speedCorrection;
 
 double error=0;				// felv�rde
 double errorSpeed=0;
 double prevError=0;			// f�rg�ende felv�rde
 double bv = 0;					// b�rv�rde
 double P=0;					// P-regulator
 double Pspeed=0;
 double I=0;					// I-regulator
 double D=0;					// D-regulator
 double kp=0.100;				// kp = t/1000 verkar fungera bra med Arduino-kod
 double kpSpeed =0.1;
 double Td=0;
 double Ti=0;
 double dT=0;
 double sum=0;					// summan av flera felv�rden
 double u;						// nya styrv�rdet

 double N =144;					// pulser per rotation
 double t =100;					// samplingstid
 double leftSpeed =0;					// hastighet f�r v�nsterhjul
 double rightSpeed =0;					// hastighet f�r h�gerhjul
 double totSpeed=0;
 double pi =3.14159265359;
 //double omkretsV=486;
 //double omkretsH=488.5;

 double lastLeft = 0;
 double lastRight = 0;

 double currentLeft = 0;
 double currentRight = 0;

 double historyLeft[HISTORY_SIZE] = {0};
 double historyRight[HISTORY_SIZE] = {0};

 void task_regulate() 
{
	currentLeft = counterLeft;
	currentRight = counterRight;
	
	//printf("counterLeft: %i\ncounterRight: %i\n", (int)counterLeft, (int)counterRight);
	
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
		
		leftSpeed = ((historyLeft[0] - historyLeft[1])*CIRCUMFERENCE_LEFT*1000/(N*t));
		rightSpeed = ((historyRight[0] - historyRight[1])*CIRCUMFERENCE_RIGHT*1000/(N*t));
		totSpeed = (leftSpeed+rightSpeed)/2;
		
		//printf("uV*K: %i\nuH*K: %i\n", (int)(leftSpeed*1000), (int)(rightSpeed*1000));
		//printf("totSpeed*K: %i\n", (int)(totSpeed*1000));
  
		//PID reglering

		if (mode_movement == 'r')
		{
			rightSpeed *= (-1);
		}
		error = leftSpeed - rightSpeed;
		errorSpeed = regulated_speed.target - totSpeed;
		//printf("error*K: %i\n", (int)(error*1000));
		//printf("errorSpeed*K: %i\n", (int)(errorSpeed*1000));
		//sum = sum + error;
		P = kp*error;
		Pspeed = errorSpeed*kpSpeed;
		if (errorSpeed > 200)
		{
			Pspeed *= 3;
		}
		else if (errorSpeed > 50)
		{
			Pspeed *= 2;
		}
		//printf("P*K: %i\n", (int)(P*1000));
		//printf("Pspeed*K: %i\n", (int)(Pspeed*1000));
		// I = (sum*(dT/Ti));
		// D = ((error-prevError)*(Td/dT));
		//prevError = error;

		u = P + I + D;
  

		leftCorrection = leftCorrection - u;
		rightCorrection = rightCorrection + u;
		speedCorrection += Pspeed;

		regulated_speed.left = leftCorrection + speedCorrection;
		regulated_speed.right = rightCorrection + speedCorrection;

		//switch (mode_movement)
		//{
			//case 'd':
				//break;
			//case 'r':
				//leftCorrection = (leftCorrection - u + Pspeed);
				//rightCorrection = (rightCorrection - u + Pspeed);
				//regulated_speed.left = regulated_speed.target + leftCorrection;
				//regulated_speed.right = -(regulated_speed.target + rightCorrection);
				//break;
		//}
		
		//printf("left: %i\nright: %i\n", regulated_speed.left, regulated_speed.right);
  }
	 
int16_t getSpeed()
{
	return ((historyLeft[0] - historyLeft[1]) + (historyRight[0] - historyRight[1]))/2;
}