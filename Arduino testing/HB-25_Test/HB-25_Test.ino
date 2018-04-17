//  HB-25 Library Test
//
//  Version:  1.1
//  Date:     10th December 2015
//
//  Valid speed ranges for the forwardAtSpeed and reverseAtSpeed methods are
//  0 (stop) to 500 (maximum speed). For rampToSpeed and moveAtSpeed you can use from -500 (full
//  reverse) to 500 (full forward). As before, a speed of 0 will stop the motor.
//
//	Remember to call the begin() method in setup().
//
//  Adapted from a sketch by zoomkat 10-22-11 serial servo test

#include <Servo.h>                      //  You need to include Servo.h as it is used by the HB-25 Library
#include "HB25MotorControl.h"

const byte controlPin1 = 2;              //  Pin Definition
const byte controlPin2 = 3;              //  Pin Definition
String readString;
boolean regulateRightMotor = false;
boolean regulateLeftMotor = false;
boolean regulateBothMotors = false;


HB25MotorControl motorControl1(controlPin1);
HB25MotorControl motorControl2(controlPin2);

void setup() {
  Serial.begin(9600);
  Serial.println("HB-25 Motor Control Library Test");
  Serial.println("Enter a speed between -500 and 500.");
  Serial.println("A negative speed will reverse the motor direction. 0 will stop.");
  motorControl1.begin();
  motorControl2.begin();
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();             //  Gets one byte from the serial buffer
    readString += c;
    delay(2);                           //  Slow looping to allow buffer to fill with the next character
  }
    
    if (readString.length() > 0) {
      Serial.print("\nString entered: ");
      Serial.print(readString);        // Echo captured string
      int n = readString.toInt();     // Convert readString into a number
      Serial.println(readString);
      if ( n >3000){                   // value over 3000 makes the robot rotate
        n = n - 3500;
        regulateRightMotor = true;
        regulateLeftMotor = true;
        
      }
      else if (n >2000){
        n = n - 2500;
        regulateRightMotor = true;
      }
      else if(n > 1000){
        n = n - 1500;
        regulateLeftMotor = true;
      }
      else{
        regulateBothMotors = true;
      }
    
     n = constrain(n, -500, 500);
    
      if (n > 0) {
        Serial.print("Set Forward Speed: ");
      } else if (n < 0) {
        Serial.print("Set Reverse Speed: ");
      } else {
        Serial.print("Stop Motor. Speed: ");
      }
      Serial.println(n);
      if (regulateRightMotor && regulateLeftMotor){
                motorControl1.moveAtSpeed(n);
                motorControl2.moveAtSpeed(-n);
      }
      else if(regulateRightMotor){
        motorControl1.moveAtSpeed(n);
      }
      else if(regulateLeftMotor)
      {
        motorControl2.moveAtSpeed(n);
      }
      else if(regulateBothMotors){
        motorControl1.moveAtSpeed(n);
        motorControl2.moveAtSpeed(n);
      }
    }
    regulateRightMotor = false;
    regulateLeftMotor = false;
    regulateBothMotors = false;
    readString = "";                  //  Empty string for the next input
}

