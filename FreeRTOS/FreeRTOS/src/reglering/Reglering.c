/*
 * CFile1.c
 *
 * Created: 2018-04-23 09:51:12
 *  Author: Jack Mao
 */ 
 #include "MotorControl.h" 
 #include "WheelCounters.h"

 uint16_t error=0;
 uint16_t prevError=0;
 uint16_t bv = 0;
 uint16_t P =0;
 uint16_t I=0;
 uint16_t D=0;
 double kp=0;
 double Td=0;
 double Ti=0;
 double dT=0;
 int32_t sum=0;
 uint16_t u; // nya styrvärdet

 // styrvärde motorer
 //var ska värderna sättas?
 uint16_t motorright = 0; 
 uint16_t motorleft = 0;

 void PID(int32_t counterLeft, int32_t counterRight){ 

  while(1){ 

	  error = counterLeft - counterRight;
	  sum = sum + error;
	  P = kp*error;
	  I = (sum*(dT/Ti));
	  D = ((error-prevError)*(Td/dT));
	  prevError = error;

	  u = P + I + D;
	  
	  if ( error > bv){
		  motorleft = motorleft - u;
		  motorright = motorright + u;
	  }
	  else if( error < bv){
		  motorleft = motorleft + u;
		  motorright = motorright - u;
	  }

	  //Sätta det nya styrvärdet till motor via PWM
	  // NEW PWM Value
	  pwm_channel_update_duty(PWM, &pwm_motorLeft, motorleft);
	  pwm_channel_update_duty(PWM, &pwm_motorRight, motorright);
  }

 }
