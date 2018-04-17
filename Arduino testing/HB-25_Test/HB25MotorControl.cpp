#include "HB25MotorControl.h"

HB25MotorControl::HB25MotorControl(byte controlPin) {
	_controlPin = controlPin;
}

//	Private Methods

void HB25MotorControl::_checkHoldOffTime() {
	//	Check that time since the last command is greater than the HOLD_OFF_TIME.
	//	
	//	Note - Millis() returns the number of milliseconds since the Arduino board began running the current program. 
	//	This number will overflow (go back to zero), after approximately 50 days. We will check for this overflow.
	
	unsigned long timeSinceStartUp = millis();
	
	if (timeSinceStartUp <= _timeOfLastCommand) {		//	Millis() Overflow
		delay(HOLD_OFF_TIME);
	}
	
	unsigned long timeSinceLastCommand = timeSinceStartUp - _timeOfLastCommand;
	
	if (timeSinceLastCommand < HOLD_OFF_TIME) {
		delay(HOLD_OFF_TIME - timeSinceLastCommand);
	} 
}

//	Public Methods

void HB25MotorControl::begin() {
	_timeOfLastCommand = 0;
	delay(5);											//	HB-25 initialisation time
	pinMode(_controlPin, OUTPUT);
	digitalWrite(_controlPin, LOW);						//	Set control pin low on power up
	_servo.attach(_controlPin, 800, 2200);				//	Attach HB-25 to the control pin & set valid range
	_servo.writeMicroseconds(STOP);
	delay(20);
}

void HB25MotorControl::stop() {
	_checkHoldOffTime();
	_servo.writeMicroseconds(STOP);
	_timeOfLastCommand = millis();
}

void HB25MotorControl::fullForward() {
	_checkHoldOffTime();
	_servo.writeMicroseconds(FORWARD);
	_timeOfLastCommand = millis();
}

void HB25MotorControl::fullReverse() {
	_checkHoldOffTime();
	_servo.writeMicroseconds(REVERSE);
	_timeOfLastCommand = millis();
}

void HB25MotorControl::rampToSpeed(int speed) {
	_checkHoldOffTime();
	speed = constrain(speed, -500, 500);
	speed = STOP + speed;
	if (speed > 0) {
		for (int rampSpeed = STOP; rampSpeed < speed; rampSpeed++) {
			_servo.writeMicroseconds(rampSpeed);
			delay(150);
		}
	} else if (speed < 0) {
		for (int rampSpeed = STOP; rampSpeed > speed; rampSpeed--) {
			_servo.writeMicroseconds(rampSpeed);
			delay(150);
		}
	} else {
		_servo.writeMicroseconds(STOP);
	}
}

void HB25MotorControl::moveAtSpeed(int speed) {
	_checkHoldOffTime();
	speed = constrain(speed, -500, 500);				//	Constrain speed to valid range
	speed = STOP + speed;
	_servo.writeMicroseconds(speed);
	_timeOfLastCommand = millis();
}


void HB25MotorControl::forwardAtSpeed(int speed) {
	_checkHoldOffTime();
	speed = constrain(speed, 0, 500);					//	Constrain speed to valid range
	speed = STOP + speed;
	_servo.writeMicroseconds(speed);
	_timeOfLastCommand = millis();
}

void HB25MotorControl::reverseAtSpeed(int speed) {
	_checkHoldOffTime();
	speed = constrain(speed, 0, 500);					//	Constrain speed to valid range
	speed = STOP - speed;
	_servo.writeMicroseconds(speed);
	_timeOfLastCommand = millis();
}