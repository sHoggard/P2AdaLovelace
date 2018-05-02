#include <Servo.h>

#define pin_motorLeft 9
#define pin_motorRight 8
#define pin_sensorLeft1 34
#define pin_sensorLeft2 35
#define pin_sensorRight1 38
#define pin_sensorRight2 39
#define FULL_REVERSE 1000
#define MOTOR_BRAKE 1500
#define FULL_FORWARD 2000
#define FULL_ROTATION 144

Servo motorLeft;
Servo motorRight;

String printString;

int uL = 0;
int uR = 0;
int command;


void motorSetup() {
  Serial.println("motorSetup");
  //put motors in rest mode
  pinMode(pin_motorLeft, INPUT);
  pinMode(pin_motorRight, INPUT);
  while (digitalRead(pin_motorLeft) == 0 || digitalRead(pin_motorRight) == 0) {
    delayMicroseconds(100);
  }
  digitalWrite(pin_motorLeft, LOW);     //go low before switching to output mode
  digitalWrite(pin_motorRight, LOW);
  pinMode(pin_motorLeft, OUTPUT);
  pinMode(pin_motorRight, OUTPUT);
  delay(5);                             //wait for initialization
  //motors are ready to be attached
  motorLeft.attach(pin_motorLeft, FULL_REVERSE, FULL_FORWARD);
  motorRight.attach(pin_motorRight, FULL_REVERSE, FULL_FORWARD);
}

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  motorSetup();
  motorLeft.writeMicroseconds(uL);
  motorRight.writeMicroseconds(uR);

  //BT setup
  Serial1.println("U,9600,N");  // Change the baudrate to 9600, no parity
  Serial1.begin(9600);  // Start bluetooth serial at 9600
  command = 1500;
  Serial.println("setup done");
}

void loop() {

  delay(50);

  if(Serial1.available())  // If the PC sent any characters
  { 
    command = (int)Serial1.parseInt();
    Serial1.print(command); // Receives the string from PC and prints it back.
  delay(50);
  }
  
  uL = command;
  uR = command;
  if(command>=1000 && command<=2000)
  {
    motorLeft.writeMicroseconds(uL);
    motorRight.writeMicroseconds(uR);
  }
  delay(1);
}

