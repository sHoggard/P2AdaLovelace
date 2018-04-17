/*
 *	Parallax HB-25 (Part Number: #29144) 
 *	Motor Controller Library
 *
 *  Written By:	David Such (Reefwing Software - http://www.reefwing.com.au/)
 *  Version: 	1.0
 *  Date:    	11th October 2015
 *
 *	Version History:
 *		1.0		11/10/15	Original release
 *
 *	Wiring:
 *		1.	If you are using the Parallax Motor Mount and wheel kits (part numbers
 *			#28962 - aluminium or #28963 - plastic) then the red cable should be 
 *			connected to M1 on the HB-25 and the blue cable should be connected to
 *			M2. If these are reversed then the FORWARD and REVERSE commands will be 
 *			reversed.
 *		2.	Make sure that the jumper is in place for mode 1 operation.
 *
 *	Notes:
 *		1. 	Library currently only supports mode 1 operation of the HB-25. In this
 *			mode, you need a separate digital output for each HB-25 that you want to
 *			control.
 *		2.	The HB-25 operates like a servo. You only need to send a single pulse (in mode 1)
 *			to change direction or speed. Pulse width determines the HB-25 output.
 *		3.	Valid pulse widths are 0.8 ms to 2.2 ms. If the HB-25 receives a pulse width
 *			which is outside this range, the motor will be stopped until it receives a 
 *			valid pulse.
 *		4.	The minimum time between pulses (HOLD_OFF_TIME) is 5.25 ms + pulse time (max 2.2 ms).
 *			Thus the worst case hold off time needs to be 7.45 ms. We have used 8 ms.
 *		5.	The maximum time between pulse is unlimited, since a single pulse will be latched
 *			by the HB-25. An exception to this would be if the Communication Timeout feature of
 *			the HB-25 has been enabled. You can read more about this on the HB-25 data sheet 
 *			(https://www.parallax.com/downloads/hb-25-motor-controller-product-documentation).
 *		6.	Regardless of the mode, the HB-25 signal pin should be brought low immediately upon
 *			power up. The Library does this when you instantiate a HB25MotorControl object.
 *		7.	Pulse Input (1 ms = 1000 microseconds):
 *				1.0 ms	Full Reverse
 *				1.5 ms	Neutral (STOP)
 *				2.0 ms	Full Forward
 *		8.	Valid speed ranges for the forwardAtSpeed and reverseAtSpeed methods are
 *			0 (stop) to 500 (maximum speed). For moveAtSpeed & rampToSpeed you can use from -500 (full
 *			reverse) to 500 (full forward). As before, a speed of 0 will stop the motor.
 *
 */
 
#ifndef HB25MotorControl_h
#define	HB25MotorControl_h

#include <Arduino.h>
#include <Servo.h>

#define REVERSE       1000
#define STOP          1500
#define FORWARD       2000
#define HOLD_OFF_TIME 8

class HB25MotorControl
{
private:
	unsigned long _timeOfLastCommand;
	void _checkHoldOffTime();
	Servo _servo;
	byte _controlPin;
public:
	HB25MotorControl(byte controlPin);
	void begin();
	void stop();
	void fullForward();
	void fullReverse();
	void rampToSpeed(int speed);
	void moveAtSpeed(int speed);
	void forwardAtSpeed(int speed);
	void reverseAtSpeed(int speed);
};

#endif